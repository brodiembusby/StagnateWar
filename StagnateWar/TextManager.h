#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>


class TextManager {
public:
   TextManager(TTF_Font* font);
   ~TextManager();
   void setText(std::string newText) { text = newText; }
   std::string getText() const { return text; };
   std::string menuEvent(SDL_Event& event);
   void renderMenu(SDL_Renderer* renderer, int logicalWidth, int logicalHeight);
   void display(SDL_Renderer* renderer, int logicalWidth, int logicalHeight, std::string option);

private:
   TTF_Font* font;
   SDL_Texture* textTexture;
   std::string text;
   int selectedIndex;
};