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
   int direction = 0; 
   bool isMoving = false; 
   float animationTime = 0.1f;
   int currentFrame = 0; 

public:
   Entity() : rect{ 0, 0, DEFAULT_HEIGHT, DEFAULT_WIDTH } {}
   virtual ~Entity() { delete spriteSheet; }


   enum class Direction {
      UP = 0,
      DOWN = 1,
      LEFT = 2,
      RIGHT = 3,
      NONE = 4
   };


   // Getters and Setters
   virtual SDL_FRect& getRect() { return rect; }
   virtual const SDL_FRect& getRect() const { return rect; }
   virtual Position& getPosition() { return position; }
   virtual const Position& getPosition() const { return position; }
   int getDirection() const { return direction; }
   bool getIsMoving() const { return isMoving; }
   virtual SpriteSheet* getSpriteSheet() const { return spriteSheet; }

   void setDirection(int dir) { direction = dir; }
   void setIsMoving(bool moving) { isMoving = moving; }
   virtual void setSpriteSheet(SpriteSheet* ss) { spriteSheet = ss; }
   virtual void setRect(float x, float y, float width, float height) {
      rect.x = x;
      rect.y = y;
      rect.w = width;
      rect.h = height;
   }
   virtual void setPosition(float x, float y) {
      position.setX(x);
      position.setY(y);
      rect.x = x;
      rect.y = y;
   }
   virtual void setSize(float width, float height) {
      rect.w = width;
      rect.h = height;
   }


   void updateAnimation(float deltaTime);
   void playerEvent(SDL_Event& event, Entity* player);
   bool hasCollided(const Entity& other) const {
      return SDL_HasRectIntersectionFloat(&rect, &other.rect);
   }




};

