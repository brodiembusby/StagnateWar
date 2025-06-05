#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>
#include <string>

// Aspect Ration of 4:3
class SpriteSheet {
private:
   
   SDL_Surface* image;
   SDL_Rect mClip;

public:
   SpriteSheet() = default;

   //SpriteSheet(char const* path, int row, int column) {
   //   path = ;
   SpriteSheet(char const* path, int row, int column);
   ~SpriteSheet();

   void selectSprite(int x, int y);
   void drawSprite(SDL_Surface* windowSurface, SDL_Rect* position);


};