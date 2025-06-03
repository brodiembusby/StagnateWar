#pragma once
class Position
{
private:
   float x;
   float y;
public:

   void setX(float x) {this->x = x; }
   void setY(float y) {this->y = y; }

   float getX()   {return x; }
   float getY()  { return y; }

};

