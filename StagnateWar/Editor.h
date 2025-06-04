#pragma once
// 480 272 good for 16: 9 aspect ratio
#include "Tile.h"
#include "Level.h"
#include "SDL_Specific.h"

class Editor
{
private:

   Tile* level[16][12];
   bool isPlacingWall = false;

public:

   Editor() {
      // Initalize a  Empty tile map
      for (int i = 0; i < 12; i++) {
         for (int j = 0; j < 16; j++) {
            level[i][j] = nullptr;
         }
      }
   }
   ~Editor() {
      // Delete all tiles not saved in map
      for (int i = 0; i < 12; i++) {
         for (int j = 0; j < 16; j++) {
            delete level[i][j];
            level[i][j] = nullptr;
         }
      }
   }
   
   void renderGrid(SDL_Specific& sdl);
   void updateTile(SDL_Event& event); 


   void saveMap();

};

