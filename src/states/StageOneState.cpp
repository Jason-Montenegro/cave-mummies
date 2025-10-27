// Copyright 2025 Jason Montenegro-Navarro

#include <algorithm>
#include <chrono>
#include <memory>
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
#include "Projectile.hpp"
#include "InputHandler.hpp"

using Direction = cave_mummies::entities::Direction;
using GameStateID = cave_mummies::core::GameStateID;
using EnemyDifficulty = cave_mummies::entities::EnemyDifficulty;

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
    const float screenW{static_cast<float>(GetScreenWidth())};
    const float x{screenW / 2.0f - texture.width / 2.0f};
    const float y{game.getGameStageFloorHeight() - texture.height};
    const float playerW{static_cast<float>(texture.width / 4.0f)};
    const float playerH{static_cast<float>(texture.height)};
    this->player->setBounds({.x = x, .y = y, .width = playerW
      , .height = playerH});
    // Setup level settings
    this->startTime = std::chrono::high_resolution_clock::now();
    this->fontSize = screenW * 0.04f;  // 4% relative to screen width
    // "A" is a sample text for measuring
    this->textHeight = MeasureTextEx(this->textFont, "A", this->fontSize
      , 1.0f).y;
    this->loaded = true;
  }
}

cave_mummies::core::GameStateID StageOneState::update() {
  // when Esc is pressed, go back to main menu
  if (this->isGamePaused) {
    this->continueGameTime();
  }
  this->player->update();
  this->checkProjectileShot();
  this->reloadPlayerAmmunition();
  this->updateProjectilesShot();
  this->updateKilledEnemies();
  this->updateGameScore();

  // Destroy all stranded projectiles that crossed the screen borders
  this->projectileCollection.erase(std::remove_if(
    this->projectileCollection.begin(), this->projectileCollection.end(),
    [] (const auto& p) {
      return p->position.x < 0 || p->position.x > GetScreenWidth();
    }), this->projectileCollection.end());

  cave_mummies::core::GameStateID newState{this->stateID};
  if (this->game.getInputHandler().isPressed(KEY_ESCAPE)) {
    this->pauseGameTime();
    this->game.getGameStateHandler().registerState(GameStateID::PausedMenu);
    newState = cave_mummies::core::GameStateID::PausedMenu;
  } else {
    newState = this->checkDeadPlayer();
  }
  return newState;
}

void StageOneState::checkProjectileShot() {
  auto& input{this->game.getInputHandler()};
  const uint32_t currentAmmo{this->player->getRemainingAmmunition()};
  if (input.isMouseLeftPressed() && currentAmmo > 0) {
    PlaySound(this->player->getGunShotSoundEffect());
    this->player->decrementAmmunitionCount();
    // Calculates start position of bullet
    Vector2 mousePosition{input.getCurrentMousePosition()};
    Rectangle playerBounds{this->player->getBounds()};
    const float yCoord{playerBounds.y + playerBounds.height * 0.3f};
    const float xCoord{(this->player->getDirection() == Direction::Right)
      ? playerBounds.x + playerBounds.width : playerBounds.x};
    Vector2 startPosition{xCoord, yCoord};

    // Direction to mouse coordinate
    Vector2 dir{.x = (mousePosition.x - startPosition.x)
      , .y = mousePosition.y - startPosition.y};
    // Normalizes vector direction
    const float length{sqrtf(dir.x * dir.x + dir.y * dir.y)};
    if (length != 0) {
      dir.x /= length;
      dir.y /= length;
    }
    // Amplifies the bullet speed
    const float bulletSpeed{50.0f};
    Vector2 velocity{.x = (dir.x * bulletSpeed), .y = (dir.y * bulletSpeed)};
    auto p{std::make_shared<cave_mummies::entities::Projectile>(startPosition
      , velocity, 6.0f, DARKGRAY)};
    this->projectileCollection.push_back(p);
    // TODO(Jason): add asm function
  }
}

void StageOneState::reloadPlayerAmmunition() {
  auto& input{this->game.getInputHandler()};
  // Gun reloading is only allowed with the R key
  auto now{std::chrono::high_resolution_clock::now()};

  if ((input.isPressed(KEY_R) || input.isMouseLeftPressed())
    && !this->currentlyReloading
    && (this->player->getRemainingAmmunition() == 0)) {
    this->startReloadAmmo = now;
    this->currentlyReloading = true;
  }

  if (this->currentlyReloading) {
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(
      now - this->startReloadAmmo);
    // Calculates a 2 seconds timer for reloading
    if (elapsed.count() >= 2) {
      PlaySound(this->player->getReloadSoundEffect());
      this->player->reloadAmmunition();
      this->currentlyReloading = false;
    }
  }
  // TODO(Jason): set up asm function
}

void StageOneState::updateProjectilesShot() {
  for (auto& p : this->projectileCollection) {
    p->update();
  }
}

void StageOneState::updateKilledEnemies() {
  std::vector<std::shared_ptr<cave_mummies::entities::Enemy>> shotEnemies;
  std::vector<std::shared_ptr<cave_mummies::entities::Projectile>>
    impactedProjectiles;
  for (auto& enemy : this->enemyCollection) {
    enemy->update();
    // Checks if the player collisioned with an enemy: he dies for that
    if (this->game.getCollisionHandler().checkCollision(
      this->player->getBounds(), enemy->getBounds())) {
      this->isPlayerDead = true;
      break;
    }
    // Check all collisioned projectiles with enemies
    for (auto& p : this->projectileCollection) {
      if (this->game.getCollisionHandler().checkCollision(p->getBounds()
        , enemy->getBounds())) {
        impactedProjectiles.push_back(p);
        enemy->incrementReceivedAttacks();
        if (enemy->getAttackTolerance() == enemy->getReceivedAttacks()) {
          shotEnemies.push_back(enemy);
        }
      }
    }
  }
  // Kill all shot enemies
  for (auto& enemy : shotEnemies) {
    this->enemyCollection.remove(enemy);
    // Every enemy killed grants one extra jump to the player
    this->player->incrementKillCount();
    this->player->reduceJumpCount();
  }
  // Erase all impacted projectiles
  for (auto& p : impactedProjectiles) {
    this->projectileCollection.remove(p);
  }
}

void StageOneState::updateGameScore() {
  uint64_t gameScore{this->game.getCurrentGameScore()};
  // Kill count score
  const uint64_t currentKills{this->player->getKillCount()};
  if (currentKills > this->lastKillCount) {
    gameScore += (currentKills - this->lastKillCount) * 10;  // +10 per kill
    this->lastKillCount = currentKills;
  }
  // Time score
  const auto now{std::chrono::high_resolution_clock::now()};
  const std::chrono::duration<double> elapsed{now - this->startTime};
  const uint32_t totalSeconds{static_cast<uint32_t>(elapsed.count())};
  if (totalSeconds > this->lastSecond) {
    gameScore += (totalSeconds - this->lastSecond);  // +1 per elapsed second
    this->lastSecond = totalSeconds;
  }
  // Update game scores
  this->player->setCurrentScore(gameScore);
  this->game.setCurrentGameScore(gameScore);
  // TODO(Jason): set up asm function
}

cave_mummies::core::GameStateID StageOneState::checkDeadPlayer() {
  GameStateID newState{this->stateID};
  if (this->isPlayerDead) {
    this->game.getGameStateHandler().removeState(GameStateID::StageOne);
    this->game.getGameStateHandler().registerState(GameStateID::GameOver);
    newState = GameStateID::GameOver;
  }
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

void StageOneState::draw() {
  GameState::drawBackground();
  this->drawFloor();
  this->drawScore();
  this->drawClock();
  this->drawAmmunitionLabel();
  this->player->draw();
  for (auto& p : this->projectileCollection) {
    p->draw();
  }
  this->spawnEnemies();
}

void StageOneState::drawFloor() {
  const float tileSize{32.0};  // Texture pixel width
  const int32_t screenWidth{GetScreenWidth()};
  const int32_t screenHeight{GetScreenHeight()};
  // 0.15f as in 15% in relative sizing
  const float scaleFactor{(screenWidth * 0.15f) / floorTile.width};
  const float coordIncrement{tileSize * scaleFactor};
  float yCoord{static_cast<float>(this->game.getGameStageFloorHeight())};
  // Draws as many tiles as possible until no more tiles fit are seen on the
  // screen
  for (; yCoord < static_cast<float>(screenHeight); yCoord += coordIncrement) {
    float xCoord{0.0f};
    for (; xCoord < static_cast<float>(screenWidth); xCoord += coordIncrement) {
      Vector2 position{.x = xCoord, .y = yCoord};
      DrawTextureEx(floorTile, position, 0.0f, scaleFactor, WHITE);
    }
  }
}

void StageOneState::drawScore() {
  const uint64_t currentScore{this->game.getCurrentGameScore()};
  const std::string buffer{"SCORE: " + std::to_string(currentScore)};
  const float paddingX{20.0f};
  const float paddingY{20.0f};
  const float spacing{1.0f};
  DrawTextEx(this->textFont, buffer.c_str(), {.x = paddingX, .y = paddingY}
    , this->fontSize, spacing, WHITE);
}

void StageOneState::drawClock() {
  const auto end{std::chrono::high_resolution_clock::now()};
  const std::chrono::duration<double> elapsed{end - this->startTime};
  const uint32_t totalSeconds{static_cast<uint32_t>(elapsed.count())};
  const uint32_t seconds{totalSeconds % 60};
  const uint32_t minutes{(totalSeconds % 3600) / 60};
  const uint32_t hours{totalSeconds / 3600};

  const std::string clockBuffer{"TIME: "
    + (hours < 10 ? "0" + std::to_string(hours) : std::to_string(hours))
    + ":"
    + (minutes < 10 ? "0" + std::to_string(minutes) : std::to_string(minutes))
    + ":"
    + (seconds < 10 ? "0" + std::to_string(seconds) : std::to_string(seconds))};

  // Situated below SCORE label
  // +10.0f for padding between labels
  const float paddingY{20.0f + this->textHeight + 10.0f};
  const float paddingX{20.0f};
  const float spacing{1.0f};
  DrawTextEx(this->textFont, clockBuffer.c_str(), {paddingX, paddingY}
    , this->fontSize, spacing, WHITE);
}

void StageOneState::drawAmmunitionLabel() {
  const uint64_t currentAmmo{this->player->getRemainingAmmunition()};
  const std::string buffer{"AMMO: " + std::to_string(currentAmmo)};

  // Situated below TIME label
  // +20.0f for padding between labels
  const float paddingY{20.0f + this->textHeight * 2 + 20.0f};
  const float paddingX{20.0f};
  const float spacing{1.0f};
  DrawTextEx(this->textFont, buffer.c_str(), {paddingX, paddingY}
    , this->fontSize, spacing, WHITE);
}

void StageOneState::spawnEnemies() {
  generateEnemies();
  for (auto& enemy : this->enemyCollection) {
    enemy->draw();
  }
}

void StageOneState::generateEnemies() {
  // Calculate time elapsed in the game
  const auto end{std::chrono::high_resolution_clock::now()};
  const std::chrono::duration<double> elapsed{end - this->startTime};
  const uint32_t totalSeconds{static_cast<uint32_t>(elapsed.count())};
  const uint32_t minutesElapsed{(totalSeconds % 3600) / 60};

  // Generate enemies if there isn't any, or if an exact minute has elapsed
  if (this->enemyCollection.empty() || minutesElapsed > this->lastSpawnMinute) {
    this->lastSpawnMinute = minutesElapsed;
    uint32_t enemyCount{this->calculateSpawnEnemyCount(minutesElapsed)};
    cave_mummies::entities::EnemyDifficulty enemyDifficulty{
      this->calculateEnemyDifficulty(minutesElapsed)};
    this->randomizeEnemySpawn(enemyCount, enemyDifficulty);
  }
}

uint32_t StageOneState::calculateSpawnEnemyCount(uint32_t minutesElapsed) {
  if (minutesElapsed < 1) {
    return 2;  // Spawn 2 enemies
  } else if (minutesElapsed < 2) {
    return 3;  // Spawn 3 enemies
  } else {
    return 4;  // Spawn 4 enemies
  }
}

EnemyDifficulty StageOneState::calculateEnemyDifficulty(
  uint32_t minutesElapsed) {
  if (minutesElapsed < 1) {
    return EnemyDifficulty::Easy;
  } else if (minutesElapsed < 2) {
    return EnemyDifficulty::Moderate;
  } else {
    return EnemyDifficulty::Hard;
  }
}

void StageOneState::randomizeEnemySpawn(uint32_t enemyCount
  , EnemyDifficulty enemyDifficulty) {
  const float floorY{this->game.getGameStageFloorHeight()};
  // Random side picker
  auto randomX = [this]() -> float {
    // Chooses a random side: lower number is left, greater numbers is right
    const float side{this->xDis(gen) < 0.5f ? 0.04f : 0.96f};
    return GetScreenWidth() * (side + this->xDis(gen) * 0.10f);
  };

  for (size_t count{0}; count < enemyCount; ++count) {
    const float xCoord{randomX()};
    auto enemy{std::make_shared<cave_mummies::entities::Enemy>(this->game
      , *this->player, enemyDifficulty)};

    // Set spawn points: +10.0f to compensate for enemy sprite texture
    const float enemyY{floorY - enemy->getTexture().height + 10.0f};
    const float height{static_cast<float>(enemy->getTexture().height)};
    // 4 indicates the sprite texture frame count
    const float width{static_cast<float>(enemy->getTexture().width / 4)};

    enemy->setBounds(Rectangle{.x = xCoord, .y = enemyY, .width = width
      , .height = height});
    this->enemyCollection.push_back(enemy);
  }
}

}  // namespace cave_mummies::states
