#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class SpriteSheet {
private:
   SDL_Texture* texture; // Does not own the texture
   SDL_FRect clip; // Current clip rectangle for the selected sprite

public:
   SpriteSheet(SDL_Texture* tex, int rows, int columns);
   void selectSprite(int x, int y);
   void drawSprite(SDL_Renderer* renderer,  SDL_FRect& rect) ;
   const SDL_FRect& getClip() const { return clip; }
};