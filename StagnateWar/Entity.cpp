#include "Entity.h"
#include <algorithm>

void Entity::playerEvent(SDL_Event& event, Entity* player) {

   // Handle events related to the party member menu here

   if (event.type == SDL_EVENT_KEY_DOWN) {

      float newX = player->getPosition().getX();
      float newY = player->getPosition().getY();
      float playerWidth = player->getRect().w;
      float playerHeight = player->getRect().h;

      switch (event.key.scancode)
      {
      case SDL_SCANCODE_W:
         newY -= 10;
         break;
      case SDL_SCANCODE_S:
         newY += 10;
         break;
      case SDL_SCANCODE_A:
         newX -= 10;
         break;
      case SDL_SCANCODE_D:
         newX += 10;
         break;
      default:
         break;
      }

      if (event.key.scancode == SDLK_ESCAPE) {
         // Example: Close the party member menu on Escape key press
         SDL_Log("Party member menu closed");
      }
      // Clamp player position to world boundaries, accounting for player size
      newX = std::max(0.0f, std::min(newX, WORLD_WIDTH - playerWidth));
      newY = std::max(0.0f, std::min(newY, WORLD_HEIGHT - playerHeight));

      // Set the clamped position
      player->setPosition(newX, newY);
   }

}