// Copyright 2025 Jason Montenegro-Navarro

#ifndef CAVE_MUMMIES_ENTITIES_ENEMY_HPP
#define CAVE_MUMMIES_ENTITIES_ENEMY_HPP

#include <cstdint>
#include "Entity.hpp"

#ifdef __linux__
extern "C" {
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
   * @brief Updates enemy horizontal movement toward its objective.
   * @param currentSpeed Enemy speed attribute.
   * @param velocity Enemy velocity attribute.
   * @param objectiveX Objective x coordinate.
   * @param enemyX This enemy's x coordinate attribute.
   * @note This assembly function assumes arguments are always valid.
   */
  void updateEnemyLateralMovementStatus(float currentSpeed, float velocity
    , float objectiveX, float* enemyX);
}
#endif

namespace cave_mummies::entities {

class Player;

/**
 * @brief Represents the classification type of an enemy.
 */
enum class EnemyDifficulty {
  Easy,
  Moderate,
  Hard
};

/**
 * @brief Enemy entity that pursues and attacks the player.
 */
class Enemy : public Entity {
 protected:
  /// @brief Enemy sprite texture.
  const Texture2D& texture;
  /// @brief Indicates whether the player is still alive.
  bool isPlayerAlive{true};
  /// @brief Player target objective.
  cave_mummies::entities::Player& objective;
  /// @brief Enemy difficulty classification.
  EnemyDifficulty difficultyType{EnemyDifficulty::Easy};
  /// @brief Attack tolerance threshold before dying.
  uint32_t attackTolerance{0};
  /// @brief Number of projectile attacks received.
  uint32_t projectileAttacksReceived{0};

 public:
  /**
   * @brief Construct a new Enemy object.
   * @param game Game controller.
   * @param objective Target player that this enemy will follow.
   * @param diff Enemy difficulty classification.
   */
  explicit Enemy(cave_mummies::core::Game& game
    , cave_mummies::entities::Player &objective, EnemyDifficulty diff);

  /**
   * @brief Destroy the Enemy object.
   */
  ~Enemy() override = default;

  /**
   * @brief Updates this enemy’s state.
   */
  void update() override;

  /**
   * @brief Draws this enemy's sprite on the screen.
   */
  void draw() override;

  /**
   * @brief Checks whether the player followed by this enemy is alive.
   * @return true if alive, otherwise false.
   */
  inline bool getIsAlive() const {
    return this->isPlayerAlive;
  }

  /**
   * @brief Sets the alive condition of the player.
   * @param alive New alive status.
   */
  inline void setIsPlayerAlive(bool alive) {
    this->isPlayerAlive = alive;
  }

  /**
   * @brief Gets the difficulty classification of this enemy.
   * @return Enemy difficulty type.
   */
  inline EnemyDifficulty getDifficulty() const {
    return this->difficultyType;
  }

  /**
   * @brief Increments the number of projectile attacks received by one.
   */
  inline void incrementReceivedAttacks() {
    ++this->projectileAttacksReceived;
  }

  /**
   * @brief Gets the maximum attack tolerance of this enemy.
   * @return Attack tolerance value.
   */
  inline uint32_t getAttackTolerance() const {
    return this->attackTolerance;
  }

  /**
   * @brief Gets the number of projectile attacks received.
   * @return Number of attacks received.
   */
  inline uint32_t getReceivedAttacks() const {
    return this->projectileAttacksReceived;
  }

  /**
   * @brief Gets the texture associated with this enemy.
   * @return Reference to this enemy's texture.
   */
  const Texture2D& getTexture();

 protected:
  /**
   * @brief Sets this enemy’s velocity based on its difficulty.
   * @param type Enemy classification type.
   */
  void setVelocity(EnemyDifficulty type);

  /**
   * @brief Sets this enemy’s movement speed based on its difficulty.
   * @param type Enemy classification type.
   */
  void setSpeed(EnemyDifficulty type);

  /**
   * @brief Sets the attack tolerance limit based on difficulty.
   * @param type Enemy classification type.
   */
  void setAttackTolerance(EnemyDifficulty type);

  /**
   * @brief Updates this enemy’s lateral movement.
   */
  void updateLateralMovement();

  /**
   * @brief Updates this enemy’s sprite frame.
   */
  void updateSpriteFrame();
};

}  // namespace cave_mummies::entities

#endif  // CAVE_MUMMIES_ENTITIES_ENEMY_HPP
