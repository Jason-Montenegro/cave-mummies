#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <cstdlib>

#include "Entity.hpp"
#include "Player.hpp"

/**
 * @brief Enemy classification type
 */
enum class EnemyType {
  Easy,
  Moderate,
  Hard
};

/**
 * @brief Enemy entity
 */
class Enemy : public Entity {
 private:
  /// @brief Default enemy values
  static constexpr uint32_t defaultEnemyVelocity{5};
  static constexpr const char *const defaultEnemyAssetPath[3]{
    "assets/textures/entities/mummy-easy-diff-sprite.png",
    "assets/textures/entities/mummy-moderate-diff-sprite.png",
    "assets/textures/entities/mummy-hard-diff-sprite.png",
  };
  /// Alive player flag
  bool isAlive{true};
  /// Target objective
  Player &objective;
  /// Enemy type
  EnemyType type{EnemyType::Easy};

 public:
  /**
   * @brief Constructor
   * @param objective Target objective this will follow
   * @param type Enemy type
   */
  explicit Enemy(Player &objective, EnemyType type = EnemyType::Easy)
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
  inline bool getIsAlive() const { return this->isAlive; }
  /**
   * @brief Sets this enemy alive condition.
   * @param alive Alive condition
   */
  inline void setIsAlive(bool alive) { this->isAlive = alive; }

  /**
   * @brief Gets the type of enemy
   * @return EnemyType Type of enemy
   */
  inline EnemyType getType() const { return this->type; }

 private:
  /**
   * @brief Sets this object velocity
   * @param type Enemy type
   */
  inline void setVelocity(EnemyType type) {
    switch (type) {
      case EnemyType::Easy:
        this->velocity = {1.0f, 1.0f};
        break;
      case EnemyType::Moderate:
        this->velocity = {2.0f, 2.0f};
        break;
      case EnemyType::Hard:
        this->velocity = {3.0f, 3.0f};
        break;
    }
  }
};

#endif  // ENEMY_HPP
