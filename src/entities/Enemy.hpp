// Copyright 2025 Jason Montenegro-Navarro

#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <cstdlib>

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
  /// @brief Default enemy values
  static constexpr uint32_t defaultEnemyVelocity{5};
  static constexpr const char* const defaultEnemyAssetPath[3]{
    "../assets/textures/entities/wil_player_skin.png",
    "../assets/textures/entities/wil_player_skin.png",
    "../assets/textures/entities/wil_player_skin.png"
  };
  /// @brief Alive player flag
  bool isAlive{true};
  /// @brief Target objective
  cave_mummies::entities::Player& objective;
  /// @brief Enemy difficulty type
  EnemyDifficulty difficultyType{EnemyDifficulty::Easy};
  /// @brief Sprite frame
  int32_t currentSpriteFrame{0};
  /// @brief Sprite frame count
  int32_t spriteFrameCount{4};

 public:
  /**
   * @brief Constructor
   * @param game Game controller
   * @param objective Target objective this enemy will follow
   * @param diff Enemy difficulty type
   */
  explicit Enemy(cave_mummies::core::Game& game
    , cave_mummies::entities::Player &objective
    , EnemyDifficulty diff = EnemyDifficulty::Easy)
    : Entity(game, defaultEnemyAssetPath[static_cast<int>(diff)])
    , objective(objective)
    , difficultyType(diff) {
    this->setVelocity(diff);
    this->setSpeed(diff);
    this->isAlive = true;
  }

  /**
   * @brief Updates this enemy state.
   */
  void update() override;

  /**
   * @brief Draws enemy sprite on the screen.
   */
  void draw() override;

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
    return this->difficultyType;
  }

 protected:
  /**
   * @brief Sets this object velocity.
   * @param type Enemy type
   */
  inline void setVelocity(EnemyDifficulty type) {
    switch (type) {
    case EnemyDifficulty::Easy:
      this->velocity = 1.5f;
      break;
    case EnemyDifficulty::Moderate:
      this->velocity = 2.0f;
      break;
    case EnemyDifficulty::Hard:
      this->velocity = 3.0f;
      break;
    }
  }

  /**
   * @brief Sets this object speed.
   * @param type Enemy type
   */
  inline void setSpeed(EnemyDifficulty type) {
    switch (type) {
    case EnemyDifficulty::Easy:
      this->setCurrentSpeed(1.5f);
      break;
    case EnemyDifficulty::Moderate:
      this->setCurrentSpeed(1.7f);
      break;
    case EnemyDifficulty::Hard:
      this->setCurrentSpeed(2.0f);
      break;
    }
  }
};

}  // namespace cave_mummies::entities

#endif  // ENEMY_HPP
