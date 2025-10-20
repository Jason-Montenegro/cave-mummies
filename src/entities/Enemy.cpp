// Copyright 2025 Jason Montenegro-Navarro

#include "Enemy.hpp"
#include "Player.hpp"
#include "Game.hpp"

namespace cave_mummies::entities {

void Enemy::update() {
  // Move this enemy towards the objective
  const float newPosition{this->currentSpeed * this->velocity};
  const float distanceDiff{this->objective.getBounds().x - this->bounds.x};
  // this enemy y coordinate stays constant since instantiation
  if (distanceDiff < 0) {
    this->bounds.x -= newPosition;
  } else if (distanceDiff > 0) {
    this->bounds.x += newPosition;
  }
  this->currentSpriteFrame =
    ++this->currentSpriteFrame % this->spriteFrameCount;

  // Horizontal wall wrap-around
  const float screenWidth{static_cast<float>(GetScreenWidth())};
  // Walks on right wall, appears on left wall
  if (this->bounds.x > screenWidth) {
    this->bounds.x = -this->bounds.width;
  }
  // Walks on left wall, appears on right wall
  if (this->bounds.x + this->bounds.width < 0) {
    this->bounds.x = screenWidth;
  }
}

void Enemy::draw() {
  // Using the current sprite frame and the spritesheet, it selects which
  // frame is the correct one, and draws only that.
  const float frameWidth{static_cast<float>(this->texture.width / 4.0f)};
  const float frameHeight{static_cast<float>(this->texture.height)};
  const float characterScale{1.0f};

  // Always redirect this enemy facing towards the player
  const float distanceDiff{this->objective.getBounds().x - this->bounds.x};
  if (distanceDiff <= 0) {
    this->spriteDirection = cave_mummies::entities::Direction::Left;
  } else if (distanceDiff > 0) {
    this->spriteDirection = cave_mummies::entities::Direction::Right;
  }

  Rectangle sourceRec{
      this->currentSpriteFrame * frameWidth
    , 0
    , frameWidth
    , frameHeight};

  if (this->spriteDirection == cave_mummies::entities::Direction::Left) {
    sourceRec.width *= -1;
    sourceRec.x += frameWidth;
  }

  Rectangle destRec{
      this->bounds.x
    , this->bounds.y
    , frameWidth * characterScale
    , frameHeight * characterScale};

  DrawTexturePro(this->texture, sourceRec, destRec
    , (Vector2){0, 0}, 0.0f, WHITE);
}

}  // namespace cave_mummies::entities
