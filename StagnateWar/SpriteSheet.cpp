#include "SpriteSheet.h"
// https://dev.to/noah11012/using-sdl2-spritesheets-46h5

//SpriteSheet::SpriteSheet(char const* path, int row, int column) {
//
//   image = IMG_LoadTexture(sdl.getRender(), path);
//
//   mClip.w = image->w / column;
//   mClip.h = image->h / row;
//}
//
//SpriteSheet::~SpriteSheet()
//{
//   SDL_DestroyTexture(image);
//}
//
//void SpriteSheet::selectSprite(int x, int y)
//{
//   mClip.x = x * mClip.w;
//   mClip.y = y * mClip.h;
//
//}

//void SpriteSheet::drawSprite(SDL_Texture* windowSurface, SDL_Rect* rect){
//
//   SDL_BlitSurface(image, &mClip, windowSurface, rect);
//
//}
#include "SpriteSheet.h"

//SpriteSheet::SpriteSheet() : texture(nullptr) {}
//SpriteSheet::~SpriteSheet() { if (texture) { SDL_DestroyTexture(texture); texture = nullptr; } }