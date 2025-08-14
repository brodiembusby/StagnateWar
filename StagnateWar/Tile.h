#pragma once

#include "Position.h"
#include "SpriteSheet.h"
#include "Entity.h"

class Tile : public Entity
{
private: 

   bool isWalkable = true;
   float spriteX = 0.0f; 
   float spriteY = 0.0f; 

public:

   Tile() = default;
   ~Tile() = default;
   
   const void setIsWalkable(bool isWalkable) { this->isWalkable = isWalkable; }; 
   const bool getIsWalkable() { return  isWalkable; }; 
   void setSpriteCoords(float x, float y) { spriteX = x; spriteY = y; }
   float getSpriteX() const { return spriteX; }
   float getSpriteY() const { return spriteY; }
};

