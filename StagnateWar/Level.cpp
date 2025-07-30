#include "Level.h"

Level::Level() {
   for (int y = 0; y < HEIGHT; y++) {
      for (int x = 0; x < WIDTH; x++) {
         level[x][y] = nullptr;
      }
   }
}

Level::~Level() {
   for (int y = 0; y < HEIGHT; y++) {
      for (int x = 0; x < WIDTH; x++) {
         delete level[x][y];
         level[x][y] = nullptr;
      }
   }
}

Tile* Level::getTile(int x, int y) {
   if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
      return level[x][y];
   }
   return nullptr;
}

void Level::setTile(int x, int y, Tile* tile) {
   if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
      delete level[x][y];
      level[x][y] = tile;
      if (tile) {
         tile->setPosition(x * 32.0f, y * 32.0f);
         tile->getRect() = SDL_FRect{ (float)(x * 32), (float)(y * 32), 32.0f, 32.0f };
      }
   }
}

void Level::renderTiles(SDL_Renderer* renderer, float cameraX, float cameraY) {
   for (int y = 0; y < HEIGHT; y++) {
      for (int x = 0; x < WIDTH; x++) {
         Tile* tile = level[x][y];
         if (tile) {
            SDL_FRect rect = tile->getRect();
            rect.x -= cameraX;
            rect.y -= cameraY;
            SpriteSheet* ss = tile->getSpriteSheet();
            if (ss) {
               ss->drawSprite(renderer, rect);
            }
         }
      }
   }
}
void Level::renderGrid(SDL_Renderer* renderer) {
   // Render grid first 2000 / 50 = 40  (40,40)
   SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Gray grid lines

   for (int x = 0; x < 40; x++) {

      SDL_RenderLine(renderer, x * DEFAULT_WIDTH, 0, x * DEFAULT_WIDTH, WORLD_HEIGHT);

   }
   for (int y = 0; y < 40; y++) {

      SDL_RenderLine(renderer, 0, y * DEFAULT_HEIGHT, WORLD_WIDTH, y * DEFAULT_HEIGHT);

   }

}

void Level::updateTile(SDL_Event& event) {



   if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
      //   // Get mouse position
      float mouseX, mouseY;
      SDL_GetMouseState(&mouseX, &mouseY);
      SDL_Log("Mouse clicked at: (%f, %f)", mouseX, mouseY);

      int gridX = mouseX / 32; // 800 / 32 = 16 columns
      int gridY = mouseY / 32; // 600 / 32 = 12 rows

      SDL_Log("Grid mouse clicked at: (%d, %d)", gridX, gridY);

      // Working on this
      if (gridX >= 0 && gridX < 16 && gridY >= 0 && gridY < 12) {

         delete level[gridX][gridY];

         level[gridX][gridY] = new Tile();
         Tile* tile = level[gridX][gridY];
         tile->setPosition(gridX * DEFAULT_WIDTH, gridY * DEFAULT_HEIGHT);
         tile->setIsWalkable(!isPlacingWall);
         tile->getRect() = SDL_FRect{ (float)(gridX * DEFAULT_WIDTH), (float)(gridY * DEFAULT_HEIGHT), DEFAULT_WIDTH, DEFAULT_HEIGHT };
      }



   }
}

