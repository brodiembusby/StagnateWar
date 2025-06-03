#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "SDL_Specific.h"
#include "Game.h"

SDL_Specific sdl;
Game* game = nullptr;

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
   SDL_AppResult result = sdl.SDL_AppInit(appstate, argc, argv);
   if (result == SDL_APP_CONTINUE) {
      game = new Game(sdl);
      *appstate = game; // Store the Game pointer in appstate
   }
   return result;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
   return sdl.SDL_AppEvent(appstate, event);
}

SDL_AppResult SDL_AppIterate(void* appstate) {
   return sdl.SDL_AppIterate(appstate);
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
   sdl.SDL_AppQuit(appstate, result);
   delete game;
}