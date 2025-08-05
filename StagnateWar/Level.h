#pragma once
#include "Tile.h"
#include <SDL3/SDL.h>
#include "Entity.h"
#include "AssetFactory.h"  
#include "json.hpp"
#include <fstream>
#include <string>

class Level : public Entity {
private:
   static const int WIDTH = 16;
   static const int HEIGHT = 12;
   Tile* level[WIDTH][HEIGHT];
   bool isPlacingWall = false;
   SpriteSheet* tileSpriteSheet = nullptr;
   AssetFactory* assetFactory = nullptr; 

public:
  
   Level(AssetFactory* af = nullptr) : assetFactory(af) {
      for (int x = 0; x < WIDTH; x++) {
         for (int y = 0; y < HEIGHT; y++) {
            level[x][y] = nullptr;
         }
      }
   }

   ~Level() {
      for (int x = 0; x < WIDTH; x++) {
         for (int y = 0; y < HEIGHT; y++) {
            delete level[x][y];
         }
      }
      // Note: tileSpriteSheet is deleted in Game::gameQuit
   }
   void setAssetFactory(AssetFactory* af) {
      assetFactory = af;
      SDL_Log("AssetFactory set in Level: %p", assetFactory);
   }
   void renderTiles(SDL_Renderer* renderer, float cameraX, float cameraY);
   void renderGrid(SDL_Renderer* renderer);
   void updateTile(SDL_Event& event, float cameraX, float cameraY); // Add camera parameters
   void saveToFile(const std::string& filename);
   void loadFromFile(const std::string& filename);
};