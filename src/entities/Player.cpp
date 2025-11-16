// Copyright 2025 Jason Montenegro-Navarro

#include <string>
#include "Player.hpp"
#include "Game.hpp"
#include "InputHandler.hpp"
#include "TextureManager.hpp"

using TextureID = cave_mummies::core::TextureID;

namespace cave_mummies::entities {

Player::Player(cave_mummies::core::Game& game)
  : Entity(game)
  , texture(game.getTextureManager().getTexture(TextureID::PlayerSprite)) {
  this->velocity = this->baseVelocity = 3.0f;
  this->currentSpeed = 3.0f;
  std::string basePath{GetApplicationDirectory()};
  // Load sound effects
  this->gunReloadSFX = LoadSound((basePath
    + std::string("../assets/audio/sfx/gun-cocking-sfx.wav")).c_str());
  this->gunShotSFX = LoadSound((basePath
    + std::string("../assets/audio/sfx/gun-shot-sfx.wav")).c_str());
}

Player::~Player() {
  if (this->gunReloadSFX.frameCount > 0) {
    UnloadSound(this->gunReloadSFX);
  }
  if (this->gunShotSFX.frameCount > 0) {
    UnloadSound(this->gunShotSFX);
  }
}

void Player::update() {
  this->updatePlayerSprint();
  this->updateLateralMovement();
  this->updateSpriteFrame();
  this->updateWallWrapAround();
  this->calculateAndDrawJump();
}

void Player::updatePlayerSprint() {
  auto& input{this->game.getInputHandler()};
  #ifdef __linux__
  updatePlayerSprintStatus(input.isKeyDown(KEY_LEFT_SHIFT), &this->velocity
    , this->baseVelocity, this->sprintVelocityBoost
    , input.isKeyReleased(KEY_LEFT_SHIFT));
  #else
  if (input.isKeyDown(KEY_LEFT_SHIFT)) {
    this->velocity = this->baseVelocity
      + this->baseVelocity * this->sprintVelocityBoost;
  }
  if (input.isKeyReleased(KEY_LEFT_SHIFT)) {
    this->velocity = this->baseVelocity;
  }
  #endif
}

void Player::updateLateralMovement() {
  auto& input{this->game.getInputHandler()};
  #ifdef __linux__
  const bool leftDirection{input.isKeyDown(KEY_A) || input.isKeyDown(KEY_LEFT)};
  const bool rightDirection{input.isKeyDown(KEY_D)
    || input.isKeyDown(KEY_RIGHT)};
  updateLateralMovementStatus(leftDirection, rightDirection, this->velocity
    , this->currentSpeed, &this->bounds.x);
  #else
  const float newPosition{this->velocity * this->currentSpeed};
  if (input.isKeyDown(KEY_A) || input.isKeyDown(KEY_LEFT)) {
    this->bounds.x -= newPosition;
  }
  if (input.isKeyDown(KEY_D) || input.isKeyDown(KEY_RIGHT)) {
    this->bounds.x += newPosition;
  }
  #endif
}

void Player::updateSpriteFrame() {
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

void Player::updateWallWrapAround() {
  // Horizontal wall wrap-around
  const float screenWidth{static_cast<float>(GetScreenWidth())};
  #ifdef __linux__
  updateWallWrapAroundBehviour(screenWidth, &this->bounds.x
    , this->bounds.width);
  #else
  // Walks on right wall, appears on left wall
  if (this->bounds.x > screenWidth) {
    this->bounds.x = -this->bounds.width;
  }
  // Walks on left wall, appears on right wall
  if (this->bounds.x + this->bounds.width < 0.0f) {
    this->bounds.x = screenWidth;
  }
  #endif
}

void Player::calculateAndDrawJump() {
  auto& input{this->game.getInputHandler()};
  const float groundY{this->game.getGameStageFloorHeight()};
  const bool jumpKeyDown{input.isPressed(KEY_W) || input.isPressed(KEY_UP)
    || input.isPressed(KEY_SPACE)};

  #ifdef __linux__
  consumePlayerJump(jumpKeyDown, &this->jumpCount, &this->isJumping
    , &this->jumpVelocity);
  updatePlayerJumpStatus(&this->isJumping, &this->bounds.y, &this->jumpVelocity
    , groundY, this->texture.height, &this->jumpCount);
  #else
  const float gravity{1.5f};
  const float jumpStrength{30.0f};
  const int32_t maxJumps{2};

  if (jumpKeyDown && this->jumpCount < maxJumps) {
    // Use an available jump
    this->isJumping = true;
    this->jumpVelocity = -jumpStrength;
    ++this->jumpCount;
  }

  if (this->isJumping) {
    const float newPosition{this->bounds.y + this->jumpVelocity};
    this->jumpVelocity += gravity;
    if (newPosition < 0.0f) {
      // Below ground level
      this->bounds.y = 0.0f;
      this->jumpVelocity = 0.0f;
    } else if (newPosition >= groundY - this->texture.height) {
      // On ground level
      this->bounds.y = groundY - this->texture.height;
      this->jumpVelocity = 0.0f;
      this->jumpCount = 0;
      this->isJumping = false;
    } else {
      // Above ground level
      this->bounds.y = newPosition;
    }
  }
  #endif
}

void Player::draw() {
  auto& input{this->game.getInputHandler()};
  // Using the current sprite frame and the spritesheet, it selects which
  // frame is the correct one, and draws only that
  const float frameWidth{static_cast<float>(
    this->texture.width / this->totalSpriteFrameCount)};
  const float frameHeight{static_cast<float>(this->texture.height)};
  const float characterScale{1.0f};
  if (input.isKeyDown(KEY_A) || input.isKeyDown(KEY_LEFT)) {
    this->currentDirection = cave_mummies::entities::Direction::Left;
  } else if (input.isKeyDown(KEY_D) || input.isKeyDown(KEY_RIGHT)) {
    this->currentDirection = cave_mummies::entities::Direction::Right;
  }

  // Calculate the frame from the texture
  Rectangle sourceRec{this->currentSpriteFrame * frameWidth, 0.0f, frameWidth
    , frameHeight};
  if (this->currentDirection == cave_mummies::entities::Direction::Left) {
    sourceRec.width *= -1.0f;
    sourceRec.x += frameWidth;
  }
  Rectangle destRec{this->bounds.x, this->bounds.y, frameWidth * characterScale
    , frameHeight * characterScale
  };
  DrawTexturePro(this->texture, sourceRec, destRec, {0.0f, 0.0f}, 0.0f, WHITE);
}

}  // namespace cave_mummies::entities
