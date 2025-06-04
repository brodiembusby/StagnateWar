#pragma once

#include "Position.h"
#include "SpriteSheet.h"

class Tile
{
private: 

   bool isWalkable = true;
   Position position;
   SpriteSheet sprite;
   SDL_FRect rect = { 0,0, 50,50 };

public:

   Tile() = default;
   ~Tile() = default;
   
   void triggerEvent(); //Placeholder
   
   SDL_FRect& getRect() { return rect; }
   SpriteSheet& getSprite() { return sprite; }
   const Position& getPosition() const { return position; }

   void setIsWalkable(bool isWalkable) { this->isWalkable = isWalkable; }; 
   bool getIsWalkable() { return  isWalkable; }; 

};

