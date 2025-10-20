// Copyright 2025 Jason Montenegro-Navarro

#include "Player.hpp"

namespace cave_mummies::entities {

void Player::update() {
  auto& input{this->game.getInputHandler()};
  static const float baseVelocity{this->velocity};

  if (input.isKeyDown(KEY_LEFT_SHIFT)) {
    this->velocity = baseVelocity + baseVelocity * this->sprint_velocity_boost;
  }
  if (input.isKeyReleased(KEY_LEFT_SHIFT)) {
    this->velocity = baseVelocity;
  }

  // Lateral movement
  const float newPosition{this->currentSpeed * this->velocity};
  if (input.isKeyDown(KEY_A) || input.isKeyDown(KEY_LEFT)) {
    this->bounds.x -= newPosition;
  }
  if (input.isKeyDown(KEY_D) || input.isKeyDown(KEY_RIGHT)) {
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

  calculateAndDrawJump();
}

void Player::calculateAndDrawJump() {
  auto& input{this->game.getInputHandler()};
  const float groundY{this->game.getGameStageFloorHeight()};
  const float gravity{1.5f};
  const float jumpStrength{22.0f};
  const int maxJumps{2};
  bool jumpKeyDown{input.isPressed(KEY_W) || input.isPressed(KEY_SPACE)};

  if (jumpKeyDown && this->jumpCount < maxJumps) {
    this->isJumping = true;
    this->jumpVelocity = -jumpStrength;
    ++this->jumpCount;
  }

  if (this->isJumping) {
    const float newPosition{this->bounds.y + this->jumpVelocity};
    this->jumpVelocity += gravity;

    if (newPosition < 0.0f) {
      this->bounds.y = 0.0f;
      this->jumpVelocity = 0.0f;
    } else if (newPosition >= groundY - this->texture.height) {
      this->bounds.y = groundY - this->texture.height;
      this->jumpVelocity = 0.0f;
      this->jumpCount = 0;
      isJumping = false;
    } else {
      this->bounds.y = newPosition;
    }
  }
}

void Player::draw() {
  // Using the current sprite frame and the spritesheet, it selects which
  // frame is the correct one, and draws only that.
  auto& input{this->game.getInputHandler()};
  const float frameWidth{static_cast<float>(this->texture.width / 4.0f)};
  const float frameHeight{static_cast<float>(this->texture.height)};
  const float characterScale{1.0f};
  if (input.isKeyDown(KEY_A) || input.isKeyDown(KEY_LEFT)) {
    this->spriteDirection = cave_mummies::entities::Direction::Left;
  } else if (input.isKeyDown(KEY_D) || input.isKeyDown(KEY_RIGHT)) {
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
