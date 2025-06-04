#pragma once
#include "SDL_Specific.h"
#include "PartyMember.h"
#include <vector>
#include "Object.h"
#include "Editor.h"

class Game {
private:
   std::vector<Object*> objects;
   PartyMember* player;
   PartyMember* enemy;
   SDL_Specific& sdl;
   Editor editor;
   bool isEditorMode = false;

public:
   Game(SDL_Specific& sdlSpecific) : sdl(sdlSpecific) {
      enemy = new PartyMember();
      player = new PartyMember();

      enemy->setPosition(100, 100);
      objects.push_back(enemy);

      player->setPosition(50, 50);
      objects.push_back(player);
   }

   ~Game() {
      for (Object* obj : objects) {
         delete obj;
      }
   }

   void handleEvent(SDL_Event& event);

   void render(SDL_Specific& sdl) {

         sdl.updateCamera(player->getPosition());
         //level.render(sdl);
         for (Object* obj : objects) {
            sdl.renderSprite(obj->getSprite(), obj->getRect());
         }
      
         if (isEditorMode) {
            editor.renderGrid(sdl);
         }
   }
};