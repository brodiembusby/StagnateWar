#include "Level.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "sprites.h"

namespace StagnateWar {

   Level::~Level() {
      for (int x = 0; x < WIDTH; x++) {
         for (int y = 0; y < HEIGHT; y++) {
            if (level[x][y] != nullptr) {
               delete level[x][y];
               level[x][y] = nullptr;
            }
         }
      }
   }

   std::vector<std::vector<int>> ReadCSV(std::istream& str) {
      std::vector<std::vector<int>> result;
      std::string line;
      size_t rowIndex = 0;
      while (std::getline(str, line)) {
         std::vector<int> row;
         std::stringstream ss(line);
         std::string token;
         while (std::getline(ss, token, ',')) {
            try {
               row.push_back(std::stoi(token));
            }
            catch (const std::exception& e) {
               SDL_Log("Invalid CSV value in row %zu: %s, defaulting to 0", rowIndex, token.c_str());
               row.push_back(0); // Default to GrassPlain
            }
         }
         if (!row.empty()) {
            std::string rowStr;
            for (int val : row) {
               rowStr += std::to_string(val) + ", ";
            }
            if (!rowStr.empty()) rowStr.pop_back();
            //SDL_Log("Parsed Row %zu: %s", rowIndex, rowStr.c_str());
            result.push_back(row);
            ++rowIndex;
         }
      }
      return result;
   }
   Level::Level(const std::string& filename, AssetFactory* af, SpriteSheet* ts) : assetFactory(af), tileSpriteSheet(ts) {

      if (!assetFactory) {
         SDL_Log("AssetFactory is null in Level constructor");
      }
      if (!tileSpriteSheet) {
         SDL_Log("tileSpriteSheet is null in Level constructor");
      }
      // Load Level
      if (!filename.empty()) {
         SDL_Log("Loading level from file: %s", filename.c_str());
         loadFromFile(filename);
      }
      // If no filename is provided, initialize a blank default level
      else {
         SDL_Log("No filename provided, initializing default level");
         for (int x = 0; x < WIDTH; x++) {
            for (int y = 0; y < HEIGHT; y++) {
               level[x][y] = nullptr;
               level[x][y] = dynamic_cast<Tile*>(assetFactory->createEntity("tile", Position(static_cast<float>(x), static_cast<float>(y))));
               if (level[x][y]) {
                  setDefaultTile(x, y); // Set default tile properties
               }
               else {
                  SDL_Log("Failed to create tile at (%d, %d), using default", x, y);
               }
            }
         }
      }
   }


   void Level::editorEvent(SDL_Event& event) {

      if (event.type == SDL_EVENT_KEY_DOWN) {
         switch (event.key.scancode) {

         case SDL_SCANCODE_L:
            loadFromFile("assets/Basic_Bottom.csv");
            break;
         }
      }
   }

   // In Level::renderTiles, add a null check before dereferencing 'tile'
   void Level::renderTiles(SDL_Renderer* renderer, float cameraX, float cameraY) {
      for (int y = 0; y < HEIGHT; y++)
      {
         for (int x = 0; x < WIDTH; x++)
         {
            Tile* tile = level[x][y];
            if (!tile) {
               SDL_Log("Null tile at (%d, %d)", x, y);
               continue; // Prevent dereferencing a null pointer
            }
            SpriteSheet* ss = tile->getSpriteSheet();
            if (!ss)   SDL_Log("No sprite sheet for tile at (%d, %d)", x, y);
            SDL_FRect rect = tile->getRect();
            rect.x -= cameraX;
            rect.y -= cameraY;
            ss->selectCurrentSprite(static_cast<int>(tile->getSpriteX()), static_cast<int>(tile->getSpriteY()));
            ss->drawSprite(renderer, rect);
         }
      }
   }

   // Render the grid lines for the level.
   void Level::renderGrid(SDL_Renderer* renderer, float cameraX, float cameraY) {

      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

      for (float x = 0; x <= WORLD_WIDTH; x += DEFAULT_WIDTH) {
         SDL_RenderLine(renderer, x - cameraX, 0 - cameraY, x - cameraX, WORLD_HEIGHT - cameraY);
      }
      for (float y = 0; y <= WORLD_HEIGHT; y += DEFAULT_HEIGHT) {
         SDL_RenderLine(renderer, 0 - cameraX, y - cameraY, WORLD_WIDTH - cameraX, y - cameraY);
      }

   }

   void Level::loadFromFile(const std::string& filename) {
      std::ifstream file(filename);
      if (!file.is_open()) {
         SDL_Log("Failed to open file %s for loading", filename.c_str());
         return;
      }

      std::vector<std::vector<int>> levelData = ReadCSV(file);
      file.close();

      for (int y = 0; y < std::min(HEIGHT, static_cast<int>(levelData.size())); y++) {
         for (int x = 0; x < std::min(WIDTH, static_cast<int>(levelData[y].size())); x++) {
            int spriteId = levelData[y][x];
            auto it = Sprites::SpriteMap.find(spriteId);
            if (it != Sprites::SpriteMap.end() && assetFactory) {
               level[x][y] = dynamic_cast<Tile*>(assetFactory->createEntity("tile", Position(static_cast<float>(x), static_cast<float>(y))));
               if (!level[x][y]) {
                  SDL_Log("Failed to create tile at (%d, %d)", x, y);
                  setDefaultTile(x, y);
                  continue;
               }
               Tile* tile = level[x][y];
               tile->setPosition(x * DEFAULT_WIDTH, y * DEFAULT_HEIGHT);
               tile->setIsWalkable(it->second.isWalkable);
               tile->setRect(x * DEFAULT_WIDTH, y * DEFAULT_HEIGHT, DEFAULT_WIDTH, DEFAULT_HEIGHT);
               tile->setSpriteSheet(tileSpriteSheet);
               tile->setSpriteCoords(it->second.sprite.x, it->second.sprite.y); // Store sprite coords

            }
            else {
               SDL_Log("Invalid spriteId %d at (%d, %d), using default", spriteId, x, y);
               setDefaultTile(x, y);
            }
         }
      }
      SDL_Log("Map loaded from %s", filename.c_str());
   }

   void Level::setDefaultTile(int x, int y) {
      level[x][y] = new Tile();
      level[x][y]->setPosition(x * DEFAULT_WIDTH, y * DEFAULT_HEIGHT);
      level[x][y]->setIsWalkable(true);
      level[x][y]->setRect(x * DEFAULT_WIDTH, y * DEFAULT_HEIGHT, DEFAULT_WIDTH, DEFAULT_HEIGHT);
      level[x][y]->setSpriteSheet(tileSpriteSheet);
      level[x][y]->setSpriteCoords(Sprites::GrassPlain.x, Sprites::GrassPlain.y);

   }

}