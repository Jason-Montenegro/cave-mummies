// Copyright 2025 Jason Montenegro-Navarro

#ifndef CAVE_MUMMIES_ENTITIES_PLAYER_HPP
#define CAVE_MUMMIES_ENTITIES_PLAYER_HPP

#include <cstdint>
#include "Entity.hpp"

namespace cave_mummies::entities {

/**
 * @brief Player entity.
 */
class Player : public Entity {
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
   * @brief Updates the player state
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
   * @brief Gets the player's total kill count.
   * @return Kill count value.
   */
  inline uint64_t getKillCount() const {
    return this->killCount;
  }

  /**
   * @brief Gets the remaining ammunition count.
   * @return Ammunition remaining.
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
   * @brief Updates the player sprite frame (once per second).
   */
  void updateSpriteFrame();

  /**
   * @brief Updates position if the player crosses a wall boundary.
   */
  void updateWallWrapAround();
};

}  // cave_mummies::entities

#endif  // CAVE_MUMMIES_ENTITIES_PLAYER_HPP
