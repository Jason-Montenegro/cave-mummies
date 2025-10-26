// Copyright 2025 Jason Montenegro-Navarro

#include <chrono>
#include <memory>
#include <random>
#include <string>
#include <vector>

#include "StageOneState.hpp"
#include "Game.hpp"
#include "CollisionHandler.hpp"
#include "GameStateHandler.hpp"
#include "MainMenuState.hpp"
#include "PausedMenuGameState.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

using Direction = cave_mummies::entities::Direction;
using GameStateID = cave_mummies::core::GameStateID;

static int64_t score = 0;

namespace cave_mummies::states {

StageOneState::StageOneState(cave_mummies::core::Game& game)
  : GameState(game) {
  this->stateID = cave_mummies::core::GameStateID::StageOne;
}

StageOneState::~StageOneState() {
  if (this->loaded) {
    // Unload all loaded game assets
    UnloadTexture(this->background);
    UnloadTexture(this->floorTile);
    UnloadFont(this->textFont);
    this->loaded = false;
  }
  this->projectiles.clear();
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
    this->player = std::make_unique<cave_mummies::entities::Player>(this->game);

    // Update character positioning and size
    Texture2D texture = this->player->getTexture();
    const float x = static_cast<float>(
      GetScreenWidth() / 2 - texture.width / 2);
    const float y = game.getGameStageFloorHeight() - texture.height;
    const float width = static_cast<float>(texture.width / 4);
    const float height = static_cast<float>(texture.height);
    Rectangle rect = {.x = x, .y = y, .width = width, .height = height};
    this->player->setBounds(rect);

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
  this->game.setCurrentGameScore(++score);
  this->player->update();
  this->checkPlayerGunshot();
  for (auto& p : this->projectiles) {
    p.update();
  }

  std::vector<std::shared_ptr<cave_mummies::entities::Enemy>> shotEnemies;
  for (auto& enemy : this->enemyCollection) {
    enemy->update();

    if (this->game.getCollisionHandler().checkCollision(
      this->player->getBounds(), enemy->getBounds())) {
      this->isPlayerDead = true;
    }

    for (auto& p : this->projectiles) {
      if (this->game.getCollisionHandler().checkCollision(p.getBounds()
        , enemy->getBounds())) {
        shotEnemies.push_back(enemy);
        this->player->reduceJumpCount();
      }
    }
  }

  // Kill all shot enemies
  for (auto& enemy : shotEnemies) {
    this->enemyCollection.remove(enemy);
  }
  shotEnemies.clear();

  cave_mummies::core::GameStateID newState{this->stateID};
  if (this->isPlayerDead) {
    // Temporary line. This block should transition to Game Over state.
    this->game.getGameStateHandler().removeState(GameStateID::StageOne);
    this->game.getGameStateHandler().registerState(GameStateID::GameOver);
    newState = cave_mummies::core::GameStateID::GameOver;
  } else {
    if (this->game.getInputHandler().isPressed(KEY_ESCAPE)) {
      this->pauseGameTime();
      this->game.getGameStateHandler().registerState(GameStateID::PausedMenu);
      newState = cave_mummies::core::GameStateID::PausedMenu;
    }
  }

  // Erase stray bullets that traveled beyond the screen borders
  projectiles.erase(
    std::remove_if(projectiles.begin(), projectiles.end(), [](const auto& p) {
      return p.position.x < 0 || p.position.x > GetScreenWidth();
    })
    , projectiles.end());

  return newState;
}

void StageOneState::pauseGameTime() {
  this->pausedTime = std::chrono::high_resolution_clock::now();
  this->isGamePaused = true;
}

void StageOneState::continueGameTime() {
  auto now{std::chrono::high_resolution_clock::now()};
  auto pausedDuration{std::chrono::duration_cast<
    std::chrono::high_resolution_clock::duration>(now - this->pausedTime)};
  this->startTime += pausedDuration;
  isGamePaused = false;
}

void StageOneState::checkPlayerGunshot() {
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    this->player->reloadAmmunition();
    // Calculate start position of bullet
    Vector2 mousePosition{GetMousePosition()};
    Rectangle playerBounds{this->player->getBounds()};
    const float yCoord{playerBounds.y + playerBounds.height * 0.3f};
    const float xCoord{(this->player->getDirection() == Direction::Right)
      ? playerBounds.x + playerBounds.width : playerBounds.x};
    Vector2 startPosition{xCoord, yCoord};

    // Direction to mouse coordinate
    Vector2 dir{mousePosition.x - startPosition.x
      , mousePosition.y - startPosition.y};
    // Normalize vector direction
    const float length = sqrtf(dir.x * dir.x + dir.y * dir.y);
    if (length != 0) {
        dir.x /= length;
        dir.y /= length;
    }
    // Amplify bullet speed
    const float bulletSpeed{50.0f};
    Vector2 velocity{dir.x * bulletSpeed, dir.y * bulletSpeed};
    cave_mummies::entities::Projectile p{startPosition, velocity, 8.0f, MAROON};
    projectiles.push_back(p);
  }
}

void StageOneState::draw() {
  GameState::drawBackground();
  this->drawFloor();
  this->drawScore();
  this->drawClock();
  this->drawAmmunitionLabel();
  this->player->draw();
  for (auto& p : projectiles) {
    p.draw();
  }
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
  const uint64_t currentAmmo{this->player->getRemainingAmmunition()};
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
      cave_mummies::entities::EnemyDifficulty::Hard};
    if (minutes < 1) {
      enemyCount = 3;
    } else if (minutes < 7) {
      enemyCount = 5;
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
      // Sets sizes to enemy sprite
      const float height{static_cast<float>(enemy->getTexture().height)};
      const int32_t frameCount{4};
      const float width{static_cast<float>(
        enemy->getTexture().width / frameCount)};

      enemy->setBounds(Rectangle{.x = xCoord
        , .y = enemyY, .width = width, .height = height});
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
