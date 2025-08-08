#include "TextManager.h"
#include <string>


enum class MenuOptions {
   FIGHT = 0,
   RUN = 1,
   COUNT
};

// PlaceHolder for DisplayOptions
enum class DisplayOptions {
   NONE = 0,
   MENU = 1,
   TEXT = 2
};
TextManager::TextManager(TTF_Font* font) : font(font), textTexture(nullptr), text("UNKNOWN TEXT"), selectedIndex(0) {
}


TextManager::~TextManager() {
   if (textTexture) {
      SDL_DestroyTexture(textTexture);
      textTexture = nullptr;
   }
   // Note: Do not destroy the font here, as it's managed by the Game class
}


std::string TextManager::menuEvent(SDL_Event& event) {
   if (event.type != SDL_EVENT_KEY_DOWN) return "";
   int maxIndex = static_cast<int>(MenuOptions::COUNT);
   switch (event.key.scancode) {
   case SDL_SCANCODE_A:
      selectedIndex = (selectedIndex - 1 + maxIndex) % maxIndex;
      break;
   case SDL_SCANCODE_D: 
      selectedIndex = (selectedIndex + 1) % maxIndex;
      break;
   
   case SDL_SCANCODE_SPACE:
      switch (static_cast<MenuOptions>(selectedIndex)) {
      case MenuOptions::FIGHT:
         SDL_Log("Fight Selected"); 
         return "FIGHT";
      case MenuOptions::RUN:
         SDL_Log("Run Selected"); 
         return "RUN";
      default: 
         SDL_Log("Invalid selection: %d", selectedIndex); 
         return "";
      }
   default: return "";
   }
   return "";
}


void TextManager::display(SDL_Renderer* renderer, int logicalWidth, int logicalHeight, std::string option) {


   float gui_height = logicalHeight / 3.0f;
   float gui_y = logicalHeight - gui_height;

   // Draw GUI backdrop
   SDL_FRect GUIBackdrop = { 0.0f, gui_y, static_cast<float>(logicalWidth), gui_height };
   SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue backdrop
   SDL_RenderFillRect(renderer, &GUIBackdrop);

   if (!font ||  getText().size() == 0) {
      SDL_Log("Font or text is null");
      return;
   }

   // Define text color (white)
   SDL_Color textColor = { 255, 255, 255, 255 };

   // Render text to a surface using TTF_RenderText_Solid_Wrapped
   SDL_Surface* textSurface = TTF_RenderText_Solid_Wrapped(font, getText().c_str(), 0, textColor, logicalWidth - 20);
   if (!textSurface) {
      SDL_Log("Failed to render text: %s", SDL_GetError());
      return;
   }

   // Convert surface to texture
   textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
   SDL_DestroySurface(textSurface);
   if (!textTexture) {
      SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
      return;
   }

   // Define destination rectangle for text with padding
   float text_padding = 10.0f;
   SDL_FRect textRect = {
       text_padding,
       gui_y + text_padding,
       static_cast<float>(logicalWidth) - 2 * text_padding,
       gui_height - 2 * text_padding
   };

   // Render the text texture
   if (!SDL_RenderTexture(renderer, textTexture, nullptr, &textRect)) {
      SDL_Log("Failed to render text texture: %s", SDL_GetError());
   }
   if(option == "FIGHT") {
      SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red line for FIGHT
   } else if(option == "RUN") {
      SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green line for RUN
   } else {
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Default white line
   }
   // Draw a line under the text in logical coordinates (as a UI element)
   //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White line
   //float lineY = gui_y + gui_height - 30; // Position the line above the bottom of the GUI
   //SDL_RenderLine(renderer, lineX, lineY, logicalWidth / 1.8, lineY);

   // Clean up texture
   SDL_DestroyTexture(textTexture);
   textTexture = nullptr;
}



