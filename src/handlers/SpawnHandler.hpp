// Copyright 2025 Jason Montenegro-Navarro

#ifndef SPAWN_HANDLER_HPP
#define SPAWN_HANDLER_HPP

#include <memory>

#include "Player.hpp"
#include "Enemy.hpp"

namespace cave_mummies::handlers {

/**
 * @brief Spawn handler for entity creation.
 * Provides an interface to spawn all types of entities.
 */
class SpawnHandler {
 public:
  /**
   * @brief Constructor
   */
  SpawnHandler() = default;

  /**
   * @brief Destructor
   */
  ~SpawnHandler() = default;

  /**
   * @brief Spawns a mummy enemy.
   * @param objective Reference to the player that the enemy will target
   * @param type Enemy difficulty/type
   * @return Unique pointer to a newly created Enemy entity
   */
  inline std::unique_ptr<cave_mummies::entities::Enemy> spawnMummy(
      cave_mummies::entities::Player &objective
    , cave_mummies::entities::EnemyDifficulty type) const {
    return std::make_unique<cave_mummies::entities::Enemy>(objective, type);
  }

  /**
   * @brief Spawns the player character (Cat).
   * @return Unique pointer to a newly created Player entity
   */
  inline std::unique_ptr<cave_mummies::entities::Player> spawnPlayer() const {
    return std::make_unique<cave_mummies::entities::Player>();
  }
};

}  // cave_mummies::handlers

#endif  // SPAWN_HANDLER_HPP
