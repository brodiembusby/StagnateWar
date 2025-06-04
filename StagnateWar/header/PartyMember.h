#pragma once
#include "Object.h"
#include <string>

enum ItemType
{
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


   std::string getName() { return name; };
   void setName(std::string name) { this->name = name; }


   int getValue() { return value; };
   void setValue(int value) { this->value = value; }
};


class Inventory {

private:
   std::vector<Item> inventory ;
   
public:

   void addItem(Item item) { inventory.push_back(item); };
   void removeItem(Item item); // Placeholder

};
class PartyMember : public Object
{
private:
   Item item;
   Inventory inventory;
   int health = 100;
   int level = 1;
   int xp = 0;
   int strength = 1;
   int speed = 1;
   int armour = 1;
   // StatusEffect effects[];

public:

   PartyMember() = default;

   void setItem(Item item) { item = item;}
   void setXP(int xp) { this->xp = xp; }
   void setStrength(int strength) { this->strength = strength; }
   void setSpeed(int speed) { this->speed = speed; }
   void setArmour(int armour) { this->armour = armour; }
   void setPartyMemberLevel(int level) { this->level = level;}

   Item getItem() { item = item; }
   int getXP() { return xp; }
   int getStrength() { return strength; }
   int getSpeed() { return speed; }
   int getArmour() { return armour; }
   int getPartyMemberLevel() { return level; }

   void update(); // Placeholder

   // void applyStatusEffect(StatusEffect status) {effects.push_back(status);}
};

//// Placeholder implementation for removeItem (to avoid linker errors)
//void Inventory::removeItem(Item item) {
//   // TODO: Implement removal logic
//}