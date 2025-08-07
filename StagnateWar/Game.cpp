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

   if (level) {
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
   if (!SDL_SetRenderLogicalPresentation(renderer, defaultWindowWidth, defaultWindowHeight, SDL_LOGICAL_PRESENTATION_LETTERBOX)) {
      SDL_Log("Failed to set logical presentation: %s", SDL_GetError());
      return SDL_APP_FAILURE;
   }
   // TTF Text Library
   if (!TTF_Init()) {
      SDL_Log("Couldnt initalize TTF: %s", SDL_GetError());
      return SDL_APP_FAILURE;

   }

   //int windowWidth, windowHeight;
   //std::tuple<int, int> winSize = getWindowSize();
   //windowWidth = std::get<0>(winSize);
   //windowHeight = std::get<1>(winSize);
   //float fontSize = windowHeight * 0.15f;
   float fontSize = 480 * 0.15f; // Base font size on logical height
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

   assetFactory = new AssetFactory(renderer);
   SDL_Texture* tileTexture = assetFactory->loadTexture("TileSpriteSheet");
   if (tileTexture) {
      tileSpriteSheet = new SpriteSheet(tileTexture, 9, 9);
      if (tileSpriteSheet) {
         SDL_Log("Tile sprite sheet created successfully");
         level = new Level(assetFactory);
      }
      else {
         SDL_Log("Failed to create tile sprite sheet");
         return SDL_APP_FAILURE;
      }
   }
   else {
      SDL_Log("Failed to load TileSpriteSheet texture");
      return SDL_APP_FAILURE;
   }

   // Create and store entities
   Entity* player = assetFactory->createEntity("player");
   if (player) {
      entities.push_back(player);
   }
   else {
      SDL_Log("Failed to create player entity");
      return SDL_APP_FAILURE;
   }

   Entity* enemy = assetFactory->createEntity("enemy");
   if (enemy) {
      entities.push_back(enemy);
   }
   else {
      SDL_Log("Failed to create enemy entity");
      return SDL_APP_FAILURE;
   }

   // Set initial entity sizes and positions
   float entityWidth = 32.0f;
   float entityHeight = 32.0f;
   for (Entity* entity : entities) {
      entity->setSize(entityWidth, entityHeight);
      if (entity == player) {
         entity->setPosition(100.0f, 100.0f);
      }
      else if (entity == enemy) {
         entity->setPosition(200.0f, 200.0f);
      }
   }

   deltaTime = 1.0f / 60.0f;
   lastTick = SDL_GetTicks();
   return SDL_APP_SUCCESS;
}

void Game::handleEvent(SDL_Event& event) {

   // Convert event coordinates to logical render coordinates
   if (!SDL_ConvertEventToRenderCoordinates(renderer, &event)) {
      SDL_Log("Failed to convert event coordinates: %s", SDL_GetError());
   }

   if (event.type == SDL_EVENT_KEY_DOWN) {
      switch (event.key.scancode) {
      case SDL_SCANCODE_E:
         isEditorMode = !isEditorMode;
         SDL_Log(isEditorMode ? "Entering Editor Mode" : "Exiting Editor Mode");
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
      case SDL_SCANCODE_Q:
         isMenuing = !isMenuing;
         SDL_Log(isMenuing ? "Entering Menu Mode" : "Exiting Menu Mode");
         break;
      default:
         break;
      }
   }
   if (isMenuing) {
      textManager->menuEvent(event);
   }
   // Editor mode handling
   if (isEditorMode && level) {
      level->editorEvent(event);
      level->updateTile(event, camera.getX(), camera.getY());
   }

   //// TODO: Need to Fix this sorta works but not really
   //// Update entity sizes on window resize
   //int windowWidth, windowHeight;
   //std::tuple<int, int> winSize = getWindowSize();
   //windowWidth = std::get<0>(winSize);
   //windowHeight = std::get<1>(winSize);
   //float scaleFactor = windowHeight / 480.0f;
   //if (event.type == SDL_EVENT_WINDOW_RESIZED) {
   //   float entityWidth = 32.0f * scaleFactor;
   //   float entityHeight = 32.0f * scaleFactor;
   //   for (Entity* entity : entities) {
   //      entity->setSize(entityWidth, entityHeight);
   //   }
   //}


   Entity* player = findEntity("player");
   Entity* enemy = findEntity("enemy");
   if (player && enemy && player->hasCollided(*enemy)) {
      showCollisionText = true;
   }
   else {
      showCollisionText = false;
   }
   if (!isMenuing && !isEditorMode && player) {

      player->playerEvent(event, player);

   }


}
SDL_AppResult Game::gameIterate() {
   Uint64 currentTick = SDL_GetTicks();
   deltaTime = (currentTick - lastTick) / 1000.0f;
   lastTick = currentTick;

   // Update camera to follow player
   Entity* player = findEntity("player");
   if (player) {
      updateCamera(player->getPosition());
   }

   SDL_SetRenderDrawColor(renderer, 100, 100, 100, 100);
   SDL_RenderClear(renderer);

   if (level) {
      level->renderTiles(renderer, 0, 0); // No camera offset needed due to viewport
   }

   // Render entities
   for (Entity* entity : entities) {
      SpriteSheet* spriteSheet = entity->getSpriteSheet();
      if (spriteSheet) {
         int spriteRow = (entity == assetFactory->getEntity("player")) ? 1 : 2;
         spriteSheet->selectCurrentSprite(spriteRow, 0);
         SDL_FRect destRect = entity->getRect();
         destRect.x -= camera.getX(); // Apply camera offset
         destRect.y -= camera.getY();
         spriteSheet->drawSprite(renderer, destRect);
      }
      else {
         SDL_Log("Entity has no sprite sheet");
      }
   }

   if (isMenuing) {
      const char* menuText = "Fight Run";
      textManager->setText(menuText);
      textManager->display(renderer, 0, 0); // Window size not needed
   }

   if (isEditorMode) {
      level->renderGrid(renderer,camera.getX(),camera.getY());
   }

   if (showCollisionText) {
      const char* testText = "This game is a work in progress. Please be patient with me.";
      textManager->setText(testText);
      textManager->display(renderer, 0, 0); // Window size not needed
   }

   SDL_RenderPresent(renderer);
   return SDL_APP_SUCCESS;
}
void Game::updateCamera(Position& target) {
   int logicalWidth, logicalHeight;
   SDL_RendererLogicalPresentation mode;
   if (!SDL_GetRenderLogicalPresentation(renderer, &logicalWidth, &logicalHeight, &mode)) {
      SDL_Log("Failed to get logical presentation: %s", SDL_GetError());
      logicalWidth = 640;
      logicalHeight = 480;
   }

   // Center the camera on the target (player) in logical coordinates
   float cameraX = target.getX() - logicalWidth / 2.0f;
   float cameraY = target.getY() - logicalHeight / 2.0f;

   // Clamp camera to world bounds
   cameraX = std::max(0.0f, std::min(cameraX, WORLD_WIDTH - logicalWidth));
   cameraY = std::max(0.0f, std::min(cameraY, WORLD_HEIGHT - logicalHeight));

   camera.setX(cameraX);
   camera.setY(cameraY);

}

Entity* Game::findEntity(const std::string& name) {
   for (Entity* entity : entities) {
      if (entity == assetFactory->getEntity(name)) {
         return entity;
      }
   }
   return nullptr;
}

std::tuple<int, int> Game::getWindowSize() const {
   int width, height;
   if (!SDL_GetWindowSize(window, &width, &height)) {
      SDL_Log("Failed to get window size: %s", SDL_GetError());
      width = 640; // Fallback default
      height = 480;
   }
   return std::make_tuple(width, height);
}

//void Game::clampPlayerPosition(Entity* player) {
//   if (!player) return;
//   Position pos = player->getPosition();
//   float width = player->getRect().w;
//   float height = player->getRect().h;
//   pos.setX(std::max(0.0f + width / 2, std::min(pos.getX(), WORLD_WIDTH - width / 2)));
//   pos.setY(std::max(0.0f + height / 2, std::min(pos.getY(), WORLD_HEIGHT - height / 2)));
//   player->setPosition(pos.getX(), pos.getY());
//}