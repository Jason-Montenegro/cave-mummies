// Copyright 2025 Jason Montenegro-Navarro

#include "Enemy.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "TextureManager.hpp"

namespace cave_mummies::entities {

Enemy::Enemy(cave_mummies::core::Game& game
  , cave_mummies::entities::Player &objective, EnemyDifficulty diff)
  : Entity(game)
  , texture(game.getTextureManager().getEnemyTexture(diff))
  , objective(objective)
  , difficultyType(diff) {
  this->setVelocity(diff);
  this->setSpeed(diff);
  this->setAttackTolerance(diff);
}

void Enemy::setVelocity(EnemyDifficulty type) {
  switch (type) {
  case EnemyDifficulty::Easy:
    this->velocity = this->baseVelocity = 2.0f;
    break;
  case EnemyDifficulty::Moderate:
    this->velocity = this->baseVelocity = 2.3f;
    break;
  case EnemyDifficulty::Hard:
    this->velocity = this->baseVelocity = 2.5f;
    break;
  default:
    this->velocity = this->baseVelocity = 2.0f;
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
    this->setCurrentSpeed(1.5f);
    break;
  default:
    this->setCurrentSpeed(1.2f);
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
  default:
    this->attackTolerance = 1;
  }
}

const Texture2D& Enemy::getTexture() {
  return this->texture;
}

void Enemy::update() {
  this->updateLateralMovement();
  this->updateSpriteFrame();
}

void Enemy::updateLateralMovement() {
  #ifdef __linux__
  updateEnemyLateralMovementStatus(this->currentSpeed, this->velocity
    , this->objective.getBounds().x, &this->bounds.x);
  #else
  // Move this enemy toward its objective
  const float newPosition{this->currentSpeed * this->velocity};
  const float distanceDiff{this->objective.getBounds().x - this->bounds.x};
  // this enemy y coordinate stays constant since instantiation
  if (distanceDiff < 0.0f) {
    this->bounds.x -= newPosition;
  } else if (distanceDiff > 0.0f) {
    this->bounds.x += newPosition;
  }
  #endif
}

void Enemy::updateSpriteFrame() {
  #ifdef __linux__
  updateSpriteFrameStatus(&this->gameFrameCounter, this->totalSpriteFrameCount
    , &this->currentSpriteFrame);
  #else
  // 60 because the game runs on 60 fps
  this->gameFrameCounter =
    (this->gameFrameCounter + this->totalSpriteFrameCount) % 60;
  if (this->gameFrameCounter == 0) {
    this->currentSpriteFrame =
      ++this->currentSpriteFrame % this->totalSpriteFrameCount;
  }
  #endif
}

void Enemy::draw() {
  // Using the current sprite frame and the spritesheet, it selects which
  // frame is the correct one, and draws only that
  const float frameWidth{static_cast<float>(this->texture.width / 4.0f)};
  const float frameHeight{static_cast<float>(this->texture.height)};
  const float characterScale{1.0f};
  // Always redirect this enemy facing towards the player
  const float distanceDiff{this->objective.getBounds().x - this->bounds.x};
  if (distanceDiff <= 0.0f) {
    this->currentDirection = cave_mummies::entities::Direction::Left;
  } else if (distanceDiff > 0.0f) {
    this->currentDirection = cave_mummies::entities::Direction::Right;
  }
  // Calculate the frame from the texture
  Rectangle sourceRec{this->currentSpriteFrame * frameWidth, 0.0f, frameWidth
    , frameHeight};
  if (this->currentDirection == cave_mummies::entities::Direction::Left) {
    sourceRec.width *= -1.0f;
  }
  Rectangle destRec{this->bounds.x, this->bounds.y, frameWidth * characterScale
    , frameHeight * characterScale
  };
  if (this->currentDirection == cave_mummies::entities::Direction::Left) {
    // Adjusts texture when its flipped to the left
    destRec.x -= frameWidth / 2;
  }
  DrawTexturePro(this->texture, sourceRec, destRec, {0.0f, 0.0f}, 0.0f, WHITE);
  #ifdef DEBUG
  // Draws hitbox
  DrawRectangleLines(this->bounds.x, this->bounds.y, this->bounds.width,
    this->bounds.height, RED);
  #endif
}

}  // namespace cave_mummies::entities
