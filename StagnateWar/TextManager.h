#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "constants.h"

class TextManager {
public:
   TextManager(TTF_Font* font);
   ~TextManager();

   void display(SDL_Renderer* renderer, int window_width, int window_height);
   void setText(const char* text) { this->text = text; }
   const char* getText() { return text; }
   void menuEvent(SDL_Event& event);

private:
   TTF_Font* font;
   SDL_Texture* textTexture;
   //SDL_Rect textRect;
   const char* text;
};