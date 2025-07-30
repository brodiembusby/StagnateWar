#include "Game.h"
#include "TextManager.h"
#define WORLD_WIDTH 2048.0f
#define WORLD_HEIGHT 2048.0f
Game::Game() {}

Game::~Game() {
   gameQuit();
}
/// <summary>
/// Runs the main game loop, handling initialization, events, iteration, and cleanup.
/// </summary>
/// <returns>Returns SDL_APP_SUCCESS if the game loop completes successfully, or SDL_APP_FAILURE if initialization fails.</returns>
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
/// <summary>
/// Handles the cleanup of the game resources.
/// </summary>
void Game::gameQuit() {

   delete assetFactory;
   delete textManager;

   if(level) {
      delete level;
      level = nullptr;
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

/// <summary>
/// Initializes the game application, including SDL, window, renderer, font, and core game assets.
/// </summary>
/// <returns>Returns SDL_APP_SUCCESS if initialization is successful; otherwise, returns SDL_APP_FAILURE if any step fails.</returns>
SDL_AppResult Game::gameInit() {

   SDL_SetAppMetadata("Stagnate War", "1.0", "Stagnate War");

   if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
      return SDL_APP_FAILURE;
   }
   int defaultWindowWidth = 640;
   int defaultWindowHeight = 480;
   if (!SDL_CreateWindowAndRenderer("Stagnate War", defaultWindowWidth, defaultWindowHeight, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
      SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
      SDL_Quit();
      return SDL_APP_FAILURE;
   }

   // TTF Text Library
   if (!TTF_Init()) {
      SDL_Log("Couldnt initalize TTF: %s", SDL_GetError());
      return SDL_APP_FAILURE;

   }

   int windowWidth, windowHeight;
   std::tuple<int, int> winSize = getWindowSize();
   windowWidth = std::get<0>(winSize);
   windowHeight = std::get<1>(winSize);
   float fontSize = windowHeight * 0.15f;
   fontSize = std::max(12.0f, std::min(fontSize, 58.0f));
   const char* file = "assets/CourierPrime-Regular.ttf";

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


   SDL_Surface* icon = IMG_Load("assets/testIcon.png");
   if (!SDL_SetWindowIcon(window, icon)) {
      SDL_Log("Failed to set window Icon: %s", SDL_GetError());
   }
   // Someone said this gets rid of the memory leak IDK
   SDL_DestroySurface(icon);
assetFactory = new AssetFactory(textureManager, entityManager, renderer);
    SDL_Texture* tileTexture = assetFactory->loadTexture("TileSpriteSheet");
    if (tileTexture) {
        tileSpriteSheet = new SpriteSheet(tileTexture, 9, 9);
        if (tileSpriteSheet) {
            SDL_Log("Tile sprite sheet created successfully");
            level = new Level();
            level->setAssetFactory(assetFactory); // Set before other operations
            level->setSpriteSheet(tileSpriteSheet);
        } else {
            SDL_Log("Failed to create tile sprite sheet");
            return SDL_APP_FAILURE;
        }
    } else {
        SDL_Log("Failed to load TileSpriteSheet texture");
        return SDL_APP_FAILURE;
    }
    Entity* player = assetFactory->createEntity("player");
    Entity* enemy = assetFactory->createEntity("enemy");
    if (player && enemy) {
        float scaleFactor = windowHeight / 480.0f;
        float entityWidth = 32.0f * scaleFactor;
        float entityHeight = 32.0f * scaleFactor;
        player->setSize(entityWidth, entityHeight);
        enemy->setSize(entityWidth, entityHeight);
        player->setPosition(100.0f * scaleFactor, 100.0f * scaleFactor);
        enemy->setPosition(200.0f * scaleFactor, 200.0f * scaleFactor);
    }
    deltaTime = 1.0f / 60.0f;
    lastTick = SDL_GetTicks();
    return SDL_APP_SUCCESS;
}

void Game::handleEvent(SDL_Event& event) {
   int windowWidth, windowHeight;
   std::tuple<int, int> winSize = getWindowSize();
   windowWidth = std::get<0>(winSize);
   windowHeight = std::get<1>(winSize);

   float scaleFactor = windowHeight / 480.0f;
   float speed = 200.0f * scaleFactor;
   float deltaTime = getDeltaTime();
   Entity* player = entityManager.getEntity("player");
   
   // Editor mode handling
   if (isEditorMode) {
      if (level) {
         level->updateTile(event, camera.getX(), camera.getY()); // Pass camera coordinates
      }
   }
   // Player movement handling
   if (event.type == SDL_EVENT_KEY_DOWN) {
      if (player) {
         float newX = player->getPosition().getX();
         float newY = player->getPosition().getY();
         float playerWidth = player->getRect().w;
         float playerHeight = player->getRect().h;

         switch (event.key.scancode) {
         case SDL_SCANCODE_W:
            newY -= 10 * scaleFactor;
            break;
         case SDL_SCANCODE_S:
            newY += 10 * scaleFactor;
            break;
         case SDL_SCANCODE_A:
            newX -= 10 * scaleFactor;
            break;
         case SDL_SCANCODE_D:
            newX += 10 * scaleFactor;
            break;
         case SDL_SCANCODE_E:
            if (!isEditorMode) {
               isEditorMode = true;

               SDL_Log("Entering Editor Mode");
            }
            else {
               isEditorMode = false;
               SDL_Log("Exiting Editor Mode");
               
            }
            break;
         // Toggle fullscreen with F11
         case SDL_SCANCODE_F11: 
            if (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN) {
               SDL_SetWindowFullscreen(window, 0); // Exit fullscreen
            }
            else {
               SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN); // Enter fullscreen
            }
            break;
         default:
            break;
         }

         // Clamp player position to world boundaries, accounting for player size
         newX = std::max(0.0f, std::min(newX, WORLD_WIDTH - playerWidth));
         newY = std::max(0.0f, std::min(newY, WORLD_HEIGHT - playerHeight));

         // Set the clamped position
         player->setPosition(newX, newY);
      }
   }

   // Update entity sizes
   else if (event.type == SDL_EVENT_WINDOW_RESIZED) {
      Entity* player = entityManager.getEntity("player");
      Entity* enemy = entityManager.getEntity("enemy");
      if (player && enemy) {
         float entityWidth = 32.0f * scaleFactor;
         float entityHeight = 32.0f * scaleFactor;
         player->setSize(entityWidth, entityHeight);
         enemy->setSize(entityWidth, entityHeight);
      }
   }

   // Collision detection between player and enemy
   Entity* enemy = entityManager.getEntity("enemy");
   if (player->hasCollided(*enemy)) {
      showCollisionText = true;
   }
   else {
      showCollisionText = false;
   }
}


SDL_AppResult Game::gameIterate() {
   Uint64 currentTick = SDL_GetTicks();
   deltaTime = (currentTick - lastTick) / 1000.0f;
   lastTick = currentTick;

   int windowWidth, windowHeight;
   std::tuple<int, int> winSize = getWindowSize();
   windowWidth = std::get<0>(winSize);
   windowHeight = std::get<1>(winSize);

   // Update camera to follow the player
   Entity* player = entityManager.getEntity("player");
   Entity* enemy = entityManager.getEntity("enemy");

   if (player) {
      updateCamera(player->getPosition());
   }

   SDL_SetRenderDrawColor(renderer, 100,100,100,100);
   SDL_RenderClear(renderer);
   
   if (level) {
      level->renderTiles(renderer, camera.getX(), camera.getY());

   }

   // This might stay
   if (player) {
      SpriteSheet* playerSpriteSheet = player->getSpriteSheet();
      if (playerSpriteSheet) {

         playerSpriteSheet->selectSprite(1, 0); 
         SDL_FRect destRect = player->getRect();
         // Adjust the destination rectangle to account for camera position
         destRect.x -= camera.getX();
         destRect.y -= camera.getY();
         playerSpriteSheet->drawSprite(renderer, destRect);
      }
      else {
         SDL_Log("Player has no sprite sheet");
      }
   }
   // This will be replaced with a more efficent structure later
   if (enemy) {
      SpriteSheet* enemySpriteSheet = enemy->getSpriteSheet();
      if (enemySpriteSheet) {
         enemySpriteSheet->selectSprite(2, 0); 
         SDL_FRect destRect = enemy->getRect();
         destRect.x -= camera.getX();
         destRect.y -= camera.getY();
         enemySpriteSheet->drawSprite(renderer, destRect);
      }
      else {
         SDL_Log("Enemy has no sprite sheet");
      }
   }

   
   if (isEditorMode) {
      level->renderGrid(renderer);
   }

   if (showCollisionText) {
      const char* testText = "This game is a work in progress. PLease be patient with me.";
      textManager->setText(testText);
      textManager->display(renderer, windowWidth, windowHeight);
   }

   SDL_RenderPresent(renderer);
   return SDL_APP_SUCCESS;
}

void Game::updateCamera(Position& target) {

   int windowWidth, windowHeight;
   std::tuple<int, int> winSize = getWindowSize();
   windowWidth = std::get<0>(winSize);
   windowHeight = std::get<1>(winSize);
   
   // Center the camera on the target (player)
   float cameraX = target.getX() - windowWidth / 2.0f;
   float cameraY = target.getY() - windowHeight / 2.0f;

   cameraX = std::max(0.0f, std::min(cameraX, WORLD_WIDTH - windowWidth));
   cameraY = std::max(0.0f, std::min(cameraY, WORLD_HEIGHT - windowHeight));

   camera.setX(cameraX);
   camera.setY(cameraY);
}
