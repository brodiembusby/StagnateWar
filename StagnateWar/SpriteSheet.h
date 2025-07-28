#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>
#include <string>

// Sprite is 32x32 pixels 
// ODO:
class SpriteSheet {
private:
   
   SDL_Texture* image;
   SDL_FRect mClip;

public:
   SpriteSheet() = default;

   //SpriteSheet(char const* path, int row, int column) {
   //   path = ;
   SpriteSheet(char const* path, int row, int column);
   ~SpriteSheet();

   SDL_Texture* getTexture() const { return image; }
    SDL_FRect& getClip()  { return mClip; }
   void selectSprite(int x, int y);
   void drawSprite(SDL_Texture* windowSurface, SDL_Rect* position);


};