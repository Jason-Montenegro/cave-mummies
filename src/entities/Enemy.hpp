// Copyright 2025 Jason Montenegro-Navarro

#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <cstdlib>

#include "Entity.hpp"
#include "Player.hpp"

namespace cave_mummies::entities {

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
 private:
  /// @brief Default enemy values
  static constexpr uint32_t defaultEnemyVelocity{5};
  static constexpr const char* const defaultEnemyAssetPath[3]{
    "",
    "",
    ""
  };
  /// @brief Alive player flag
  bool isAlive{true};
  /// @brief Target objective
  Player& objective;
  /// @brief Enemy difficulty type
  EnemyDifficulty type{EnemyDifficulty::Easy};

 public:
  /**
   * @brief Constructor
   * @param objective Target objective this will follow
   * @param type Enemy type
   */
  explicit Enemy(Player &objective
    , EnemyDifficulty type = EnemyDifficulty::Easy)
    : Entity(defaultEnemyAssetPath[static_cast<int>(type)])
    , objective(objective), type(type) {
    this->setVelocity(type);
    this->isAlive = true;
  }

  /**
   * @brief Updates this enemy state.
   */
  void update() override;

  /**
   * @brief Checks if this enemy is alive.
   * @return true if alive, false otherwise
   */
  inline bool getIsAlive() const {
    return this->isAlive;
  }

  /**
   * @brief Sets this enemy alive condition.
   * @param alive Alive condition
   */
  inline void setIsAlive(bool alive) {
    this->isAlive = alive;
  }

  /**
   * @brief Gets the enemy difficulty.
   * @return EnemyType Type of enemy
   */
  inline EnemyDifficulty getDifficulty() const {
    return this->type;
  }

 private:
  /**
   * @brief Sets this object velocity.
   * @param type Enemy type
   */
  inline void setVelocity(EnemyDifficulty type) {
    switch (type) {
    case EnemyDifficulty::Easy:
      this->velocity = {1.0f, 1.0f};
      break;
    case EnemyDifficulty::Moderate:
      this->velocity = {2.0f, 2.0f};
      break;
    case EnemyDifficulty::Hard:
      this->velocity = {3.0f, 3.0f};
      break;
    }
  }
};

}  // namespace cave_mummies::entities

#endif  // ENEMY_HPP
