#pragma once
#include "Position.h"
#include "SpriteSheet.h"
#include "Tile.h"
#include "SDL_Specific.h"
class Level
{
private:
   
   std::vector<Position> spawnPoints;
   std::vector<Tile*> tiles;
   SpriteSheet backgroundSprite; // Optional background

public:
   
   void loadLevel(); // Placeholder
   void render(SDL_Specific& sdl) {
      //// Render background first
      //SDL_FRect bgRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
      //sdl.renderSprite(backgroundSprite, bgRect);
      //// Render tiles
      //for (Tile* tile : tiles) {
      //   sdl.renderSprite(tile->getSprite(), tile->getRect());
      //}
   }
};
