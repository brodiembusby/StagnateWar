#pragma once
/// <summary>
/// Represents a 2D position with x and y coordinates.
/// </summary>
class Position
{
private:
   float x;
   float y;
public:

   Position(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

   void setX(float x) {this->x = x; }
   void setY(float y) {this->y = y; }

   float getX()  { return x; }
   float getY()  { return y; }

};

