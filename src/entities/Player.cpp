// Copyright 2025 Jason Montenegro-Navarro

#include <string>

#include <stdexcept>

#include "Game.hpp"
#include "Player.hpp"
#include "InputHandler.hpp"

/**
 * @brief Updates the sprinting status depending on player's input
 * @param velocity Pointer to the player's current velocity
 * @param baseVelocity The player's base velocity
 * @param sprintVelocityBoost The additional velocity applied during a sprint
 * @param isShiftDown True if the sprint key is currently pressed
 * @param isShiftReleased True if the sprint key has just been released
 * @note Assembly (NASM) function for Linux-based machines
 * @note Modifies velocity argument
 */
extern "C" void update_player_sprint(float* velocity, float baseVelocity,
  float sprintVelocityBoost, bool isShiftDown, bool isShiftReleased);

namespace cave_mummies::entities {

Player::Player(cave_mummies::core::Game& game)
  : Entity(game) {
  this->velocity = this->baseVelocity = 3.0f;
  this->currentSpeed = 3.0f;
  std::string basePath{GetApplicationDirectory()};
  this->loadTexture();
  // Load sound effects
  this->gunReloadSFX = LoadSound((basePath
    + std::string("../assets/audio/sfx/gun-cocking-sfx.wav")).c_str());
  this->gunShotSFX = LoadSound((basePath
    + std::string("../assets/audio/sfx/gun-shot-sfx.wav")).c_str());
}

void Player::loadTexture() {
  if (texture.id != 0) {
    UnloadTexture(texture);
  }
  std::string filename{game.getGameTextures().getPlayerTextureFilename()};
  std::string basePath{GetApplicationDirectory()};
  Image img{LoadImage((basePath + filename).c_str())};
  if (!img.data) {
    throw std::runtime_error("Failed to load player texture: "
      + std::string(filename));
  }
  const int32_t newWidth{static_cast<int32_t>(img.width * 0.1f)};
  const int32_t newHeight{static_cast<int32_t>(img.height * 0.1f)};
  ImageResize(&img, newWidth, newHeight);
  this->texture = LoadTextureFromImage(img);
  UnloadImage(img);
}

Player::~Player() {
  if (this->texture.id != 0) {
    UnloadTexture(this->texture);
  }
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
  /*
  #ifdef __linux__
    update_player_sprint(&this->velocity, this->baseVelocity,
      this->sprintVelocityBoost, input.isKeyDown(KEY_LEFT_SHIFT),
      input.isKeyReleased(KEY_LEFT_SHIFT));
  #else
  */
    if (input.isKeyDown(KEY_LEFT_SHIFT)) {
      this->velocity = this->baseVelocity
        + this->baseVelocity * this->sprintVelocityBoost;
    }
    if (input.isKeyReleased(KEY_LEFT_SHIFT)) {
      this->velocity = this->baseVelocity;
    }
  //#endif
}

void Player::updateLateralMovement() {
  auto& input{this->game.getInputHandler()};
  const float newPosition{this->velocity * this->currentSpeed};
  if (input.isKeyDown(KEY_A) || input.isKeyDown(KEY_LEFT)) {
    this->bounds.x -= newPosition;
  }
  if (input.isKeyDown(KEY_D) || input.isKeyDown(KEY_RIGHT)) {
    this->bounds.x += newPosition;
  }
  // TODO(Jason): set up asm function
}

void Player::updateSpriteFrame() {
  // 60 because the game runs on 60 fps
  this->gameFrameCounter = (gameFrameCounter + 4) % 60;
  if (this->gameFrameCounter == 0) {
    this->currentSpriteFrame =
      ++this->currentSpriteFrame % this->spriteFrameCount;
  }
}

void Player::updateWallWrapAround() {
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
  // TODO(Jason): set up asm function
}

void Player::calculateAndDrawJump() {
  auto& input{this->game.getInputHandler()};
  const float groundY{this->game.getGameStageFloorHeight()};
  const float gravity{1.5f};
  const float jumpStrength{30.0f};
  const int maxJumps{2};
  bool jumpKeyDown{input.isPressed(KEY_W) || input.isPressed(KEY_UP)
    || input.isPressed(KEY_SPACE)};

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
      this->isJumping = false;
    } else {
      this->bounds.y = newPosition;
    }
  }
  // TODO(jason): set up asm function
}

void Player::draw() {
  auto& input{this->game.getInputHandler()};
  // Using the current sprite frame and the spritesheet, it selects which
  // frame is the correct one, and draws only that
  const float frameWidth{static_cast<float>(
    this->texture.width / this->spriteFrameCount)};
  const float frameHeight{static_cast<float>(this->texture.height)};
  const float characterScale{1.0f};
  if (input.isKeyDown(KEY_A) || input.isKeyDown(KEY_LEFT)) {
    this->currentDirection = cave_mummies::entities::Direction::Left;
  } else if (input.isKeyDown(KEY_D) || input.isKeyDown(KEY_RIGHT)) {
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

}  // namespace cave_mummies::entities
