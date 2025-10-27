// Copyright 2025 Jason Montenegro-Navarro

#include <stdexcept>
#include <string>

#include "Enemy.hpp"
#include "Player.hpp"
#include "Game.hpp"

namespace cave_mummies::entities {

Enemy::Enemy(cave_mummies::core::Game& game
  , cave_mummies::entities::Player &objective, EnemyDifficulty diff)
  : Entity(game)
  , objective(objective)
  , difficultyType(diff) {
  this->setVelocity(diff);
  this->setSpeed(diff);
  this->setAttackTolerance(diff);
  this->loadTexture();
}

void Enemy::loadTexture() {
  if (texture.id != 0) {
    UnloadTexture(texture);
  }
  std::string filename{game.getGameTextures().getEnemyTextureFilename(
    this->difficultyType)};
  std::string basePath{GetApplicationDirectory()};
  Image img{LoadImage((basePath + filename).c_str())};
  if (!img.data) {
    throw std::runtime_error("Failed to load enemy texture: "
      + std::string(filename));
  }
  const int32_t newWidth{static_cast<int32_t>(img.width * 0.1f)};
  const int32_t newHeight{static_cast<int32_t>(img.height * 0.1f)};
  ImageResize(&img, newWidth, newHeight);
  this->texture = LoadTextureFromImage(img);
  UnloadImage(img);
}

Enemy::~Enemy() {
  if (this->texture.id != 0) {
    UnloadTexture(this->texture);
  }
}

void Enemy::update() {
  this->updateLateralMovement();
  this->updateSpriteFrame();
}

void Enemy::updateLateralMovement() {
  // Move this enemy towards the objective
  const float newPosition{this->currentSpeed * this->velocity};
  const float distanceDiff{this->objective.getBounds().x - this->bounds.x};
  // this enemy y coordinate stays constant since instantiation
  if (distanceDiff < 0) {
    this->bounds.x -= newPosition;
  } else if (distanceDiff > 0) {
    this->bounds.x += newPosition;
  }
  // TODO(Jason): set up asm function
}

void Enemy::updateSpriteFrame() {
  // 60 because the game runs on 60 fps
  this->gameFrameCounter = (gameFrameCounter + 4) % 60;
  if (this->gameFrameCounter == 0) {
    this->currentSpriteFrame =
      ++this->currentSpriteFrame % this->spriteFrameCount;
  }
}

void Enemy::draw() {
  // Using the current sprite frame and the spritesheet, it selects which
  // frame is the correct one, and draws only that
  const float frameWidth{static_cast<float>(this->texture.width / 4.0f)};
  const float frameHeight{static_cast<float>(this->texture.height)};
  const float characterScale{1.0f};

  // Always redirect this enemy facing towards the player
  const float distanceDiff{this->objective.getBounds().x - this->bounds.x};
  if (distanceDiff <= 0) {
    this->currentDirection = cave_mummies::entities::Direction::Left;
  } else if (distanceDiff > 0) {
    this->currentDirection = cave_mummies::entities::Direction::Right;
  }

  // Calculate the frame from the texture
  Rectangle sourceRec{this->currentSpriteFrame * frameWidth, 0, frameWidth
    , frameHeight};

  if (this->currentDirection == cave_mummies::entities::Direction::Left) {
    sourceRec.width *= -1;
    sourceRec.x += frameWidth;
  }
  Rectangle destRec{this->bounds.x, this->bounds.y, frameWidth * characterScale,
    frameHeight * characterScale
  };

  DrawTexturePro(this->texture, sourceRec, destRec, (Vector2){0, 0}, 0.0f
    , WHITE);
}

void Enemy::setVelocity(EnemyDifficulty type) {
  switch (type) {
  case EnemyDifficulty::Easy:
    this->velocity = this->baseVelocity = 2.0f;
    break;
  case EnemyDifficulty::Moderate:
    this->velocity = this->baseVelocity = 2.5f;
    break;
  case EnemyDifficulty::Hard:
    this->velocity = this->baseVelocity = 3.0f;
    break;
  }
}

void Enemy::setSpeed(EnemyDifficulty type) {
  switch (type) {
  case EnemyDifficulty::Easy:
    this->setCurrentSpeed(1.2f);
    break;
  case EnemyDifficulty::Moderate:
    this->setCurrentSpeed(1.4f);
    break;
  case EnemyDifficulty::Hard:
    this->setCurrentSpeed(1.6f);
    break;
  }
}

void Enemy::setAttackTolerance(EnemyDifficulty type) {
  switch (type) {
  case EnemyDifficulty::Easy:
    this->attackTolerance = 1;
    break;
  case EnemyDifficulty::Moderate:
    this->attackTolerance = 2;
    break;
  case EnemyDifficulty::Hard:
    this->attackTolerance = 2;
    break;
  }
}


}  // namespace cave_mummies::entities
