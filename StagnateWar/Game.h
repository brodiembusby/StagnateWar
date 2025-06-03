#pragma once
#include "SDL_Specific.h"
#include "PartyMember.h"
#include <vector>
#include "Object.h"

class Game {
private:
   std::vector<Object*> objects;
   PartyMember* player;
   SDL_Specific& sdl;

public:
   Game(SDL_Specific& sdlSpecific) : sdl(sdlSpecific) {
      player = new PartyMember();
      player->setPosition(50, 50);
      objects.push_back(player);
   }

   ~Game() {
      for (Object* obj : objects) {
         delete obj;
      }
   }

   void handleEvent(SDL_Event& event) {
      if (event.type == SDL_EVENT_KEY_DOWN) {
         switch (event.key.scancode) {
         case SDL_SCANCODE_W:
            player->setPosition(player->getPosition().getX(), player->getPosition().getY() - 10);
            break;
         case SDL_SCANCODE_S:
            player->setPosition(player->getPosition().getX(), player->getPosition().getY() + 10);
            break;
         case SDL_SCANCODE_A:
            player->setPosition(player->getPosition().getX() - 10, player->getPosition().getY());
            break;
         case SDL_SCANCODE_D:
            player->setPosition(player->getPosition().getX() + 10, player->getPosition().getY());
            break;
         default:
            break;
         }
      }
   }

   void render(SDL_Specific& sdl) {
      for (Object* obj : objects) {
         sdl.renderSprite(obj->getSprite(), obj->getRect());
      }
   }
};