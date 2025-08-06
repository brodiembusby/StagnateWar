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

   // SDL Components and Main Components
   SDL_Window* window = nullptr;
   SDL_Renderer* renderer = nullptr;
  
   TTF_Font* font = nullptr;
   TextManager* textManager = nullptr;
   Level* level = nullptr; 
   SpriteSheet* tileSpriteSheet = nullptr;
   AssetFactory* assetFactory = nullptr;

   std::vector<Entity*> entities;

   Position camera;
   Uint64 lastTick = 0;
   float deltaTime = 0.0f;

   // Flags
   bool showCollisionText = false; 
   bool isEditorMode = false;
   bool isMenuing = false; 

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
   Entity* findEntity(const std::string& name);

   std::tuple<int, int> getWindowSize() const;
};