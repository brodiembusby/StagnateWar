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

void TextManager::display(SDL_Renderer* renderer) {
   // Draw GUI backdrop
   SDL_FRect GUIBackdrop = { 0.0f, 320.0f, WINDOW_WIDTH, WINDOW_HEIGHT / 3.0f };
   SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue backdrop
   SDL_RenderFillRect(renderer, &GUIBackdrop);

   if (!font || !getText() || strlen(getText()) == 0) {
      SDL_Log("Font or text is null");
      return;
   }

   // Define text color (white)
   SDL_Color textColor = { 255, 255, 255, 255 };

   // Render text to a surface using TTF_RenderText_Solid_Wrapped
   SDL_Surface* textSurface = TTF_RenderText_Solid_Wrapped(font, getText(), 0, textColor, WINDOW_WIDTH - 20);
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

   // Define destination rectangle to fill the backdrop (with padding)
   SDL_FRect textRect = { 10.0f, 330.0f, WINDOW_WIDTH - 20.0f, (WINDOW_HEIGHT / 3.0f) - 20.0f };

   // Render the text texture
   if (!SDL_RenderTexture(renderer, textTexture, nullptr, &textRect)) {
      SDL_Log("Failed to render text texture: %s", SDL_GetError());
   }

   // Clean up texture
   SDL_DestroyTexture(textTexture);
   textTexture = nullptr;
}
