#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class SpriteSheet {
private:
   SDL_Texture* texture; 
   SDL_FRect clip;
   SDL_FlipMode flipMode = SDL_FLIP_NONE;
   

public:
  
   SpriteSheet(SDL_Texture* tex, int rows, int columns);
   void selectCurrentSprite(int x, int y);
   void drawSprite(SDL_Renderer* renderer,  SDL_FRect& rect) ;
   void drawSpriteRotated(SDL_Renderer* renderer, SDL_Texture* texture, SDL_FRect& rect, SDL_FlipMode flip = SDL_FLIP_NONE);
   const SDL_FRect& getClip() const { return clip; }
   SDL_Texture* getTexture() const { return texture; }
   void setTexture(SDL_Texture* tex) { texture = tex; }
   void setFlipMode(SDL_FlipMode flip) { flipMode = flip; }
   SDL_FlipMode getFlipMode() const { return flipMode; }
   

};