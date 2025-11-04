// Copyright 2025 Jason Montenegro-Navarro

#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <cstdint>

#include "Entity.hpp"

namespace cave_mummies::entities {

class Player;

/**
 * @brief Enemy classification type
 */
enum class EnemyDifficulty {
  Easy,
  Moderate,
  Hard
};

/**
 * @brief Enemy entity that attacks the player
 */
class Enemy : public Entity {
 protected:
  /// @brief Enemy texture
  const Texture2D& texture;
  /// @brief Alive player flag
  bool isPlayerAlive{true};
  /// @brief Target objective
  cave_mummies::entities::Player& objective;
  /// @brief Enemy difficulty type
  EnemyDifficulty difficultyType{EnemyDifficulty::Easy};
  /// @brief Attack tolerance for player projectiles
  uint32_t attackTolerance{0};
  /// @brief Attacks received
  uint32_t projectileAttacksReceived{0};

 public:
  /**
   * @brief Constructor
   * @param game Game controller
   * @param objective Target objective this enemy will follow
   * @param diff Enemy difficulty type
   */
  explicit Enemy(cave_mummies::core::Game& game
    , cave_mummies::entities::Player &objective, EnemyDifficulty diff);

  /**
   * @brief Destructor
   */
  ~Enemy() override = default;

  /**
   * @brief Updates this enemy state
   */
  void update() override;

  /**
   * @brief Draws enemy sprite on the screen
   */
  void draw() override;

  /**
   * @brief Checks if this enemy is alive
   * @return true if alive, otherwise false
   */
  inline bool getIsAlive() const {
    return this->isPlayerAlive;
  }

  /**
   * @brief Setter of alive player condition
   * @param alive Alive condition
   */
  inline void setIsPlayerAlive(bool alive) {
    this->isPlayerAlive = alive;
  }

  /**
   * @brief Gets this enemy difficulty type
   * @return this enemy difficulty classification type
   */
  inline EnemyDifficulty getDifficulty() const {
    return this->difficultyType;
  }

  /**
   * @brief Increments the projectile attacks received counter by one
   */
  inline void incrementReceivedAttacks() {
    ++this->projectileAttacksReceived;
  }

  /**
   * @brief Getter of this enemy attack tolerance
   */
  inline uint32_t getAttackTolerance() const {
    return this->attackTolerance;
  }

  /**
   * @brief Getter of this enemy projectile attacks received
   */
  inline uint32_t getReceivedAttacks() const {
    return this->projectileAttacksReceived;
  }

  /**
   * @brief Getter of this enemy object texture
   * @return Enemy texture
   */
  const Texture2D& getTexture();

 protected:
  /**
   * @brief Sets this object velocity
   * @param type Enemy type
   */
  void setVelocity(EnemyDifficulty type);

  /**
   * @brief Sets this object speed
   * @param type Enemy classification type
   */
  void setSpeed(EnemyDifficulty type);

  /**
   * @brief Sets this object attack tolerance to player's projectiles
   * @param type Enemy classification type
   */
  void setAttackTolerance(EnemyDifficulty type);

  /**
   * @brief Updates this enemy lateral movement
   */
  void updateLateralMovement();

  /**
   * @brief Updates this enemy sprite frame, one frame per second
   */
  void updateSpriteFrame();
};

}  // namespace cave_mummies::entities

#endif  // ENEMY_HPP
