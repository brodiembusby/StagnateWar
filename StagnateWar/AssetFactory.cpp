#include "AssetFactory.h"



Entity* AssetFactory::createEntity(const std::string& name) {
   auto it = entities.find(name);
   if (it == entities.end()) {
      SDL_Log("Entity %s not found in entities", name.c_str());
      return nullptr;
   }
   EntityData& data = it->second;
   Entity* entity = nullptr;
   if (data.type == "player") {
      entity = new PartyMember();
   }
   else if (data.type == "enemy") {
      entity = new PartyMember();
   }
   else {
      SDL_Log("Unknown entity type: %s", data.type.c_str());
      return nullptr;
   }
   if (entity) {
      entity->setPosition(data.position.getX(), data.position.getY());
      SDL_Texture* texture = loadTexture(data.textureName);
      if (texture) {
         SpriteSheet* spriteSheet = new SpriteSheet(texture, data.rows, data.columns);
         entity->setSpriteSheet(spriteSheet);
         entity->setSize(64, 64);
      }
      else {
         SDL_Log("Failed to load texture for entity %s", name.c_str());
         delete entity;
         return nullptr;
      }
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