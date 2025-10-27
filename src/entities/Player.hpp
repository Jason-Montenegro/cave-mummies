// Copyright 2025 Jason Montenegro-Navarro

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <cstdint>

#include "Entity.hpp"

namespace cave_mummies::entities {

/**
 * @brief Player entity
 */
class Player : public Entity {
 protected:
  /// @brief Default ammunition quantity
  static constexpr uint32_t defaultAmmunitionQuantity{12};
  /// @brief Entity kill count
  uint64_t killCount{0};
  /// @brief Remaining ammunition for shooting
  uint32_t remainingAmmunition{Player::defaultAmmunitionQuantity};
  /// @brief Reload speed
  static constexpr uint32_t reloadingSpeedInSeconds{2};
  /// @brief Gun reload sound effect
  Sound gunReloadSFX;
  /// @brief Gun shot sound effect
  Sound gunShotSFX;
  /// @brief Current game score
  uint64_t currentScore{0};
  /// @brief Sprint increment in velocity
  const float sprintVelocityBoost{0.8f};
  /// @brief Jumping condition
  bool isJumping{false};
  int32_t jumpCount{0};
  float jumpVelocity{0.0f};

 public:
  /**
   * @brief Constructor
   * @param game Game controller
   */
  Player(cave_mummies::core::Game& game);

  /**
   * @brief Destructor
   */
  ~Player();

  /**
   * @brief Updates this player state
   */
  void update() override;

  /**
   * @brief Draws player sprite to screen
   */
  void draw() override;

  /**
   * @brief Decrements jump count by one
   */
  inline void reduceJumpCount() {
    --this->jumpCount;
  }

  /**
   * @brief Getter of player kill count
   * @return this kill count
   */
  inline uint64_t getKillCount() const {
    return this->killCount;
  }

  /**
   * @brief Getter of remaining ammunition
   * @return this remaining ammunition
   */
  inline uint32_t getRemainingAmmunition() const {
    return this->remainingAmmunition;
  }

  /**
   * @brief Getter of current score
   * @return this current score
   */
  inline uint64_t getCurrentScore() const {
    return this->currentScore;
  }

  /**
   * @brief Increments the kill count by one
   */
  inline void incrementKillCount() {
    ++this->killCount;
  }

  /**
   * @brief Reloads ammunition to the max ammunition quantity
   */
  inline void reloadAmmunition() {
    this->remainingAmmunition = Player::defaultAmmunitionQuantity;
  }

  /**
   * @brief Decrement ammunition count by one
   */
  inline void decrementAmmunitionCount() {
    --this->remainingAmmunition;
  }

  /**
   * @brief Setter of the player score
   * @param score New score
   * @remark If score is < 0, it is converted to -score.
   */
  inline void setCurrentScore(int64_t score) {
    this->currentScore = (score < 0) ? -score : score;
  }

  /**
   * @brief Getter of gun reload sound effect
   * @return Reload sound effect
   */
  inline Sound& getReloadSoundEffect() {
    return this->gunReloadSFX;
  }
  /**
   * @brief Getter of gun shot sound effect
   * @return Gun shot sound effect
   */
  inline Sound& getGunShotSoundEffect() {
    return this->gunShotSFX;
  }

 protected:
   /**
   * @brief Calculates how much should the player jump, and updates
   * its position
   */
  void calculateAndDrawJump();

  /**
   * @brief Updates the sprinting status depending on player's input
   */
  void updatePlayerSprint();

  /**
   * @brief Updates player's lateral movement
   */
  void updateLateralMovement();

  /**
   * @brief Updates player's sprite frame, one frame per second
   */
  void updateSpriteFrame();

  /**
   * @brief Updates the player's position if it went through a wall
   */
  void updateWallWrapAround();

 private:
  /**
   * @brief Loads this object sprite texture
   */
  void loadTexture();
};

}  // cave_mummies::entities

#endif  // PLAYER_HPP
