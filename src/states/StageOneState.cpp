// Copyright 2025 Jason Montenegro-Navarro

#include <algorithm>
#include <chrono>
#include <memory>
#include <string>
#include <vector>
#include "StageOneState.hpp"
#include "CollisionHandler.hpp"
#include "Enemy.hpp"
#include "Game.hpp"
#include "GameStateHandler.hpp"
#include "InputHandler.hpp"
#include "MainMenuState.hpp"
#include "PausedMenuGameState.hpp"
#include "Player.hpp"
#include "Projectile.hpp"
#include "TextureManager.hpp"

using Direction = cave_mummies::entities::Direction;
using GameStateID = cave_mummies::core::GameStateID;
using EnemyDifficulty = cave_mummies::entities::EnemyDifficulty;
using TextureID = cave_mummies::core::TextureID;

namespace cave_mummies::states {

StageOneState::StageOneState(cave_mummies::core::Game& game)
  : GameState(game, game.getTextureManager().getTexture(
    TextureID::GameBackground))
  , floorTile(game.getTextureManager().getTexture(TextureID::FloorTile)) {
  this->stateID = cave_mummies::core::GameStateID::StageOne;
}

StageOneState::~StageOneState() {
  if (this->loaded) {
    // Unload all loaded game assets
    UnloadFont(this->textFont);
    this->loaded = false;
  }
}

void StageOneState::init() {
  if (!this->loaded) {
    // Load all game assets
    const char* basePath{GetApplicationDirectory()};
    this->textFont = LoadFont((std::string(basePath)
      + "../assets/fonts/PixelOperatorMono-Bold.ttf").c_str());
    this->player = std::make_unique<cave_mummies::entities::Player>(this->game);
    const Texture2D& playerTexture{this->game.getTextureManager().getTexture(
      TextureID::PlayerSprite)};
    // Set correct bounds to player character
    const float screenW{static_cast<float>(GetScreenWidth())};
    const float x{screenW / 2.0f - playerTexture.width / 2.0f};
    const float y{game.getGameStageFloorHeight() - playerTexture.height};
    const float playerW{static_cast<float>(playerTexture.width / 4.0f)};
    const float playerH{static_cast<float>(playerTexture.height)};
    // 20% hitbox reduction
    this->player->setBounds({.x = x, .y = y, .width = playerW - playerW * 0.2f
      , .height = playerH});
    // Setup level settings
    this->startTime = std::chrono::high_resolution_clock::now();
    this->accumulatedPausedTime =
      std::chrono::high_resolution_clock::duration{0};
    this->fontSize = screenW * 0.04f;  // 4% relative to screen width
    // "A" is a sample text for measuring the font
    this->textHeight = MeasureTextEx(this->textFont, "A", this->fontSize
      , 1.0f).y;
    this->loaded = true;
    game.getInputHandler().resetPlayerMovement();
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
  this->destroyStrandedProjectiles();
  // Check state ID to return
  GameStateID newState{this->stateID};
  if (this->game.getInputHandler().isPressed(KEY_ESCAPE)) {
    this->pauseGameTime();
    this->game.getGameStateHandler().registerState(GameStateID::PausedMenu);
    newState = GameStateID::PausedMenu;
  } else {
    newState = this->checkDeadPlayer();
  }
  return newState;
}

void StageOneState::continueGameTime() {
  auto now{std::chrono::high_resolution_clock::now()};
  this->accumulatedPausedTime += now - pausedTime;
  this->isGamePaused = false;
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
    Vector2 projectileVelocity{};
    const float bulletSpeed{50.0f};

    #ifdef __linux__
    calculateProjectileVelocity(&projectileVelocity.x, &projectileVelocity.y
      , mousePosition.x, mousePosition.y, startPosition.x, startPosition.y
      , bulletSpeed);
    #else
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
    projectileVelocity.x = (dir.x * bulletSpeed);
    projectileVelocity.y = (dir.y * bulletSpeed);
    #endif

    this->projectileCollection.push_back(std::make_shared
      <cave_mummies::entities::Projectile>(startPosition, projectileVelocity
      , 6.0f, RED));
  }
}

void StageOneState::reloadPlayerAmmunition() {
  auto& input{this->game.getInputHandler()};
  auto now{std::chrono::high_resolution_clock::now()};
  // Reloading should be done when no ammo is available and the reload key is
  // pressed
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
    if (elapsed.count() >= this->player->getReloadingSpeedInSeconds()) {
      PlaySound(this->player->getReloadSoundEffect());
      this->player->reloadAmmunition();
      this->currentlyReloading = false;
    }
  }
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
    // Checks if the player collisioned with an enemy: he dies beucase of that
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
  const std::chrono::duration<double> elapsed{(now - this->startTime)
    - this->accumulatedPausedTime};
  const uint32_t totalSeconds{static_cast<uint32_t>(elapsed.count())};
  if (totalSeconds > this->lastSecond) {
    gameScore += (totalSeconds - this->lastSecond);  // +1 per elapsed second
    this->lastSecond = totalSeconds;
  }

  // Update game scores
  this->player->setCurrentScore(gameScore);
  this->game.setCurrentGameScore(gameScore);
}

void StageOneState::destroyStrandedProjectiles() {
  // Destroy all stranded projectiles that crossed the screen borders
  this->projectileCollection.erase(std::remove_if(
    this->projectileCollection.begin(), this->projectileCollection.end(),
    [] (const std::shared_ptr<cave_mummies::entities::Projectile>& p) -> bool {
      return p->position.x < 0 || p->position.x > GetScreenWidth()
        || p->position.y < 0 || p->position.y > GetScreenHeight();
    }), this->projectileCollection.end());
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
  // Draws as many tiles as possible until no more tiles are seen on the screen
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
  const auto now{std::chrono::high_resolution_clock::now()};
  const std::chrono::duration<double> elapsed{(now - this->startTime)
    - this->accumulatedPausedTime};
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
  const std::chrono::duration<double> elapsed{(end - this->startTime)
    - this->accumulatedPausedTime};
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

  for (size_t count = 0; count < enemyCount; ++count) {
    const float xCoord{randomX()};
    auto enemy{std::make_shared<cave_mummies::entities::Enemy>(this->game
      , *this->player, enemyDifficulty)};

    // Set spawn points: +10.0f to compensate for enemy sprite texture
    const float enemyY{floorY - enemy->getTexture().height + 10.0f};
    const float height{static_cast<float>(enemy->getTexture().height)};
    // 4 indicates the sprite texture frame count
    const float width{static_cast<float>(enemy->getTexture().width / 4)};
    // Reduce hitbox for better gameplay
    const float originalWidth{width};
    const float newWidth{width - width * 0.3f};
    enemy->setBounds(Rectangle{.x = xCoord + (originalWidth - newWidth) / 2.0f
      , .y = enemyY, .width = newWidth, .height = height});
    this->enemyCollection.push_back(enemy);
  }
}

}  // namespace cave_mummies::states
