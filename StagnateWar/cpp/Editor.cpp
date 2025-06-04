#include "Editor.h"

void Editor::renderGrid(SDL_Specific& sdl) {
   // Render grid first 2000 / 50 = 40  (40,40)
   SDL_SetRenderDrawColor(sdl.getRenderer(), 255, 255, 255, 255); // Gray grid lines

   for (int x = 0; x < 40; x++) {

      SDL_RenderLine(sdl.getRenderer(), x * 50, 0, x * 50, WORLD_HEIGHT);

   }
   for (int y = 0; y < 40; y++) {

      SDL_RenderLine(sdl.getRenderer(), 0, y * 50, WORLD_WIDTH, y * 50);

   }

}

void Editor::updateTile(SDL_Event& event) {
   if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
      // Get mouse position
      float mouseX, mouseY;
      SDL_GetMouseState(&mouseX, &mouseY);

      // Convert mouse position to grid coordinates
      int gridX = mouseX / 50; // 800 / 50 = 16 columns
      int gridY = mouseY / 50; // 600 / 50 = 12 rows

      // Ensure the click is within bounds
      if (gridX >= 0 && gridX < 16 && gridY >= 0 && gridY < 12) {
         // Delete any existing tile at this position
         delete level[gridX][gridY];

         // Create a new tile
         level[gridX][gridY] = new Tile();
         level[gridX][gridY]->setIsWalkable(!isPlacingWall);
         level[gridX][gridY]->getRect() = SDL_FRect{ (float)(gridX * 50), (float)(gridY * 50), 50, 50 };
         level[gridX][gridY]->getSprite() = isPlacingWall ? wallSprite : defaultSprite;
      }
   }
   else if (event.type == SDL_EVENT_KEY_DOWN) {
      // Toggle between placing walkable (grass) and non-walkable (wall) tiles
      if (event.key.scancode == SDL_SCANCODE_T) {
         isPlacingWall = !isPlacingWall;
         SDL_Log("Placing %s tiles", isPlacingWall ? "wall" : "grass");
      }
   }
}