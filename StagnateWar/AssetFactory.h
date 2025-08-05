#pragma once
#include <unordered_map>
#include <SDL3/SDL.h>
#include "Entity.h"
#include "PartyMember.h"  
#include "Position.h"
#include <SDL3_image/SDL_image.h>

class AssetFactory
{
private:
   struct EntityData {
      std::string type;
      Position position;
      std::string textureName;
      int rows;
      int columns;
   };

   struct EntityManager {
      std::unordered_map<std::string, Entity*> entities;
      ~EntityManager() {
         for (auto& pair : entities) {
            delete pair.second;
         }
         entities.clear();
      }
      void addEntity(const std::string& name, Entity* entity) { entities[name] = entity; }
      Entity* getEntity(const std::string& name) {
         auto it = entities.find(name);
         return (it != entities.end()) ? it->second : nullptr;
      }
   };

   struct TextureManager {
      std::unordered_map<std::string, SDL_Texture*> textures;
      ~TextureManager() {
         for (auto& pair : textures) {
            SDL_DestroyTexture(pair.second);
         }
         textures.clear();
      }
      void addTexture(const std::string& name, SDL_Texture* texture) {
         textures[name] = texture;
      }
      SDL_Texture* getTexture(const std::string& name) {
         auto it = textures.find(name);
         return (it != textures.end()) ? it->second : nullptr;
      }
   };

   TextureManager textureManager;
   EntityManager entityManager;
   SDL_Renderer* renderer;
   int spriteSheetRC = 9;
  
   std::unordered_map<std::string, EntityData> entities;
   std::unordered_map<std::string, std::string> texturePaths = {
       {"ArmySpriteSheet", "assets/ArmySpriteSheet.png"},
       {"TileSpriteSheet", "assets/TileSpriteSheet.png"},
       {"defaultIcon", "assets/defaultIcon.png"},
       {"default", "assets/default.png"}
   };

public:
   AssetFactory(SDL_Renderer* r)
      : renderer(r),
        entities{
          {"player", {"player", Position(100.0f, 100.0f), "ArmySpriteSheet", spriteSheetRC, spriteSheetRC}},
          {"enemy", {"enemy", Position(200.0f, 200.0f), "ArmySpriteSheet", spriteSheetRC, spriteSheetRC}},
          {"tile", {"tile", Position(0.0f, 0.0f), "TileSpriteSheet", spriteSheetRC, spriteSheetRC}}
        }
   {
   }

   SDL_Texture* loadTexture(const std::string& name);
   Entity* createEntity(const std::string& name);
   Entity* getEntity(const std::string& name) { return entityManager.getEntity(name); }
};