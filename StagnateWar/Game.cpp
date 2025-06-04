#include "Game.h"
void Game::handleEvent(SDL_Event& event) {
   if (isEditorMode) {
      // In editor mode, pass events to the editor
      //editor.updateTile(event);
      if (event.type == SDL_EVENT_KEY_DOWN) {
         //if (event.key.scancode == SDL_SCANCODE_S) {
         //   editor.saveMap();
         //}
          if (event.key.scancode == SDL_SCANCODE_E) {
            isEditorMode = false;
            SDL_Log("Exiting Editor");
         }
      }
   }
   else {
      // Gameplay mode
      float speed = 200.0f; // Pixels per second
      float deltaTime = sdl.getDeltaTime();

      if (event.type == SDL_EVENT_KEY_DOWN) {
         switch (event.key.scancode) {
         case SDL_SCANCODE_W:
            player->setPosition(player->getPosition().getX(), player->getPosition().getY() - 10);
            break;
         case SDL_SCANCODE_S:
            player->setPosition(player->getPosition().getX(), player->getPosition().getY() + 10);
            break;
         case SDL_SCANCODE_A:
            player->setPosition(player->getPosition().getX() - 10, player->getPosition().getY());
            break;
         case SDL_SCANCODE_D:
            player->setPosition(player->getPosition().getX() + 10, player->getPosition().getY());
            break;
         case SDL_SCANCODE_E:
            isEditorMode = true;;
            break;
         default:
            break;
         }
      }
   }
   //for (const Tile* tile : level.getTiles()) {
   //    if (!tile->getIsWalkable()) {
   //        if(player->hasCollided(&tile->getRect()))
   //            player->setPosition(player->getPosition().getX() - (playerRect.x - tileRect.x),
   //            player->getPosition().getY() - (playerRect.y - tileRect.y));
   //}
   //}
}