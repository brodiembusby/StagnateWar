#pragma once
#include "PartyMember.h"
#include "Entity.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "TextManager.h"
#include "SpriteSheet.h"
#include "AssetFactory.h"
#include "Level.h"

/// <summary>
/// Game class that manages the game state, rendering, and input handling.
/// </summary>
class Game {
private:

   SDL_Window* window = nullptr;
   SDL_Renderer* renderer = nullptr;
  
   TTF_Font* font = nullptr;
   TextManager* textManager = nullptr;
   Level* level = nullptr; 

   Position camera;
   bool showCollisionText = false; 
   bool isEditorMode = false;
   float deltaTime = 0.0f;
   Uint64 lastTick = 0;

   SpriteSheet* tileSpriteSheet = nullptr;
protected:

   TextureManager textureManager;
   EntityManager entityManager;
   AssetFactory* assetFactory = nullptr;

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

   std::tuple<int, int> getWindowSize() const {
      int width, height;
      if (!SDL_GetWindowSize(window, &width, &height)) {
         SDL_Log("Failed to get window size: %s", SDL_GetError());
         width = 640; // Fallback default
         height = 480;
      }
      return std::make_tuple(width, height);
   }
};