#include "Game.h"
#include "TextManager.h"
Game::Game() : player(nullptr), textManager(nullptr) {
}

Game::~Game() {
   gameQuit();
}

SDL_AppResult Game::Run() {
   
if (gameInit() != SDL_APP_SUCCESS) {
      return SDL_APP_FAILURE;
   }

   bool running = true;
   SDL_Event event;

   while (running) {
      while (SDL_PollEvent(&event)) {
         if (event.type == SDL_EVENT_QUIT) {
            running = false;
         }
         handleEvent(event);
      }

      SDL_AppResult result = gameIterate();
      if (result != SDL_APP_SUCCESS) {
         running = false;
      }
   }

   gameQuit();
   return SDL_APP_SUCCESS;
}

void Game::gameQuit() {
   
   //TODO change to array of entityies and auto delete
   if (playerTexture) {
      SDL_DestroyTexture(playerTexture);
      playerTexture = nullptr;
   }
   if (textManager) {
      delete textManager;
      textManager = nullptr;
   }
   if (player) {
      delete player;
      player = nullptr;
   }
   if (renderer) {
      SDL_DestroyRenderer(renderer);
      renderer = nullptr;
   }
   if (window) {
      SDL_DestroyWindow(window);
      window = nullptr;
   }
   if (font) {
      TTF_CloseFont(font);
      font = nullptr;
      TTF_Quit();
   }
   SDL_Quit();
}

void Game::handleEvent(SDL_Event& event) {
   float speed = 200.0f; // Pixels per second
   float deltaTime = getDeltaTime();

   if (event.type == SDL_EVENT_KEY_DOWN) {
      if (!player) return; // Guard against null player
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
         isEditorMode = true;
         SDL_Log("Entering Editor Mode");
         break;
      default:
         break;
      }
   }
}

SDL_AppResult Game::gameInit() {
   SDL_SetAppMetadata("Stagnate War", "1.0", "Stagnate War");

   if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
      return SDL_APP_FAILURE;
   }

   if (!SDL_CreateWindowAndRenderer("Stagnate War", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer)) {
      SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
      SDL_Quit();
      return SDL_APP_FAILURE;
   }

   // TTF Text Library
   if (!TTF_Init()) {
      SDL_Log("Couldnt initalize TTF: %s", SDL_GetError());
      return SDL_APP_FAILURE;

   }
   /*
   Fonts I think look good 
   "assets/BitcountPropSingle_Cursive-ExtraBold.ttf"
   "assets/BitcountPropSingle_Cursive-Regular"
   "assets/BitcountPropSingle-SemiBold"
   */
   const char* file = "assets/CourierPrime-Regular.ttf";
   float fontSize = 24;
   font = TTF_OpenFont(file, fontSize);
   if (!font) {
      SDL_Log("Couldnt open TTF font file: %s", SDL_GetError());
      return SDL_APP_FAILURE;

   }

   textManager = new TextManager(font);
   if (!textManager) {
      SDL_Log("Failed to create TextManager");
      return SDL_APP_FAILURE;
   }

   //TODO auto add members from a array probably based on levelManager

   const char* path = "assets/testGuy.png";
   playerTexture = IMG_LoadTexture(renderer, path);
   if (!playerTexture) {
      SDL_Log("Couldn't load texture %s: %s", path, SDL_GetError());
      return SDL_APP_FAILURE;
   }

   player = new PartyMember();
   deltaTime = 1.0f / 60.0f;

   return SDL_APP_SUCCESS;
}

SDL_AppResult Game::gameIterate() {
   // Update deltaTime
   Uint64 currentTick = SDL_GetTicks();
   deltaTime = (currentTick - lastTick) / 1000.0f; 
   lastTick = currentTick;

   // Clear screen

   // This is gross I just wanted to see what it looked like
   const SDL_Color SAGE_GREEN = { 178, 172, 136, 255 };
   SDL_SetRenderDrawColor(renderer, SAGE_GREEN.r, SAGE_GREEN.g, SAGE_GREEN.b, SAGE_GREEN.a); 
   SDL_RenderClear(renderer);

   // Render Text
   if (textManager) {
      textManager->display(renderer, "This game is a work in progress.");
   }

   if (player) {
      SDL_FRect playerRect = { player->getPosition().getX(), player->getPosition().getY(), 50, 50 };
      //DEBUG
      //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); 
      SDL_RenderFillRect(renderer, &playerRect);
      if (playerTexture) {
         if (!SDL_RenderTexture(renderer, playerTexture, nullptr, &playerRect)) {
            SDL_Log("Couldn't render texture: %s", SDL_GetError());
         }
      }
   }

   SDL_RenderPresent(renderer);
   return SDL_APP_SUCCESS;
}

void Game::updateCamera(Position& target) {
    // Center the camera on the target (player)
    camera.setX(target.getX() - WINDOW_WIDTH / 2.0f);
    camera.setY(target.getY() - WINDOW_HEIGHT / 2.0f);

    // Optional: Clamp the camera to the game world boundaries
    if (camera.getX() < 0) {
        camera.setX(0);
    }
    if (camera.getY() < 0) {
        camera.setY(0);
    }
    if (camera.getX() > WORLD_WIDTH - WINDOW_WIDTH) {
        camera.setX(WORLD_WIDTH - WINDOW_WIDTH);
    }
    if (camera.getY() > WORLD_HEIGHT - WINDOW_HEIGHT) {
        camera.setY(WORLD_HEIGHT - WINDOW_HEIGHT);
    }
}
/*
void Game::renderSprite(SpriteSheet sprite, SDL_FRect rect) {
    SDL_SetRenderDrawColor(renderer, 100, 0, 0, 255); // Rect colors
    // Adjust the rectangle's position relative to the camera
    SDL_FRect adjustedRect = {
        rect.x - camera.getX(),
        rect.y - camera.getY(),
        rect.w,
        rect.h
    };
    SDL_RenderRect(renderer, &adjustedRect);
}

void Game::render() {
    updateCamera(player->getPosition());
    //level.render(sdl);
    for (Entity* obj : objects) {
        renderSprite(obj->getSprite(), obj->getRect());
    }
    if (isEditorMode) {
        editor.renderGrid(sdl);
    }
}

if (isEditorMode) {
    // In editor mode, pass events to the editor
    //editor.updateTile(event);
    if (event.type == SDL_EVENT_KEY_DOWN) {
        if (event.key.scancode == SDL_SCANCODE_E) {
            isEditorMode = false;
            SDL_Log("Exiting Editor");
        }
    }
}

for (const Tile* tile : level.getTiles()) {
    if (!tile->getIsWalkable()) {
        if (player->hasCollided(&tile->getRect()))
            player->setPosition(player->getPosition().getX() - (playerRect.x - tileRect.x),
                                player->getPosition().getY() - (playerRect.y - tileRect.y));
    }
}
*/