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
  static constexpr const char* const enemyAssetPaths[3]{
    "../assets/textures/entities/wil_player_skin.png",
    "../assets/textures/entities/wil_player_skin.png",
    "../assets/textures/entities/wil_player_skin.png"
  };
  /// @brief Alive player flag
  bool isPlayerAlive{true};
  /// @brief Target objective
  cave_mummies::entities::Player& objective;
  /// @brief Enemy difficulty type
  EnemyDifficulty difficultyType{EnemyDifficulty::Moderate};

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
    : Entity(game, Enemy::getEnemyTextureFilename(diff))
    , objective(objective)
    , difficultyType(diff) {
    this->setVelocity(diff);
    this->setSpeed(diff);
  }

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

 protected:
  /**
   * @brief Sets this object velocity.
   * @param type Enemy type
   */
  inline void setVelocity(EnemyDifficulty type) {
    switch (type) {
    case EnemyDifficulty::Easy:
      this->velocity = this->baseVelocity = 2.0f;
      break;
    case EnemyDifficulty::Moderate:
      this->velocity = this->baseVelocity = 3.0f;
      break;
    case EnemyDifficulty::Hard:
      this->velocity = this->baseVelocity = 4.0f;
      break;
    }
  }

  /**
   * @brief Sets this object speed.
   * @param type Enemy classification type
   */
  inline void setSpeed(EnemyDifficulty type) {
    switch (type) {
    case EnemyDifficulty::Easy:
      this->setCurrentSpeed(1.2f);
      break;
    case EnemyDifficulty::Moderate:
      this->setCurrentSpeed(1.4f);
      break;
    case EnemyDifficulty::Hard:
      this->setCurrentSpeed(1.6f);
      break;
    }
  }

  /**
   * @brief Getter of enemy texture file name
   * @param type Enemy classification type
   * @return Texture file name
   */
  static inline const char* getEnemyTextureFilename(EnemyDifficulty type) {
    switch (type) {
    case EnemyDifficulty::Easy: return enemyAssetPaths[0];
    case EnemyDifficulty::Moderate: return enemyAssetPaths[1];
    case EnemyDifficulty::Hard: return enemyAssetPaths[2];
    default: return "";
    }
  }

  /**
   * @brief Updates this enemy lateral movement
   */
  void updateLateralMovement();

  /**
   * @brief Updates this enemy sprite frame, one frame per second
   */
  void updateSpriteFrame();

  /**
   * @brief Updates this enemy position if it went through a wall
   */
  void updateWallWrapAround();
};

}  // namespace cave_mummies::entities

#endif  // ENEMY_HPP
