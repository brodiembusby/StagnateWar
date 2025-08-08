#include "Entity.h"
#include <algorithm>

void Entity::playerEvent(SDL_Event& event, Entity* player) {
   if (event.type == SDL_EVENT_KEY_DOWN) {

      float newX = player->getPosition().getX();
      float newY = player->getPosition().getY();
      float speed = 5.0f;

      float playerWidth = player->getRect().w;
      float playerHeight = player->getRect().h;
      Direction newDirection = Direction::NONE; // Default direction

      switch (event.key.scancode) {
      case SDL_SCANCODE_W:
         newY -= speed;
         newDirection = Direction::UP;
         isMoving = true;
         break;
      case SDL_SCANCODE_S:
         newY += speed;
         newDirection = Direction::DOWN;
         isMoving = true;
         break;
      case SDL_SCANCODE_A:
         newX -= speed;
         newDirection = Direction::LEFT;
         isMoving = true;
         break;
      case SDL_SCANCODE_D:
         newX += speed;
         newDirection = Direction::RIGHT;
         isMoving = true;
         break;

      default:
         isMoving = false;
         break;
      }

      // Clamp player position to world boundaries
      newX = std::max(0.0f, std::min(newX, WORLD_WIDTH - playerWidth));
      newY = std::max(0.0f, std::min(newY, WORLD_HEIGHT - playerHeight));

      // Set the clamped position and direction
      player->setPosition(newX, newY);
      player->setDirection((int)newDirection); // Store the direction
      setIsMoving(isMoving);
   }
}

void Entity::updateAnimation(float deltaTime) {

   if (isMoving) {
      
// Update animation time
      animationTime += deltaTime;
      // Cycle through frames every 0.2 seconds
      if (animationTime >= 0.2f) {
         if (direction == (int)Direction::LEFT || direction == (int)Direction::RIGHT) currentFrame = 1 + ((currentFrame - 1 + 1) % 3); // Cycle 1-3
         if (direction == (int)Direction::DOWN) currentFrame = 5 + ((currentFrame - 5 + 1) % 3); // Cycle 5-7
         if (direction == (int)Direction::UP) currentFrame = 9 + ((currentFrame - 9 + 1) % 3); // Cycle 9-11
         animationTime = 0.0f; // Reset timer
      }
   }
   else {
      currentFrame = 0; // Standing still, use frame (0, 0)
      animationTime = 0.0f; // Reset timer
   }


// Update sprite sheet
if (spriteSheet) {
   spriteSheet->selectCurrentSprite(currentFrame, 0);
   // Set flip based on direction

   if (direction == (int)Direction::LEFT) {
      spriteSheet->setFlipMode(SDL_FLIP_HORIZONTAL);
   }
   else {
      spriteSheet->setFlipMode(SDL_FLIP_NONE);
   }
}
}