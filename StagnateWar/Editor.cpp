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

}