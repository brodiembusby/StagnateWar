#pragma once
#include <SDL3/SDL.h>
#include "SpriteSheet.h"

class Game; // Forward declaration

class SDL_Specific {
private:
   SDL_Window* window = nullptr;
   SDL_Renderer* renderer = nullptr;
   float deltaTime = 0.0f;
   Uint64 lastTick = 0;

public:
   SDL_Specific() = default;
   ~SDL_Specific() { SDL_AppQuit(nullptr, SDL_APP_SUCCESS); }

   SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]);
   SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event);
   SDL_AppResult SDL_AppIterate(void* appstate);
   void SDL_AppQuit(void* appstate, SDL_AppResult result);

   void renderSprite(SpriteSheet sprite, SDL_FRect rect);

   SDL_Renderer* getRenderer() const { return renderer; }
};