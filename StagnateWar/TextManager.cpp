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

void TextManager::display(SDL_Renderer* renderer, int window_width, int window_height) {
   
   float gui_height = window_height / 3.0f;
   float gui_y = window_height - gui_height;

   // Draw GUI backdrop
   SDL_FRect GUIBackdrop = { 0.0f, gui_y, window_width, gui_height };
   SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue backdrop
   SDL_RenderFillRect(renderer, &GUIBackdrop);

   if (!font || !getText() || strlen(getText()) == 0) {
      SDL_Log("Font or text is null");
      return;
   }

   // Define text color (white)
   SDL_Color textColor = { 255, 255, 255, 255 };

   // Render text to a surface using TTF_RenderText_Solid_Wrapped
   SDL_Surface* textSurface = TTF_RenderText_Solid_Wrapped(font, getText(), 0, textColor, window_width - 20);
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

   // Define destination rectangle for text with padding, anchored relative to GUI backdrop
   float text_padding = 10.0f; // Padding from edges of the backdrop
   SDL_FRect textRect = {
       text_padding,
       gui_y + text_padding,
       static_cast<float>(window_width) - 2 * text_padding,
       gui_height - 2 * text_padding
   };

   // Render the text texture
   if (!SDL_RenderTexture(renderer, textTexture, nullptr, &textRect)) {
      SDL_Log("Failed to render text texture: %s", SDL_GetError());
   }

   // Clean up texture
   SDL_DestroyTexture(textTexture);
   textTexture = nullptr;
}