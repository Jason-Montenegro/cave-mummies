// Copyright 2025 Jason Montenegro-Navarro

#include "Game.hpp"
#include "StageOneState.hpp"

namespace cave_mummies::states {

StageOneState::~StageOneState() {
  if (this->loaded) {
    // Unload all loaded game assets
    UnloadTexture(this->stageBackground);
    UnloadTexture(this->floorTile);
    UnloadFont(this->textFont);
    this->loaded = false;
  }
}

void StageOneState::init() {
  if (!this->loaded) {
    // Load all game assets
    this->stageBackground = LoadTexture("assets/background/game_bg.png");
    this->floorTile = LoadTexture("assets/textures/scene/floor_tile.png");
    this->textFont = LoadFont("assets/fonts/PixelOperatorMono-Bold.ttf");
    this->loaded = true;
  }
}

cave_mummies::core::GameStateID StageOneState::update() {
  // when Esc is pressed, go back to main menu
  if (this->game.getInputHandler().isPressed(KEY_ESCAPE)) {
    return cave_mummies::core::GameStateID::MainMenu;
  }
  return this->stateID;
}

void StageOneState::draw() {
  drawBackground();
  drawFloor();
}

void StageOneState::drawBackground() {
  // Draw background
  ClearBackground(BLACK);
  // Calculate the math for extending background to whole game screen
  Rectangle sourceRec{0.0f, 0.0f, static_cast<float>(this->stageBackground.width)
    , static_cast<float>(this->stageBackground.height)};
  Rectangle destRec{0.0f, 0.0f, static_cast<float>(GetScreenWidth())
    , static_cast<float>(GetScreenHeight())};
  Vector2 origin{0.0f, 0.0f};
  DrawTexturePro(this->stageBackground, sourceRec, destRec, origin, 0.0f
    , WHITE);

}

void StageOneState::drawFloor() {
  const int32_t tileSize{32};
  const int32_t screenWidth{GetScreenWidth()};
  const int32_t screenHeight{GetScreenHeight()};
  int y_coord{static_cast<int>(screenHeight / 2 + screenHeight * 0.3f)};
  const float scaleFactor{
    static_cast<float>((screenWidth * 0.15) / floorTile.width)};
  const int32_t coord_increment{tileSize * static_cast<int>(scaleFactor)};

  for (; y_coord < screenHeight; y_coord += coord_increment) {
    int x_coord{0};
    for (; x_coord < screenWidth; x_coord += coord_increment) {
      Vector2 position{static_cast<float>(x_coord)
        , static_cast<float>(y_coord)};
      DrawTextureEx(floorTile, position, 0.0f, scaleFactor, WHITE);
    }
  }
}

}  // namespace cave_mummies::states
