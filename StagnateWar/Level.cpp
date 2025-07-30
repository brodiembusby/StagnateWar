#include "Level.h"
// Render the tiles in the level, adjusting for camera position.
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
// Render the grid lines for the level.
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

// Updates the tile at the mouse position when a mouse button is pressed.
// Takes camera offsets into account for correct grid placement.
void Level::updateTile(SDL_Event& event, float cameraX, float cameraY) {
   // Check for mouse button down event
   if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
      float mouseX, mouseY;
      SDL_GetMouseState(&mouseX, &mouseY);

      // Convert mouse position to grid coordinates, factoring in camera offset
      int gridX = static_cast<int>((mouseX + cameraX) / DEFAULT_WIDTH);
      int gridY = static_cast<int>((mouseY + cameraY) / DEFAULT_HEIGHT);

      // Validate grid coordinates
      if (gridX >= 0 && gridX < WIDTH && gridY >= 0 && gridY < HEIGHT) {
         // Delete any existing tile at this grid position
         delete level[gridX][gridY];
         level[gridX][gridY] = nullptr;

         // Ensure assetFactory is available
         if (!assetFactory) {
            SDL_Log("AssetFactory is null!");
            return; // Exit early to prevent crash
         }

         // Create a new tile entity using the asset factory
         level[gridX][gridY] = dynamic_cast<Tile*>(assetFactory->createEntity("tile"));
         if (level[gridX][gridY]) {
            Tile* tile = level[gridX][gridY];
            tile->setPosition(gridX * DEFAULT_WIDTH, gridY * DEFAULT_HEIGHT);
            tile->setIsWalkable(!isPlacingWall);
            tile->setRect(gridX * DEFAULT_WIDTH, gridY * DEFAULT_HEIGHT, DEFAULT_WIDTH, DEFAULT_HEIGHT);
         } else {
            SDL_Log("Failed to create or cast tile entity at: (%d, %d)", gridX, gridY);
         }
      } else {
         SDL_Log("Invalid grid coordinates: (%d, %d)", gridX, gridY);
      }
   }
}