#include "SDL_Specific.h"
#include "Game.h"

SDL_AppResult SDL_Specific::SDL_AppInit(void** appstate, int argc, char* argv[]) {
   SDL_SetAppMetadata("Stagnate War", "1.0", "SDL_DEMO");

   if (!SDL_Init(SDL_INIT_VIDEO)) {
      SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
      return SDL_APP_FAILURE;
   }

   if (!SDL_CreateWindowAndRenderer("Stagnate War", 640, 480, 0, &window, &renderer)) {
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
   SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
   SDL_RenderClear(renderer);

   Game* game = static_cast<Game*>(appstate);
   if (game) {
      game->render(*this);
   }

   SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red rectangle
   SDL_RenderPresent(renderer);

   return SDL_APP_CONTINUE;
}

void SDL_Specific::SDL_AppQuit(void* appstate, SDL_AppResult result) {
   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);
   SDL_Quit();
}

void SDL_Specific::renderSprite(SpriteSheet sprite, SDL_FRect rect) {
   SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
   SDL_RenderRect(renderer, &rect);
}