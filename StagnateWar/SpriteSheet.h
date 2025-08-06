#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class SpriteSheet {
private:
   SDL_Texture* texture; 
   SDL_FRect clip;

public:
  
   SpriteSheet(SDL_Texture* tex, int rows, int columns);
   void selectCurrentSprite(int x, int y);
   int getSpriteIndexX() { return clip.x; }
   int getSpriteIndexY() { return  clip.y; }
   void setSpriteIndexX(int x) {  x =clip.x; }
   void setSpriteIndexY(int y) {   y = clip.y; }
   void drawSprite(SDL_Renderer* renderer,  SDL_FRect& rect) ;
   const SDL_FRect& getClip() const { return clip; }
   SDL_Texture* getTexture() const { return texture; }
   void setTexture(SDL_Texture* tex) { texture = tex; }
};