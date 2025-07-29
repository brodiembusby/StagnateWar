#pragma once
#include <unordered_map>
#include <SDL3/SDL.h>
#include "Entity.h"
#include "PartyMember.h"  
#include "Position.h"
#include <SDL3_image/SDL_image.h>
/// <summary>
/// Holds and manages all entities in the game.
/// </summary>
struct EntityManager {
  
  std::unordered_map<std::string, Entity*> entities;
   ~EntityManager() {
      for (auto& pair : entities) {
         delete pair.second;
      }
      entities.clear();
   }
   void addEntity(const std::string& name, Entity* entity) {
      entities[name] = entity;
   }
   Entity* getEntity(const std::string& name) {
      auto it = entities.find(name);
      return (it != entities.end()) ? it->second : nullptr;
   }
};
/// <summary>
/// Manages a collection of SDL_Texture pointers, allowing textures to be added, 
/// retrieved by name, and properly destroyed when the manager is destructed.
/// </summary>
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




struct EntityData {
    std::string type;
    Position position;
    std::string textureName;
    int rows;
    int columns;
};

/// <summary>
/// A factory class responsible for loading textures and creating entities using 
/// provided managers and renderer. Right now it doesn't help much but it will in the future.
/// </summary>

class AssetFactory
{
private:
   TextureManager& textureManager;
   EntityManager& entityManager;
   SDL_Renderer* renderer;
   int spriteSheetRC = 9;
  
   std::unordered_map<std::string, EntityData> entities;
   std::unordered_map<std::string, std::string> texturePaths = {
       {"ArmySpriteSheet", "assets/ArmySpriteSheet.png"},
       {"TileSpriteSheet", "assets/TileSpriteSheet.jpg"},
       {"defaultIcon", "assets/defaultIcon.png"},
       {"default", "assets/default.png"}
   };

public:
   
   AssetFactory(TextureManager& tm, EntityManager& em, SDL_Renderer* r)
      : textureManager(tm), entityManager(em), renderer(r),
      entities{
          {"player", {"player", Position(100.0f, 100.0f), "ArmySpriteSheet", spriteSheetRC, spriteSheetRC}},
          {"enemy", {"enemy", Position(200.0f, 200.0f), "ArmySpriteSheet", spriteSheetRC, spriteSheetRC}}
      } {
   }


   SDL_Texture* loadTexture(const std::string& name);
   Entity* createEntity(const std::string& name);
   Entity& getEntity(const std::string& name);


};