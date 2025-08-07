#include "TextManager.h"

TextManager::TextManager(TTF_Font* font) : font(font), textTexture(nullptr), text("UNKNOW TEXT") {
}

TextManager::~TextManager() {
   if (textTexture) {
      SDL_DestroyTexture(textTexture);
      textTexture = nullptr;
   }
   // Note: Do not destroy the font here, as it's managed by the Game class
}

void TextManager::display(SDL_Renderer* renderer, int, int) {
   int logicalWidth, logicalHeight;
   SDL_RendererLogicalPresentation mode;
   if (!SDL_GetRenderLogicalPresentation(renderer, &logicalWidth, &logicalHeight, &mode)) {
      SDL_Log("Failed to get logical presentation: %s", SDL_GetError());
      return;
   }

   float gui_height = logicalHeight / 3.0f;
   float gui_y = logicalHeight - gui_height;

   // Draw GUI backdrop
   SDL_FRect GUIBackdrop = { 0.0f, gui_y, static_cast<float>(logicalWidth), gui_height };
   SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue backdrop
   SDL_RenderFillRect(renderer, &GUIBackdrop);

   if (!font || !getText() || strlen(getText()) == 0) {
      SDL_Log("Font or text is null");
      return;
   }

   // Define text color (white)
   SDL_Color textColor = { 255, 255, 255, 255 };

   // Render text to a surface using TTF_RenderText_Solid_Wrapped
   SDL_Surface* textSurface = TTF_RenderText_Solid_Wrapped(font, getText(), 0, textColor, logicalWidth - 20);
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

   // Draw a line under the text in logical coordinates (as a UI element)
   SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White line
   SDL_RenderLine(renderer, 0, gui_y, logicalWidth, gui_y);

   // Clean up texture
   SDL_DestroyTexture(textTexture);
   textTexture = nullptr;
}

// If we are in here then we are in the menu
void TextManager::menuEvent(SDL_Event& event) {



   if (event.type == SDL_EVENT_KEY_DOWN) {
      switch (event.key.scancode)
      {
      case SDL_SCANCODE_A:
         SDL_Log("A Pressed");
         break;
      case SDL_SCANCODE_D:
         SDL_Log("D Pressed");
         break;
      case SDL_SCANCODE_SPACE:
         SDL_Log("Space Pressed");
         break;

      default:
         break;
      }
   }
}
