#pragma once
#include "SpriteSheet.h"
// learned this from https://github.com/TheCherno/Genesis-Remake/blob/master/Graphics/SPRITE.h

namespace StagnateWar {


   struct  Sprite {
      float x = 0;
      float y = 0;
      float size = 32;
   };


   namespace  Sprites {

      constexpr Sprite Nothing = { 9, 9 };

      // Tile Grass constexpr SPRITEs
      constexpr Sprite GrassPlain = { 0, 2 };
      constexpr Sprite GrassCorner1 = { 0, 0 };
      constexpr Sprite GrassCorner2 = { 1, 0 };
      constexpr Sprite GrassCorner3 = { 0, 1 };
      constexpr Sprite GrassCorner4 = { 1, 1 };

      constexpr Sprite AutumnGrassPlain = { 1, 2 };
      constexpr Sprite AutmnGrassCorner1 = { 2, 0 };
      constexpr Sprite AutmnGrassCorner2 = { 3,0 };
      constexpr Sprite AutmnGrassCorner3 = { 2, 1 };
      constexpr Sprite AutmnGrassCorner4 = { 3, 1 };

      constexpr Sprite PharohGrassPlain = { 7, 5 };
      constexpr Sprite PharohGrassCorner1 = { 7, 3 };
      constexpr Sprite PharohGrassCorner2 = { 8, 3 };
      constexpr Sprite PharohGrassCorner3 = { 7, 4 };
      constexpr Sprite PharohGrassCorner4 = { 8, 4 };

      // Dirt constexpr Sprites
      constexpr Sprite DirtPlain = { 3, 2 };
      constexpr Sprite DirtRock = { 2, 2 };

      constexpr Sprite AutumnDirtPlain = { 5, 3 };
      constexpr Sprite AutumnDirtRock = { 6, 3 };

      constexpr Sprite PharohDirtPlain = { 5, 4 };
      constexpr Sprite PharohDirtRock = { 6, 4 };

      // Miscellaneous constexpr Sprites (Trees, Rocks, Fences)
      constexpr Sprite TreeBottom = { 6, 0 };
      constexpr Sprite TreeTop = { 6, 1 };

      constexpr Sprite PharohTreeBottom = { 0, 6 };
      constexpr Sprite PharohTreeTop = { 0, 5 };

      constexpr Sprite AutmnTreeBottom = { 0, 4 };
      constexpr Sprite AutmnTreeTop = { 0, 3 };

      constexpr Sprite Rocks = { 5, 2 };
      constexpr Sprite Fence = { 6, 2 };
      constexpr Sprite FenceLeft = { 7, 2 };
      constexpr Sprite FenceRight = { 8, 2 };

      // House
      constexpr Sprite HouseTopLeft = { 7, 0 };
      constexpr Sprite HouseTopRight = { 8, 0 };
      constexpr Sprite HouseBottomLeft = { 7, 1 };
      constexpr Sprite HouseBottomRight = { 8, 1 };

      constexpr Sprite AutumnHouse1 = { 3, 3 };
      constexpr Sprite AutumnHouse2 = { 4, 3 };
      constexpr Sprite AutumnHouse3 = { 3, 4 };
      constexpr Sprite AutumnHouse4 = { 4, 4 };

      constexpr Sprite PharohHouse1 = { 3, 5 };
      constexpr Sprite PharohHouse2 = { 4, 5 };
      constexpr Sprite PharohHouse3 = { 3, 6 };
      constexpr Sprite PharohHouse4 = { 4, 6 };

      // Water constexpr Sprites
      constexpr Sprite WaterPlain = { 4, 1 };
      constexpr Sprite WaterCorner1 = { 4, 0 };
      constexpr Sprite WaterCorner2 = { 5, 0 };
      constexpr Sprite WaterCorner4 = { 5, 1 };
      constexpr Sprite WaterCorner3 = { 4, 2 };

      constexpr Sprite MurkyWaterPlain = { 1, 4 };
      constexpr Sprite MurkyWaterCorner1 = { 1, 3 };
      constexpr Sprite MurkyWaterCorner2 = { 2, 3 };
      constexpr Sprite MurkyWaterCorner3 = { 2, 4 };


      struct  SpriteMapping {
         Sprite  sprite;
         bool isWalkable;
      };

      // This is a mess i know its from the editor I used to make the map
      const std::unordered_map<int, SpriteMapping> SpriteMap = {
         {-1, {Nothing, true}},

         {18, {GrassPlain, true}},
         {0, {GrassCorner1, true}},
         {1, {GrassCorner2, true}},
         {9, {GrassCorner3, true}},
         {10, {GrassCorner4, true}},

         {2,  {AutmnGrassCorner1, true}},
         {3,  {AutmnGrassCorner2, true}},
         {11, {AutmnGrassCorner3, true}},
         {12, {AutmnGrassCorner4, true}},
         {19, {AutumnGrassPlain, true}},

         {13, {WaterPlain, false}},
         {4, {WaterCorner1, true}},
         {5,  {WaterCorner2, true}},
         {14, {WaterCorner3, true}},
         {22, {WaterCorner4, true}},

         {6, {TreeBottom, false}},
         {15, {TreeTop, false}},

         {45, {PharohTreeTop, false}},
         {54, {PharohTreeBottom, false}},

         {36, {AutmnTreeBottom, false}},
         {27, {AutmnTreeTop, false}},

         {7, {HouseTopLeft, false}},
         {8, {HouseTopRight, false}},
         {16, {HouseBottomLeft, false}},
         {17, {HouseBottomRight, false}},

         {23, {Rocks, false}},
         {24, {Fence, false}},
         {25, {FenceLeft, false}},
         {26, {FenceRight, false}},

         {21, {DirtPlain, true}},
         {20, {DirtRock, true}},


         {32, {AutumnDirtPlain, true}},
         {33, {AutumnDirtRock, true}},

         {41, {PharohDirtPlain, true}},
         {42, {PharohDirtRock, true}},

         {30, {AutumnHouse1, false}},
         {31, {AutumnHouse2, false}},
         {39, {AutumnHouse3, false}},
         {40, {AutumnHouse4, false}},

         {48, {PharohHouse1, false}},
         {49, {PharohHouse2, false}},
         {57, {PharohHouse3, false}},
         {58, {PharohHouse4, false}},

         {52, {PharohGrassPlain, true}},
         {34, {PharohGrassCorner1, true}},
         {35, {PharohGrassCorner2, true}},
         {43, {PharohGrassCorner3, true}},
         {44, {PharohGrassCorner4, true}},

         {37, {MurkyWaterPlain, true}},
         {28, {MurkyWaterCorner1, true}},
         {29, {MurkyWaterCorner2, true}},
         {38, {MurkyWaterCorner3, true}},

      };
   }
}
