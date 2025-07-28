#pragma once
#include <SDL3/SDL.h>
//#include "SpriteSheet.h"
#include "Position.h"
#include "constants.h"

class Entity {
protected:
   Position position;
   SDL_FRect rect;
   // TODO will be replaces with a sprite sheet
   SDL_Texture* texture = nullptr;

public:
   Entity() : rect{ 0, 0, DEFAULT_HEIGHT, DEFAULT_WIDTH } {}
   virtual ~Entity() = default;

   // Getters and Setters
   virtual SDL_FRect& getRect() { return rect; }
   virtual const SDL_FRect& getRect() const { return rect; } 
   virtual Position& getPosition() { return position; }
   virtual const Position& getPosition() const { return position; } 
   virtual void setTexture(SDL_Texture* t) { texture = t; }
   virtual SDL_Texture* getTexture() const { return texture; }
   virtual void setPosition(float x, float y) {
      position.setX(x);
      position.setY(y);
      rect.x = x;
      rect.y = y;
   }
   
   // Methods
   bool hasCollided(const Entity& other) const {
      return SDL_HasRectIntersectionFloat(&rect, &other.rect);
   }


};

