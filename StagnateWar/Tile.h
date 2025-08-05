#pragma once

#include "Position.h"
#include "SpriteSheet.h"
#include "Entity.h"

class Tile : public Entity
{
private: 

   bool isWalkable = true;

public:

   Tile() = default;
   ~Tile() = default;
   
   const void setIsWalkable(bool isWalkable) { this->isWalkable = isWalkable; }; 
   const bool getIsWalkable() { return  isWalkable; }; 

};

