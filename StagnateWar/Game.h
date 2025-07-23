#pragma once
#include "PartyMember.h"
#include "Entity.h"
#include "Editor.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "TextManager.h"

class Game {
private:

   SDL_Window* window = nullptr;
   SDL_Renderer* renderer = nullptr;
  
   TTF_Font* font = nullptr;
   TextManager* textManager = nullptr; // Add TextManager


   Position camera;

   // TODO: Temp will be moved later
   SDL_Texture* playerTexture = nullptr;
   PartyMember* player = nullptr;

   bool isEditorMode = false;
   float deltaTime = 0.0f;
   Uint64 lastTick = 0;

public:
   Game();
   ~Game();

   void gameQuit();
   void handleEvent(SDL_Event& event);
   SDL_AppResult Run();
   SDL_AppResult gameInit();
   SDL_AppResult gameIterate();
   
   float getDeltaTime() const { return deltaTime; }
   void updateCamera(Position& target);

};