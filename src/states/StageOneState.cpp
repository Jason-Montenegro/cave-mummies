// Copyright 2025 Jason Montenegro-Navarro

#include <chrono>
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
    this->startTime = std::chrono::high_resolution_clock::now();
    this->loaded = true;
    this->textHeight = MeasureTextEx(this->textFont, "A", this->fontSize
      , 1.0f).y;
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
  drawScore();
  drawClock();
  drawAmmunitionLabel();
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

void StageOneState::drawScore() {
  const uint64_t currentScore{this->player->getCurrentScore()};
  const std::string buffer{"SCORE: " + std::to_string(currentScore)};
  
  const float paddingX{20.0f};
  const float paddingY{20.0f};
  DrawTextEx(this->textFont, buffer.c_str(), {paddingX, paddingY}
    , this->fontSize, 1.0f, WHITE);
}

void StageOneState::drawClock() {
  auto end{std::chrono::high_resolution_clock::now()};
  const std::chrono::duration<double> elapsed{end - this->startTime};
  const int32_t totalSeconds{static_cast<int>(elapsed.count())};
  const int32_t seconds{totalSeconds % 60};
  const int32_t minutes{(totalSeconds % 3600) / 60};
  const int32_t hours{totalSeconds / 3600};

  const std::string buffer{"TIME: "
    + (hours < 10 ? "0" + std::to_string(hours) : std::to_string(hours)) + ":"
    + (minutes < 10 ? "0" + std::to_string(minutes) : std::to_string(minutes))
    + ":"
    + (seconds < 10 ? "0" + std::to_string(seconds) : std::to_string(seconds))};

  // Situated below SCORE label
  // +10.0f for padding between labels
  const float paddingY{20.0f + this->textHeight + 10.0f};
  const float paddingX{20.0f};
  DrawTextEx(this->textFont, buffer.c_str(), {paddingX, paddingY}
    , this->fontSize, 1.0f, WHITE);
}

void StageOneState::drawAmmunitionLabel() {
  const uint64_t currentAmmo{this->player->getLoadedAmmunitionRemaining()};
  const std::string buffer{"AMMO: " + std::to_string(currentAmmo)};
  
  // Situated below TIME label
  // +20.0f for padding between labels
  const float paddingY{20.0f + this->textHeight * 2 + 20.0f};
  const float paddingX{20.0f};
  DrawTextEx(this->textFont, buffer.c_str(), {paddingX, paddingY}
    , this->fontSize, 1.0f, WHITE);
}

}  // namespace cave_mummies::states
