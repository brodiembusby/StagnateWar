#include "SpriteSheet.h"
// https://dev.to/noah11012/using-sdl2-spritesheets-46h5

SpriteSheet::SpriteSheet(SDL_Texture* tex, int rows, int columns) : texture(tex) {
   
   float texWidth , texHeight ;
   SDL_GetTextureSize(texture, &texWidth, &texHeight);
   clip.w = static_cast<float>(texWidth) / columns;
   clip.h = static_cast<float>(texHeight) / rows;
   clip.x = 0.0f;
   clip.y = 0.0f;
}

void SpriteSheet::selectSprite(int x, int y)
{
   clip.x = x * clip.w;
   clip.y = y * clip.h;

}

void SpriteSheet::drawSprite(SDL_Renderer* renderer, SDL_FRect& rect){

   SDL_RenderTexture(renderer, texture, &clip, &rect);
}
