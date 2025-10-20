// Copyright 2025 Jason Montenegro-Navarro

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <cstdint>

#include "Entity.hpp"
#include "Game.hpp"

namespace cave_mummies::entities {

/**
 * @brief Entity that the player uses
 */
class Player : public Entity {
 private:
  /// @brief Default player values
  static constexpr uint32_t defaultAmmunitionQuantity{12};
  static constexpr const char* const defaultPlayerAssetPath
    {"assets/textures/entities/wil_player_skin.png"};
  /// @brief Alive player flag
  bool isAlive{true};
  /// @brief Entity kill count
  uint64_t killCount{0};
  /// @brief loaded ammunition remaining for shooting
  uint64_t loadedAmmunitionRemaining{Player::defaultAmmunitionQuantity};
  /// @brief Reload speed
  static constexpr uint32_t reloadingSpeedInSeconds{2};
  /// @brief Current game score
  uint64_t currentScore{0};
  /// @brief Sprint increment in velocity
  const float sprint_velocity_boost{1.1f};
  /// @brief Sprite frame
  int32_t currentSpriteFrame{0};
  /// @brief Sprite frame count
  int32_t spriteFrameCount{4};
  bool isJumping{false};
  int32_t jumpCount{0};
  float jumpVelocity{0.0f};

 public:
  /**
   * @brief Constructor
   * @param game Game controller
   * @param playerAssetPath Texture for player object
   */
  explicit Player(cave_mummies::core::Game& game
    , const char* const playerAssetPath = Player::defaultPlayerAssetPath)
    : Entity(game, playerAssetPath) { }

  /**
   * @brief Updates this player state.
   */
  void update() override;

  /**
   * @brief Draws player sprite to screen.
   */
  void draw() override;

  /**
   * @brief Checks if this player is alive.
   * @return true if alive, false otherwise
   */
  inline bool isPlayerAlive() const {
    return this->isAlive;
  }

  /**
   * @brief Gets the number of enemies killed by the player.
   * @return Kill count
   */
  inline uint64_t getKillCount() const {
    return this->killCount;
  }

  /**
   * @brief Gets the current amount of ammunition loaded to shoot.
   * @return Loaded ammunition remaining
   */
  inline uint64_t getLoadedAmmunitionRemaining() const {
    return this->loadedAmmunitionRemaining;
  }

  /**
   * @brief Gets the current score of the player.
   * @return Current score
   */
  inline uint64_t getCurrentScore() const {
    return this->currentScore;
  }

  /**
   * @brief Sets whether the player is alive.
   * @param alive true if alive, false otherwise
   */
  inline void setIsAlive(bool alive) {
    this->isAlive = alive;
  }

  /**
   * @brief Sets the number of enemies killed.
   * @param count New kill count
   * @remark If count is < 0, it is converted to -count.
   */
  inline void setKillCount(int32_t count) {
    this->killCount = (count < 0) ? -count : count;
  }

  /**
   * @brief Sets the current amount of ammunition loaded to shoot.
   * @param qty Ammunition quantity
   * @remark If qty is < 0, it is converted to -qty.
   */
  inline void setLoadedAmmunitionRemaining(int32_t qty) {
    this->loadedAmmunitionRemaining = (qty < 0) ? -qty : qty;
  }

  /**
   * @brief Sets the current score of the player.
   * @param score New score
   * @remark If score is < 0, it is converted to -score.
   */
  inline void setCurrentScore(int64_t score) {
    this->currentScore = (score < 0) ? -score : score;
  }

 private:
  /**
   * @brief Calculates how much should the player jump, and updates
   * its position.
   */
  void calculateAndDrawJump();
};

}  // cave_mummies::entities

#endif  // PLAYER_HPP
