#include "AssetFactory.h"
#include "Tile.h"


Entity* AssetFactory::createEntity(const std::string& name, Position pos) {
   // Look up entity data by name
   auto it = entities.find(name);
   if (it == entities.end()) {
      SDL_Log("Entity %s not found in entities", name.c_str());
      return nullptr;
   }
   EntityData& data = it->second;
   // Create entity based on type (PartyMember for player/enemy, Tile for tile)
   Entity* entity = nullptr;


   if (data.entityName == "player" || data.entityName == "enemy") {
      entity = new PartyMember();
   }
   else if (data.entityName == "tile") {
      entity = new Tile();
   }
   else {
      SDL_Log("Unknown entity entityName: %s", data.entityName.c_str());
      return nullptr;
   }
   // Set position and load texture, create sprite sheet
   if (entity) {
      entity->setPosition(pos.getX(), pos.getY());
      SDL_Texture* texture = loadTexture(data.textureName);
      if (texture) {
         SpriteSheet* spriteSheet = new SpriteSheet(texture, data.ssrows, data.sscolumns);
         entity->setSpriteSheet(spriteSheet);
      }
      else {
         SDL_Log("Failed to load texture for entity %s", name.c_str());
         delete entity;
         return nullptr;
      }
      // Add to entity manager and return
      entityManager.addEntity(name, entity);
      return entity;
   }
   return nullptr;
}

SDL_Texture* AssetFactory::loadTexture(const std::string& name) {
   auto it = texturePaths.find(name);
   if (it == texturePaths.end()) {
      SDL_Log("Texture %s not found in texturePaths", name.c_str());
      return nullptr;
   }
   SDL_Texture* texture = textureManager.getTexture(name);
   if (!texture) {
      texture = IMG_LoadTexture(renderer, it->second.c_str());
      if (!texture) {
         SDL_Log("Failed to load texture %s: %s", it->second.c_str(), SDL_GetError());
         return nullptr;
      }
      textureManager.addTexture(name, texture);
   }
   return texture;
}
