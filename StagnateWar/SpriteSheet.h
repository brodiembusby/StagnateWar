#pragma once
#include <SDL3/SDL.h>
#include <vector>
class SpriteSheet {
private:
   std::vector<SDL_Texture*> sprites; 
   SDL_Texture sSprite;
   std::string imagePath;

public:
   
   SpriteSheet(std::string imagePath) : imagePath() ;
   
   void setImagePath() { this->sSprite = sSprite; }
   std::string getImagePath() { return imagePath; }

   SDL_Texture getSprite() { return sSprite; }
   

};