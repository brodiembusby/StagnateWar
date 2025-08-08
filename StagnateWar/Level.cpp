#include "Level.h"

// Sets a default tiles set in the background
Level::Level(AssetFactory* af) : assetFactory(af) {
   for (int x = 0; x < WIDTH; x++) {
      for (int y = 0; y < HEIGHT; y++) {
         level[x][y] = nullptr;
         if (assetFactory) {
            level[x][y] = dynamic_cast<Tile*>(assetFactory->createEntity("tile", (x, y)));
            if (level[x][y]) {
               Tile* tile = level[x][y];
               tile->setPosition(x * DEFAULT_WIDTH, y * DEFAULT_HEIGHT);
               tile->setIsWalkable(true); 
               tile->setRect(x * DEFAULT_WIDTH, y * DEFAULT_HEIGHT, DEFAULT_WIDTH, DEFAULT_HEIGHT);
               tile->getSpriteSheet()->selectCurrentSprite(0, 4); // Default grass no edges
            }
            else {
               SDL_Log("Failed to create tile at (%d, %d)", x, y);
               level[x][y] = new Tile(); // Fallback
               level[x][y]->setPosition(x * DEFAULT_WIDTH, y * DEFAULT_HEIGHT);
               level[x][y]->setIsWalkable(true);
               level[x][y]->setRect(x * DEFAULT_WIDTH, y * DEFAULT_HEIGHT, DEFAULT_WIDTH, DEFAULT_HEIGHT);
            }
         }
         else {
            level[x][y] = new Tile(); // Fallback if no assetFactory
            level[x][y]->setPosition(x * DEFAULT_WIDTH, y * DEFAULT_HEIGHT);
            level[x][y]->setIsWalkable(true);
            level[x][y]->setRect(x * DEFAULT_WIDTH, y * DEFAULT_HEIGHT, DEFAULT_WIDTH, DEFAULT_HEIGHT);
         }
      }
   }
}

void Level::editorEvent(SDL_Event& event) {

   if (event.type == SDL_EVENT_KEY_DOWN) {
      switch (event.key.scancode) {
      case SDL_SCANCODE_M:
         saveToFile("assets/map.json");
         break;
      case SDL_SCANCODE_L:
         loadFromFile("assets/map.json");
         break;
      }
   }
}

// Render the tiles in the level, adjusting for camera position.
void Level::renderTiles(SDL_Renderer* renderer, float cameraX, float cameraY) {
   for (int y = 0; y < HEIGHT; y++) {
      for (int x = 0; x < WIDTH; x++) {
         Tile* tile = level[x][y];
         if (tile) {
            SDL_FRect rect = tile->getRect();
            rect.x -= cameraX;
            rect.y -= cameraY;
            SpriteSheet* ss = tile->getSpriteSheet();
            if (ss) ss->drawSprite(renderer, rect);

         }
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

// Updates the tile at the mouse position when a mouse button is pressed.
// Takes camera offsets into account for correct grid placement.
void Level::updateTile(SDL_Event& event, float cameraX, float cameraY) {
   // Check for mouse button down event
   if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
      float mouseX, mouseY;
      SDL_GetMouseState(&mouseX, &mouseY);

      // Convert mouse position to grid coordinates, factoring in camera offset
      int gridX = static_cast<int>((mouseX + cameraX) / DEFAULT_WIDTH);
      int gridY = static_cast<int>((mouseY + cameraY) / DEFAULT_HEIGHT);

      // Validate grid coordinates
      if (gridX >= 0 && gridX < WIDTH && gridY >= 0 && gridY < HEIGHT) {
         // Delete any existing tile at this grid position
         delete level[gridX][gridY];
         level[gridX][gridY] = nullptr;

         // Ensure assetFactory is available
         if (!assetFactory) {
            SDL_Log("AssetFactory is null!");
            return; // Exit early to prevent crash
         }

         // Create a new tile entity using the asset factory
         level[gridX][gridY] = dynamic_cast<Tile*>(assetFactory->createEntity("tile", (gridX,gridY)));
         if (level[gridX][gridY]) {
            Tile* tile = level[gridX][gridY];
            tile->setPosition(gridX * DEFAULT_WIDTH, gridY * DEFAULT_HEIGHT);
            tile->setIsWalkable(!isPlacingWall);
            tile->setRect(gridX * DEFAULT_WIDTH, gridY * DEFAULT_HEIGHT, DEFAULT_WIDTH, DEFAULT_HEIGHT);
         }
         else {
            SDL_Log("Failed to create or cast tile entity at: (%d, %d)", gridX, gridY);
         }
      }
      else {
         SDL_Log("Invalid grid coordinates: (%d, %d)", gridX, gridY);
      }
   }
}

void Level::saveToFile(const std::string& filename) {
   nlohmann::json j;
   j["width"] = WIDTH;
   j["height"] = HEIGHT;
   j["tiles"] = nlohmann::json::array();

   for (int y = 0; y < HEIGHT; y++) {
      for (int x = 0; x < WIDTH; x++) {
         Tile* tile = level[x][y];
         nlohmann::json tileJson;
         tileJson["x"] = x;
         tileJson["y"] = y;
         tileJson["isWalkable"] = tile ? tile->getIsWalkable() : true;
         if (tile && tile->getSpriteSheet()) {
            tileJson["selectedTileX"] = tile->getSpriteSheet()->getClip().x;
            tileJson["selectedTileY"] = tile->getSpriteSheet()->getClip().y;
         }
         else {
            tileJson["selectedTileX"] = 0; // Default sprite index
            tileJson["selectedTileY"] = 4; // Default sprite index
         }
         j["tiles"].push_back(tileJson);
      }
   }
   std::ofstream file(filename);
   if (file.is_open()) {
      file << j.dump(4); // Pretty print with 4-space indent
      file.close();
      SDL_Log("Map saved to %s", filename.c_str());
   }
   else {
      SDL_Log("Failed to open file %s for saving", filename.c_str());
   }
}

void Level::loadFromFile(const std::string& filename) {
   std::ifstream file(filename);
   if (!file.is_open()) {
      SDL_Log("Failed to open file %s for loading", filename.c_str());
      return;
   }

   nlohmann::json j;
   try {
      file >> j;
      file.close();

      for (int x = 0; x < WIDTH; x++) {
         for (int y = 0; y < HEIGHT; y++) {
            delete level[x][y];
            level[x][y] = nullptr;
         }
      }

      // Load tiles
      for (const auto& tileJson : j["tiles"]) {
         int x = tileJson["x"].get<int>();
         int y = tileJson["y"].get<int>();
         bool isWalkable = tileJson["isWalkable"].get<bool>();
         int selectedTileX = tileJson.value("selectedTileX", 0); // Default to 0 if missing
         int selectedTileY = tileJson.value("selectedTileY", 4); // Default to 4 if missing

         if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT && assetFactory) {
            level[x][y] = dynamic_cast<Tile*>(assetFactory->createEntity("tile", (x, y)));
            if (level[x][y]) {
               Tile* tile = level[x][y];
               tile->setPosition(x * DEFAULT_WIDTH, y * DEFAULT_HEIGHT);
               tile->setIsWalkable(isWalkable);
               tile->setRect(x * DEFAULT_WIDTH, y * DEFAULT_HEIGHT, DEFAULT_WIDTH, DEFAULT_HEIGHT);
               if (tileSpriteSheet) {
                  tile->setSpriteSheet(tileSpriteSheet);
                  tile->getSpriteSheet()->selectCurrentSprite(selectedTileX, selectedTileY); // Use selectSprite
               }
            }
            else {
               SDL_Log("Failed to create tile at (%d, %d)", x, y);
               level[x][y] = new Tile(); // Fallback
               level[x][y]->setPosition(x * DEFAULT_WIDTH, y * DEFAULT_HEIGHT);
               level[x][y]->setIsWalkable(isWalkable);
               level[x][y]->setRect(x * DEFAULT_WIDTH, y * DEFAULT_HEIGHT, DEFAULT_WIDTH, DEFAULT_HEIGHT);
            }
         }
         else {
            SDL_Log("Invalid grid coordinates or assetFactory null at (%d, %d)", x, y);
         }
      }
      SDL_Log("Map loaded from %s", filename.c_str());
   }
   catch (const nlohmann::json::parse_error& e) {
      SDL_Log("JSON parse error: %s", e.what());
      file.close();
   }
}