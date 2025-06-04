#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <string>
#include <SDL3/SDL.h>

class SpriteSheet {
private:
   
   std::vector<SDL_Texture*> sprites; 
   SDL_Texture sSprite;
   std::string path;
   


public:
   
   SpriteSheet(std::string path) : path(path) {
      
   }

   ~SpriteSheet() {
      if (sSprite) {
         SDL_DestroyTexture(sSprite);
         sSprite = nullptr;
      }
   }
   void setImagePath() { this->sSprite = sSprite; }
   std::string getImagePath() { return path; }

   SDL_Texture getSprite() { return sSprite; }
   

};