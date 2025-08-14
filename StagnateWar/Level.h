#pragma once
#include <SDL3/SDL.h>
#include "Entity.h"
#include "Tile.h"
#include "AssetFactory.h"
#include "sprites.h"
namespace StagnateWar {
   class Level : public Entity {
   private:
      static const int WIDTH = 30;
      static const int HEIGHT = 20;
      Tile* level[WIDTH][HEIGHT];
      bool isPlacingWall = false;
      SpriteSheet* tileSpriteSheet = nullptr;
      AssetFactory* assetFactory = nullptr;
      int currentSpriteId = 0; // Current sprite ID for tile editing

   public:

      Level(const std::string& filename, AssetFactory* af, SpriteSheet* ts); // Updated constructor
      ~Level();

      void setAssetFactory(AssetFactory* af) { assetFactory = af; }
      void renderTiles(SDL_Renderer* renderer, float cameraX, float cameraY);
      void renderGrid(SDL_Renderer* renderer, float cameraX, float cameraY);
      void loadFromFile(const std::string& filename);
      void editorEvent(SDL_Event& event);
      void setCurrentSpriteId(int id) { currentSpriteId = id; }
      void setDefaultTile(int x, int y);

   };
}