#pragma once
#include <SDL3/SDL.h>
#include "SpriteSheet.h"
#include "Position.h"

class Object {
protected:
   SpriteSheet sprite;
   Position position;
   SDL_FRect rect; 

public:
   Object() : rect{ 0, 0, 50, 50 } {} // Default size 50x50
   virtual ~Object() = default;

   bool hasCollided(const Object& other) const {
      return SDL_HasRectIntersectionFloat(&rect, &other.rect);
   }

   void animateSprite() {
      // Placeholder for sprite animation
   }

   // Getters/Setters for position (which updates rect)
   Position& getPosition() { return position; }
   void setPosition(float x, float y) {
      position.setX(x);
      position.setY(y);
      rect.x = x;
      rect.y = y;
   }

   SDL_FRect& getRect() { return rect; }
   SpriteSheet& getSprite() { return sprite; }
};