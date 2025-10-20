// Copyright 2025 Jason Montenegro-Navarro

#include <chrono>
#include <memory>
#include <string>
#include <random>

#include "Game.hpp"
#include "StageOneState.hpp"

namespace cave_mummies::states {

StageOneState::~StageOneState() {
  if (this->loaded) {
    // Unload all loaded game assets
    UnloadTexture(this->background);
    UnloadTexture(this->floorTile);
    UnloadFont(this->textFont);
    this->loaded = false;
  }
}

void StageOneState::init() {
  if (!this->loaded) {
    // Load all game assets
    const char* basePath{GetApplicationDirectory()};
    this->background = LoadTexture((std::string(basePath)
    + "../assets/background/game_bg.png").c_str());
    this->floorTile = LoadTexture((std::string(basePath)
      + "../assets/textures/scene/floor_tile.png").c_str());
    this->textFont = LoadFont((std::string(basePath)
      + "../assets/fonts/PixelOperatorMono-Bold.ttf").c_str());
    this->player = std::make_unique<cave_mummies::entities::Player>(this->game,
      "../assets/textures/entities/wil_player_skin.png");
    this->player->setVelocity(8.0);
    Rectangle playerBounds{.height = 32.0
      , .width = 32.0
      , .x = static_cast<float>(GetScreenWidth() / 2)
      , .y = this->game.getGameStageFloorHeight()
        - player->getTexture().height};
    this->player->setBounds(playerBounds);
    this->player->setCurrentSpeed(1.5);
    this->startTime = std::chrono::high_resolution_clock::now();
    this->loaded = true;
    this->fontSize = GetScreenWidth() * 0.04f;
    this->textHeight = MeasureTextEx(this->textFont, "A", this->fontSize
      , 1.0f).y;
  }
}

cave_mummies::core::GameStateID StageOneState::update() {
  // when Esc is pressed, go back to main menu
  if (this->isGamePaused) {
    this->continueGameTime();
  }
  this->player->update();
  for (auto& enemy : this->enemyCollection) {
    enemy->update();
  }
  cave_mummies::core::GameStateID newState{this->stateID};
  if (this->game.getInputHandler().isPressed(KEY_ESCAPE)) {
    this->pauseGameTime();
    this->game.getGameStateHandler().registerState(GameStateID::PausedMenu
      , std::make_shared<cave_mummies::states::PausedMenuGameState>(
        this->game));
    newState = cave_mummies::core::GameStateID::PausedMenu;
  }
  return newState;
}

void StageOneState::pauseGameTime() {
  this->pausedTime = std::chrono::high_resolution_clock::now();
  isGamePaused = true;
}

void StageOneState::continueGameTime() {
  auto now{std::chrono::high_resolution_clock::now()};
  auto pausedDuration{std::chrono::duration_cast<
    std::chrono::high_resolution_clock::duration>(now - this->pausedTime)};
  this->startTime += pausedDuration;
  isGamePaused = false;
}

void StageOneState::draw() {
  GameState::drawBackground();
  this->drawFloor();
  this->drawScore();
  this->drawClock();
  this->drawAmmunitionLabel();
  this->player->draw();
  this->spawnEnemies();
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

void StageOneState::generateEnemies() {
  // Calculate time elapsed in the game
  auto end{std::chrono::high_resolution_clock::now()};
  const std::chrono::duration<double> elapsed{end - this->startTime};
  const int32_t totalSeconds{static_cast<int>(elapsed.count())};
  const int32_t minutes{(totalSeconds % 3600) / 60};

  // Generate enemis if there isn't any, or if an exact minute has elapsed
  if (this->enemyCollection.empty() || minutes > this->lastSpawnMinute) {
    this->lastSpawnMinute = minutes;
    size_t enemyCount{0};
    cave_mummies::entities::EnemyDifficulty enemyDifficulty{
      cave_mummies::entities::EnemyDifficulty::Easy};
    if (minutes < 3) {
      enemyCount = 3;
    } else if (minutes < 7) {
      enemyCount = 5;
      enemyDifficulty = cave_mummies::entities::EnemyDifficulty::Moderate;
    } else {
      enemyCount = 7;
      enemyDifficulty = cave_mummies::entities::EnemyDifficulty::Hard;
    }

    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> xDis(0.0f, 1.0f);
    const float floorY{this->game.getGameStageFloorHeight()};
    for (size_t count{0}; count < enemyCount; ++count) {
      float xCoord{};
      if (xDis(gen) < 0.5f) {
        // Spawn on the left side
        xCoord = GetScreenWidth() * (0.05f + xDis(gen) * 0.20f);
      } else {
        // Spawn on the right side
        xCoord = GetScreenWidth() * (0.75f + xDis(gen) * 0.20f);
      }
      auto enemy{std::make_shared<cave_mummies::entities::Enemy>(this->game
        , *this->player, enemyDifficulty)};
      // Set spawn points
      const float enemyY{floorY - enemy->getTexture().height};
      enemy->setBounds(Rectangle{xCoord, enemyY, enemy->getBounds().width
        , enemy->getBounds().height});
      this->enemyCollection.push_back(enemy);
    }
  }
}

void StageOneState::spawnEnemies() {
  generateEnemies();
  static std::uniform_real_distribution<float> dis(0, 1);
  for (auto& enemy : this->enemyCollection) {
    enemy->draw();
  }
}

}  // namespace cave_mummies::states
