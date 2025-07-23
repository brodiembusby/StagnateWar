#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "constants.h"

class TextManager {
public:
   TextManager(TTF_Font* font); 
   ~TextManager();

   void display(SDL_Renderer* renderer, const char* textToRender);

private:
   TTF_Font* font; 
   SDL_Texture* textTexture;
};