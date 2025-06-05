#pragma once
#include <SDL3/SDL.h>
#include "SpriteSheet.h"
#include "Position.h"
#include "constants.h"

class Object {
protected:
   SpriteSheet sprite;
   Position position;
   SDL_FRect rect; 

public:
   Object() : rect{ 0, 0, DEFAULT_HEIGHT, DEFAULT_WIDTH } {} // Default size 50x50
   Object(SpriteSheet sprite) : rect{ 0, 0, DEFAULT_HEIGHT, DEFAULT_WIDTH }, sprite(sprite) {}
   virtual ~Object() = default;

   bool hasCollided(const Object& other) const {
      return SDL_HasRectIntersectionFloat(&rect, &other.rect);
   }
   virtual SpriteSheet& getSprite() { return sprite; }
   virtual SDL_FRect& getRect() { return rect; }
   virtual Position& getPosition() { return position; }
   virtual void setPosition(float x, float y) {
      position.setX(x);
      position.setY(y);
      rect.x = x;
      rect.y = y;
   }
};