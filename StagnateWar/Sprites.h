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

      // Tile Grass constexpr SPRITEs
      constexpr Sprite GrassPlain = { 0, 4 };
      constexpr Sprite GrassCorner1 = { 0, 0 };
      constexpr Sprite GrassCorner2 = { 1, 0 };
      constexpr Sprite GrassCorner3 = { 0, 1 };
      constexpr Sprite GrassCorner4 = { 1, 1 };


      constexpr Sprite Nothing = { 9, 9 };


      constexpr Sprite GrassNoDCorner1 = { 2, 0 };
      constexpr Sprite GrassNoDCorner2 = { 3, 0 };
      constexpr Sprite GrassNoDCorner3 = { 2, 1 };
      constexpr Sprite GrassNoDCorner4 = { 3, 1 };

      constexpr Sprite AutumnPlain = { 1, 4 };
      constexpr Sprite AutumnCorner1 = { 0, 2 };
      constexpr Sprite AutumnCorner2 = { 1, 2 };
      constexpr Sprite AutumnCorner3 = { 1, 3 };
      constexpr Sprite AutumnCorner4 = { 0, 3 };

      constexpr Sprite DirtPlain = { 2, 4 };
      constexpr Sprite DirtRock = { 2, 3 };

      //Miscellaneous constexpr Sprites(Trees, Rocks, Fences)
      constexpr Sprite TreeBottom = { 0, 7 };
      constexpr Sprite TreeTop = { 0, 6 };
      constexpr Sprite Rocks = { 1, 7 };
      constexpr Sprite Fence = { 2, 7 };
      constexpr Sprite FenceLeft = { 2, 8 };
      constexpr Sprite FenceRight = { 3, 8 };

      //House
      constexpr Sprite HouseTopLeft = { 3, 6 };
      constexpr Sprite HouseTopRight = { 4, 6 };
      constexpr Sprite HouseBottomLeft = { 3, 7 };
      constexpr Sprite HouseBottomRight = { 4, 7 };

      // Water constexpr Sprites
      constexpr Sprite WaterPlain = { 2, 2 };
      constexpr Sprite WaterCorner1 = { 4, 1 };
      constexpr Sprite WaterCorner2 = { 5, 0 };
      constexpr Sprite WaterCorner3 = { 4, 1 };
      constexpr Sprite WaterCorner4 = { 5, 0 };

      // Player constexpr Sprites
      constexpr Sprite playerStand = { 0, 0 };
      constexpr Sprite playerWalk1 = { 0, 1 };
      constexpr Sprite playerWalk2 = { 0, 2 };
      constexpr Sprite playerWalk3 = { 0, 3 };

      constexpr Sprite playerForward1 = { 0, 4 };
      constexpr Sprite playerForward2 = { 0, 5 };
      constexpr Sprite playerForward3 = { 0, 6 };
      constexpr Sprite playerForward4 = { 0, 7 };

      constexpr Sprite playerBack1 = { 0, 7 };
      constexpr Sprite playerBack2 = { 0, 8 };
      constexpr Sprite playerBack3 = { 0, 9 };
      constexpr Sprite playerBack4 = { 0, 10 };

      struct  SpriteMapping {
         Sprite  sprite;
         bool isWalkable;
      };

      // This is a mess i know its from the editor I used to make the map
      const std::unordered_map<int, SpriteMapping> SpriteMap = {
         {-1, {Nothing, true}},
         {36, {GrassPlain, true}},
         {0, {GrassCorner1, true}},
         {1, {GrassCorner2, true}},
         {9, {GrassCorner3, true}},
         {10, {GrassCorner4, true}},

         {2, {GrassNoDCorner1, true}},
         {3, {GrassNoDCorner2, true}},
         {11, {GrassNoDCorner3, true}},
         {12, {GrassNoDCorner4, true}},
         {37, {AutumnPlain, true}},

         {63, {TreeBottom, false}},
         {54, {TreeTop, false}},

         {64, {Rocks, false}},
         {65, {Fence, false}},
         {74, {FenceLeft, false}},
         {75, {FenceRight, false}},

         {38, {DirtPlain, true}},
         {29, {DirtRock, false}},

         {20, {WaterPlain, false}},
         {4,  {WaterCorner1, true}},
         {5,  {WaterCorner2, true}},
         {13, {WaterCorner3, true}},
         {14, {WaterCorner4, true}},

         {57, {HouseTopLeft, false}},
         {58, {HouseTopRight, false}},
         {66, {HouseBottomLeft, false}},
         {67, {HouseBottomRight, false}},
      };
   }
}
