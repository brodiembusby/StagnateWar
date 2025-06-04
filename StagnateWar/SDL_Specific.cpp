#include "SDL_Specific.h"
#include "Game.h"
#include "constants.h"

SDL_AppResult SDL_Specific::SDL_AppInit(void** appstate, int argc, char* argv[]) {
   SDL_SetAppMetadata("Stagnate War", "1.0", "Stagnate War");

   if (!SDL_Init(SDL_INIT_VIDEO)) {
      SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
      return SDL_APP_FAILURE;
   }

   if (!SDL_CreateWindowAndRenderer("Stagnate War", WINDOW_HEIGHT, WINDOW_WIDTH, 0, &window, &renderer)) {
      SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
      return SDL_APP_FAILURE;
   }

   return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_Specific::SDL_AppEvent(void* appstate, SDL_Event* event) {
   if (event->type == SDL_EVENT_QUIT) {
      return SDL_APP_SUCCESS;
   }

   Game* game = static_cast<Game*>(appstate); // Cast directly from void* to Game*
   if (game) {
      game->handleEvent(*event);
   }

   return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_Specific::SDL_AppIterate(void* appstate) {
   
   Uint64 currentTick = SDL_GetTicks();
   deltaTime = (currentTick - lastTick) / 1000.0f; // Convert to seconds
   lastTick = currentTick;

   
   SDL_SetRenderDrawColor(renderer, 220, 220, 022, 255); // Black background
   SDL_RenderClear(renderer);

   Game* game = static_cast<Game*>(appstate);
   if (game) {
      game->render(*this);
   }

   SDL_RenderPresent(renderer);

   return SDL_APP_CONTINUE;
}

void SDL_Specific::SDL_AppQuit(void* appstate, SDL_AppResult result) {
   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);
   SDL_Quit();
}

void SDL_Specific::updateCamera(Position& target) {
   // Center the camera on the target (player)
   camera.setX(target.getX() - WINDOW_WIDTH / 2.0f);
   camera.setY(target.getY() - WINDOW_HEIGHT / 2.0f);

   // Optional: Clamp the camera to the game world boundaries
   if (camera.getX() < 0) {
      camera.setX(0);
   }
   if (camera.getY() < 0) {
      camera.setY(0);
   }
   if (camera.getX() > WORLD_WIDTH - WINDOW_WIDTH) {
      camera.setX(WORLD_WIDTH - WINDOW_WIDTH);
   }
   if (camera.getY() > WORLD_HEIGHT - WINDOW_HEIGHT) {
      camera.setY(WORLD_HEIGHT - WINDOW_HEIGHT);
   }
}


void SDL_Specific::renderSprite(SpriteSheet sprite, SDL_FRect rect) {
   
   SDL_SetRenderDrawColor(renderer, 100, 0, 0, 255); // Rect colors
   // Adjust the rectangle's position relative to the camera
   
   SDL_FRect adjustedRect = {
       rect.x - camera.getX(),
       rect.y - camera.getY(),
       rect.w,
       rect.h
   };
   
   
   //SDL_RenderTexture(renderer, sprite.getTexture(), nullptr, &adjustedRect);

   SDL_RenderRect(renderer, &adjustedRect);
}