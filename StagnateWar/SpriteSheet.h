#pragma once
#include <SDL3/SDL.h>
#include <vector>

class SpriteSheet {
private:
   std::vector<SDL_Texture*> sprites; // Fixed to pointer for SDL_Texture

public:
   SpriteSheet() = default;
};