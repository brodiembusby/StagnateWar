#pragma once
#include <SDL3/SDL.h>
//#include "SpriteSheet.h"
#include "Position.h"
#include "constants.h"

class Entity {
protected:
   Position position;
   SDL_FRect rect;

public:
   Entity() : rect{ 0, 0, DEFAULT_HEIGHT, DEFAULT_WIDTH } {}
   virtual ~Entity() = default;

   bool hasCollided(const Entity& other) const {
      return SDL_HasRectIntersectionFloat(&rect, &other.rect);
   }

   virtual SDL_FRect& getRect() { return rect; }
   virtual const SDL_FRect& getRect() const { return rect; } 

   virtual Position& getPosition() { return position; }
   virtual const Position& getPosition() const { return position; } 

   virtual void setPosition(float x, float y) {
      position.setX(x);
      position.setY(y);
      rect.x = x;
      rect.y = y;
   }
};




/// Entity Manager?    void initGame() {
//enemy = new PartyMember();
//player = new PartyMember();
//
//enemy->setPosition(100, 100);
//objects[0] = enemy;
//
//player->setPosition(50, 50);
//objects[player] = player;
//   };