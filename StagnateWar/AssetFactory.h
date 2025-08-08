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
      std::string entityName;
      std::string textureName;
      int ssrows;
      int sscolumns;
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
      void removeEntity(const std::string& name) {
         auto it = entities.find(name);
         if (it != entities.end()) {
            delete it->second;
            entities.erase(it);
         }
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
      void removeTexture(const std::string& name) {
         auto it = textures.find(name);
         if (it != textures.end()) {
            SDL_DestroyTexture(it->second);
            textures.erase(it);
         }
      }
   };

   TextureManager textureManager;
   EntityManager entityManager;
   SDL_Renderer* renderer;
   

   std::unordered_map<std::string, EntityData> entities;
   std::unordered_map<std::string, std::string> texturePaths = {
       {"PlayerSpriteSheet", "assets/player.png"},
       {"badSoliderMAX", "assets/badSoliderMAX.png"},
       {"TileSpriteSheet", "assets/TileSpriteSheet.png"},
       {"defaultIcon", "assets/defaultIcon.png"},
       {"default", "assets/default.png"},
      {"playerWalk", "assets/sWalk.png"},

   };

public:
   AssetFactory(SDL_Renderer* r)
      : renderer(r),
      entities{
        {"player", {"player", "PlayerSpriteSheet", 1, 12}},
        {"enemy", {"enemy",  "badSoliderMAX", 1, 12}},
        {"tile", {"tile",  "TileSpriteSheet", 9, 9}},
      }
   {
   }

   SDL_Texture* loadTexture(const std::string& name);
   Entity* createEntity(const std::string& name, Position pos);
   Entity* getEntity(const std::string type) { return entityManager.getEntity(type); }
};



