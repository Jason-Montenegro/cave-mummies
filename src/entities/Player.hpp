// Copyright 2025 Jason Montenegro-Navarro

#ifndef CAVE_MUMMIES_ENTITIES_PLAYER_HPP
#define CAVE_MUMMIES_ENTITIES_PLAYER_HPP

#include <cstdint>
#include "Entity.hpp"

#ifdef __linux__
extern "C" {
  /**
   * @brief Updates player sprinting status based on input.
   * @param isKeyDown Is key currently down condition.
   * @param velocity Player velocity attribute pointer.
   * @param baseVelocity Player base velocity attribute.
   * @param sprintVelocityBoost Player sprint velocity boost attribute.
   * @param isKeyReleased Is key released condition.
   * @note This assembly function assumes arguments are always valid.
   */
  void updatePlayerSprintStatus(bool isKeyDown, float* velocity
    , float baseVelocity, float sprintVelocityBoost, bool isKeyReleased);

  /**
   * @brief Updates player lateral movement based on input.
   * @param leftDirection Left direction keys down condition.
   * @param rightDirection Right direction keys down condition.
   * @param velocity Player velocity attribute.
   * @param currentSpeed Player current speed attribute
   * @param xCoordinate Player x coordinate attribute pointer
   * @note This assembly function assumes arguments are always valid.
   */
  void updateLateralMovementStatus(bool leftDirection, bool rightDirection
    , float velocity, float currentSpeed, float* xCoordinate);

  /**
   * @brief Updates the sprite frame.
   * @param gameFrameCounter Current game frame counter.
   * @param totalSpriteFrameCount Total sprite frame count of loaded texture. 
   * @param currentSpriteFrame Current sprite frame of loaded texture.
   * @note This assembly function assumes arguments are always valid.
   */
  void updateSpriteFrameStatus(int32_t* gameFrameCounter
    , int32_t totalSpriteFrameCount, int32_t* currentSpriteFrame);

  /**
   * @brief Updates position if the player crosses a wall boundary.
   * @param screenWidth Screen width.
   * @param xCoordinate Player object x coordinate.
   * @param playerWidth Player texture width.
   * @note This assembly function assumes arguments are always valid.
   */
  void updateWallWrapAroundBehviour(float screenWidth, float* xCoordinate
    , float playerWidth);
  
  /**
   * @brief Consumes a single jump from player jump count if available.
   * @param jumpKeyDown Jump key pressed condition.
   * @param jumpCount Player jump count attribute.
   * @param isJumping Player jump status attribute.
   * @param jumpVelocity Jump velocity to modify.
   * @note This assembly function assumes arguments are always valid.
   */
  void consumePlayerJump(bool jumpKeyDown, int32_t* jumpCount, bool* isJumping
  , float* jumpVelocity);

  /**
   * @brief Updates jump state and vertical position of the player.
   * @param isJumping Player jump status attribute.
   * @param yCoordinate Player object y coordinate.
   * @param jumpVelocity Vertical jump velocity.
   * @param groundY Ground reference height.
   * @param playerHeight Player texture height.
   * @param jumpCount Player jump count attribute.
   * @note This assembly function assumes arguments are always valid.
   */
  void updatePlayerJumpStatus(bool* isJumping, float* yCoordinate
    , float* jumpVelocity, float groundY, float playerHeight
    , int32_t* jumpCount);
}
#endif

namespace cave_mummies::entities {

/**
 * @brief Player entity.
 */
class Player : public Entity {
 protected:
   /// @brief Default ammunition quantity.
  static constexpr uint32_t defaultAmmunitionQuantity{12};
  /// @brief Player texture.
  const Texture2D& texture;
  /// @brief Total enemies defeated by the player.
  uint64_t killCount{0};
  /// @brief Remaining ammunition for shooting.
  uint32_t remainingAmmunition{Player::defaultAmmunitionQuantity};
  /// @brief Gun reload speed.
  static constexpr uint32_t reloadingSpeedInSeconds{2};
  /// @brief Gun reload sound effect.
  Sound gunReloadSFX;
  /// @brief Gun shot sound effect.
  Sound gunShotSFX;
  /// @brief Current game score.
  uint64_t currentScore{0};
  /// @brief Sprint velocity increment.
  const float sprintVelocityBoost{0.8f};
  /// @brief Indicates whether the player is jumping.
  bool isJumping{false};
  /// @brief Remaining number of jumps available.
  int32_t jumpCount{0};
  /// @brief Vertical velocity during jump.
  float jumpVelocity{0.0f};

 public:
  /**
   * @brief Construct a new Player object.
   * @param game Game controller.
   */
  Player(cave_mummies::core::Game& game);

  /**
   * @brief Destroy the Player object.
   */
  ~Player();

  /**
   * @brief Updates the player state.
   */
  void update() override;

  /**
   * @brief Draws the player sprite on screen.
   */
  void draw() override;

  /**
   * @brief Decrements the jump counter by one.
   */
  inline void reduceJumpCount() {
    --this->jumpCount;
  }

  /**
   * @brief Increments the kill count by one.
   */
  inline void incrementKillCount() {
    ++this->killCount;
  }

  /**
   * @brief Gets the this player total kill count.
   * @return Kill count.
   */
  inline uint64_t getKillCount() const {
    return this->killCount;
  }

  /**
   * @brief Gets the remaining ammunition count.
   * @return Remaining ammunition.
   */
  inline uint32_t getRemainingAmmunition() const {
    return this->remainingAmmunition;
  }

  /**
   * @brief Reloads ammunition to the maximum quantity.
   */
  inline void reloadAmmunition() {
    this->remainingAmmunition = Player::defaultAmmunitionQuantity;
  }
  
  /**
   * @brief Decrements the ammunition count by one.
   */
  inline void decrementAmmunitionCount() {
    --this->remainingAmmunition;
  }

  /**
   * @brief Gets the current player score.
   * @return Current score.
   */
  inline uint64_t getCurrentScore() const {
    return this->currentScore;
  }

  /**
   * @brief Sets the player score.
   * @param score New score value (negative values are converted to positive).
   */
  inline void setCurrentScore(int64_t score) {
    this->currentScore = (score < 0) ? -score : score;
  }

  /**
   * @brief Gets the gun reload sound effect.
   * @return Reference to reload sound effect.
   */
  inline Sound& getReloadSoundEffect() {
    return this->gunReloadSFX;
  }

  /**
   * @brief Gets the gun shot sound effect.
   * @return Reference to gun shot sound effect.
   */
  inline Sound& getGunShotSoundEffect() {
    return this->gunShotSFX;
  }

  /**
   * @brief Get the reloading speed in seconds.
   * @return Reloading speed in seconds.
   */
  inline constexpr uint32_t getReloadingSpeedInSeconds() {
    return this->reloadingSpeedInSeconds;
  }

 protected:
  /**
   * @brief Calculates jump height and updates position.
   */
  void calculateAndDrawJump();

  /**
   * @brief Updates sprinting status based on input.
   */
  void updatePlayerSprint();

  /**
   * @brief Updates lateral movement based on input.
   */
  void updateLateralMovement();

  /**
   * @brief Updates the player sprite frame.
   */
  void updateSpriteFrame();

  /**
   * @brief Updates position if the player crosses a wall boundary.
   */
  void updateWallWrapAround();
};

}  // cave_mummies::entities

#endif  // CAVE_MUMMIES_ENTITIES_PLAYER_HPP
