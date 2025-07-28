#include "Game.h"
#include "TextManager.h"

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


   SDL_Surface* icon = IMG_Load("assets/testIcon.png");
   if (!SDL_SetWindowIcon(window, icon)) {
      SDL_Log("Failed to set window Icon: %s", SDL_GetError());
   }
   // Someone said this gets rid of the memory leak IDK
   SDL_DestroySurface(icon);

   assetFactory = new AssetFactory(textureManager, entityManager, renderer);

   assetFactory->createEntity("player");
   assetFactory->createEntity("enemy");

   deltaTime = 1.0f / 60.0f;
   lastTick = SDL_GetTicks();

   return SDL_APP_SUCCESS;
}

void Game::handleEvent(SDL_Event& event) {
   float speed = 200.0f; // Pixels per second
   float deltaTime = getDeltaTime();
   Entity* player = entityManager.getEntity("player");

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
         isEditorMode = true;
         SDL_Log("Entering Editor Mode");
         break;
      case SDL_SCANCODE_F11: // Toggle fullscreen with F11
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
   }
   Entity* enemy = entityManager.getEntity("enemy");
   if (player->hasCollided(*enemy)) {

      showCollisionText = true;
      const char* testText = "This game is a work in progress.";
      textManager->setText(testText);
   }
   else if (!player->hasCollided(*enemy)) {
      showCollisionText = false;
   }
}

SDL_AppResult Game::gameIterate() {
   Uint64 currentTick = SDL_GetTicks();
   deltaTime = (currentTick - lastTick) / 1000.0f;
   lastTick = currentTick;

   const SDL_Color SAGE_GREEN = { 178, 172, 136, 255 };
   SDL_SetRenderDrawColor(renderer, SAGE_GREEN.r, SAGE_GREEN.g, SAGE_GREEN.b, SAGE_GREEN.a);
   SDL_RenderClear(renderer);

   Entity* player = entityManager.getEntity("player");
   Entity* enemy = entityManager.getEntity("enemy");

   if (player) {
      SpriteSheet* playerSpriteSheet = player->getSpriteSheet();
      if (playerSpriteSheet) {
         SDL_FRect destRect = player->getRect();
         playerSpriteSheet->drawSprite(renderer, destRect);
      }
      else {
         SDL_Log("Player has no sprite sheet");
      }
   }
   if (enemy) {
      SpriteSheet* enemySpriteSheet = enemy->getSpriteSheet();
      if (enemySpriteSheet) {
         SDL_FRect destRect = enemy->getRect();
         enemySpriteSheet->drawSprite(renderer, destRect);
      }
      else {
         SDL_Log("Enemy has no sprite sheet");
      }
   }
   if (showCollisionText) {
      textManager->display(renderer);
   }
   SDL_RenderPresent(renderer);
   return SDL_APP_SUCCESS;
}

void Game::updateCamera(Position& target) {
   camera.setX(target.getX() - WINDOW_WIDTH / 2.0f);
   camera.setY(target.getY() - WINDOW_HEIGHT / 2.0f);
   if (camera.getX() < 0) camera.setX(0);
   if (camera.getY() < 0) camera.setY(0);
   if (camera.getX() > WORLD_WIDTH - WINDOW_WIDTH) camera.setX(WORLD_WIDTH - WINDOW_WIDTH);
   if (camera.getY() > WORLD_HEIGHT - WINDOW_HEIGHT) camera.setY(WORLD_HEIGHT - WINDOW_HEIGHT);
}
