#pragma once
#include <SDL3/SDL.h>
#include "SpriteSheet.h"
#include "Position.h"
#include "constants.h"

class Entity {
protected:
   Position position;
   SDL_FRect rect;
   SpriteSheet* spriteSheet = nullptr;

public:
   Entity() : rect{ 0, 0, DEFAULT_HEIGHT, DEFAULT_WIDTH } {}
   virtual ~Entity() { delete spriteSheet; }

   // Getters and Setters
   virtual SDL_FRect& getRect() { return rect; }
   virtual const SDL_FRect& getRect() const { return rect; } 
   virtual void setRect(float x, float y, float width, float height) {
      rect.x = x;
      rect.y = y;
      rect.w = width;
      rect.h = height;
   }
   
   virtual Position& getPosition() { return position; }
   virtual const Position& getPosition() const { return position; } 
   virtual void setPosition(float x, float y) {
      position.setX(x);
      position.setY(y);
      rect.x = x;
      rect.y = y;
   }
   virtual void setSpriteSheet(SpriteSheet* ss) { spriteSheet = ss; }
   virtual SpriteSheet* getSpriteSheet() const { return spriteSheet; }

   virtual void setSize(float width, float height) {
      rect.w = width;
      rect.h = height;
   }

   //Methods
   void playerEvent(SDL_Event& event, Entity* player);
   bool hasCollided(const Entity& other) const {
      return SDL_HasRectIntersectionFloat(&rect, &other.rect);
   }


};

