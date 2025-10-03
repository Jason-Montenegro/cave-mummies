// Copyright 2025 Jason Montenegro-Navarro

#ifndef SPAWN_HANDLER_HPP
#define SPAWN_HANDLER_HPP

#include <memory>

#include "Player.hpp"
#include "Projectile.hpp"
#include "Enemy.hpp"

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
  inline std::unique_ptr<Enemy> spawnMummy(Player &objective
    , EnemyType type) const {
    return std::make_unique<Enemy>(objective, type);
  }

  /**
   * @brief Spawns the player character (Cat).
   * @return Unique pointer to a newly created Player entity
   */
  inline std::unique_ptr<Player> spawnPlayer() const {
    return std::make_unique<Player>();
  }

  /**
   * @brief Spawns a projectile at a given position with a given velocity.
   * @param position Starting position of the projectile
   * @param velocity Velocity vector of the projectile
   * @return Unique pointer to a newly created Projectile entity
   */
  inline std::unique_ptr<Projectile> spawnProjectile(const Vector2 &position
    , const Vector2 &velocity) const {
    auto projectile{std::make_unique<Projectile>(
      "assets/textures/projectiles/projectile-sprite.png")};
    projectile->setPosition(position);
    projectile->setVelocity(velocity);
    return projectile;
  }
};

#endif  // SPAWN_HANDLER_HPP
