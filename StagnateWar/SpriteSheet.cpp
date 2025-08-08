#include "SpriteSheet.h"
#include <string>
// https://dev.to/noah11012/using-sdl2-spritesheets-46h5

SpriteSheet::SpriteSheet(SDL_Texture* tex, int rows, int columns) : texture(tex) {
   
   float texWidth , texHeight ;
   SDL_GetTextureSize(texture, &texWidth, &texHeight);
   clip.w = static_cast<float>(texWidth) / columns;
   clip.h = static_cast<float>(texHeight) / rows;
   clip.x = 0.0f;
   clip.y = 0.0f;
}
// x is column and y is the row
void SpriteSheet::selectCurrentSprite(int x, int y)
{
   clip.x = x * clip.w;
   clip.y = y * clip.h;

}

void SpriteSheet::drawSprite(SDL_Renderer* renderer, SDL_FRect& rect){

   SDL_RenderTexture(renderer, texture, &clip, &rect);
}

void SpriteSheet::drawSpriteRotated(SDL_Renderer* renderer,SDL_Texture* texture, SDL_FRect& rect, SDL_FlipMode flip) {
  
   SDL_RenderTextureRotated(renderer, texture, &clip, &rect, 0.0f, nullptr, flip);
}