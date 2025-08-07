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

   std::string option = "default";

public:
   Game();
   ~Game();

   void gameQuit();
   void handleEvent(SDL_Event& event);
   SDL_AppResult Run();
   SDL_AppResult gameInit();
   SDL_AppResult gameIterate();
   

   void setEditorMode(bool mode) { isEditorMode = mode; }
   bool getEditorMode() const { return isEditorMode; }
   void setMenuing(bool menu) { isMenuing = menu; }
   bool getMenuing() const { return isMenuing; }
   void setShowCollisionText(bool show) { showCollisionText = show; }
   bool getShowCollisionText() const { return showCollisionText; }
   SDL_Renderer* getRenderer() const { return renderer; }
   SDL_Window* getWindow() const { return window; }
   float getDeltaTime() const { return deltaTime; }
   void updateCamera(Position& target);
   Entity* findEntity(const std::string& name);
   void setOption(const std::string& opt) { option = opt; }
   std::string getOption() const { return option; }

   std::tuple<int, int> getWindowSize() const;
};