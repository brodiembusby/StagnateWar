#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "Game.h"

int main(int argc, char* argv[]) {

   StagnateWar::Game game;
   game.Run();

   return 0;
}
