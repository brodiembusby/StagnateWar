#pragma once
#include "Entity.h"
#include <string> 


enum class ItemType{
   WEAPON,
   ARMOUR,
   CONSUMABLE,
   KEYITEM

};


class Item {

private:
   
   int value;
   std::string name;

public:

   Item() : value(0), name("") {}

   std::string getName() { return name; }
   void setName(std::string name) { this->name = name; }

   int getValue() { return value; }
   void setValue(int value) { this->value = value; }
};



struct Inventory {

   Item inventory[10]; ;
   
};


class PartyMember : public Entity {
private:
   Item item;
   int health = 100;
   int level = 1;
   int xp = 0;
   int strength = 1;
   int speed = 1;
   int armour = 1;

public:
   PartyMember() = default;

   void setItem(Item item) { this->item = item; }
   void setXP(int xp) { this->xp = xp; }
   void setStrength(int strength) { this->strength = strength; }
   void setSpeed(int speed) { this->speed = speed; }
   void setArmour(int armour) { this->armour = armour; }
   void setPartyMemberLevel(int level) { this->level = level; }

   Item getItem() const { return item; } 
   int getXP() const { return xp; } 
   int getStrength() const { return strength; } 
   int getSpeed() const { return speed; } 
   int getArmour() const { return armour; } 
   int getPartyMemberLevel() const { return level; } 

};
