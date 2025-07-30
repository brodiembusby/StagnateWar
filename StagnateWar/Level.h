#pragma once
#include "Tile.h"
#include <SDL3/SDL.h>

class Level {
private:
   static const int WIDTH = 16;
   static const int HEIGHT = 12;
   Tile* level[WIDTH][HEIGHT];
   bool isPlacingWall = false;

public:
   Level();
   ~Level();
   Tile* getTile(int x, int y);
   void setTile(int x, int y, Tile* tile);
   void renderTiles(SDL_Renderer* renderer, float cameraX, float cameraY);
   void renderGrid(SDL_Renderer* renderer);
   void updateTile(SDL_Event& event);


};