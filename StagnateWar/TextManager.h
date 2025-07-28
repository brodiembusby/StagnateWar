#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "constants.h"

class TextManager {
public:
   TextManager(TTF_Font* font); 
   ~TextManager();

   void display(SDL_Renderer* renderer);
   void setText(const char* text) { this->text = text; }
   const char* getText() { return text; }

private:
   TTF_Font* font; 
   SDL_Texture* textTexture;
   const char* text;
};