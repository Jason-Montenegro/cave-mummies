// Copyright 2025 Jason Montenegro-Navarro

#include <memory>

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
    this->player = std::make_unique<cave_mummies::entities::Player>(this->game,
      "assets/textures/entities/wil_player_skin.png");
    this->player->setVelocity(8.0);
    Rectangle playerBounds{.height = 32.0
      , .width = 32.0
      , .x = static_cast<float>(GetScreenWidth() / 2)
      , .y = this->game.getGameStageFloorHeight()
        - player->getTexture().height};
    this->player->setBounds(playerBounds);
    this->loaded = true;
  }
}

cave_mummies::core::GameStateID StageOneState::update() {
  // when Esc is pressed, go back to main menu
  this->player->update();
  if (this->game.getInputHandler().isPressed(KEY_ESCAPE)) {
    return cave_mummies::core::GameStateID::MainMenu;
  }
  return this->stateID;
}

void StageOneState::draw() {
  drawBackground();
  drawFloor();
  this->player->draw();
}

void StageOneState::drawBackground() {
  // Draw background
  ClearBackground(BLACK);
  // Calculate the math for extending background to whole game screen
  Rectangle sourceRec{0.0f, 0.0f
    , static_cast<float>(this->stageBackground.width)
    , static_cast<float>(this->stageBackground.height)};
  Rectangle destRec{0.0f, 0.0f, static_cast<float>(GetScreenWidth())
    , static_cast<float>(GetScreenHeight())};
  Vector2 origin{0.0f, 0.0f};
  DrawTexturePro(this->stageBackground, sourceRec, destRec, origin, 0.0f
    , WHITE);
}

void StageOneState::drawFloor() {
  const float tileSize{32.0};
  const int32_t screenWidth{GetScreenWidth()};
  const int32_t screenHeight{GetScreenHeight()};
  const float scaleFactor{(screenWidth * 0.15f) / floorTile.width};
  const float coordIncrement{tileSize * scaleFactor};
  float yCoord{static_cast<float>(this->game.getGameStageFloorHeight())};

  for (; yCoord < static_cast<float>(screenHeight); yCoord += coordIncrement) {
    float xCoord{0.0f};
    for (; xCoord < static_cast<float>(screenWidth); xCoord += coordIncrement) {
      Vector2 position{xCoord, yCoord};
      DrawTextureEx(floorTile, position, 0.0f, scaleFactor, WHITE);
    }
  }
}

}  // namespace cave_mummies::states
