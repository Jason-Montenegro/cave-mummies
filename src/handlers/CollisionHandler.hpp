// Copyright 2025 Jason Montenegro-Navarro

#ifndef COLLISION_HANDLER_HPP
#define COLLISION_HANDLER_HPP

#include <utility>
#include <vector>

#include "Entity.hpp"

using CollidingEntityPair =
  std::vector<std::pair<Entity*, Entity*>>;

/**
 * @brief Interface for handling collisions between game entities.
 */
class CollisionHandler {
 public:
  /**
   * @brief Constructor
   */
  CollisionHandler() = default;

  /**
   * @brief Destructor
   */
  ~CollisionHandler() = default;

  /**
   * @brief Checks collision between two entities.
   * @param a First entity
   * @param b Second entity
   * @return true if entities collide, false otherwise
   */
  bool checkCollision(const Entity& a, const Entity& b) const;

  /**
   * @brief Checks collisions for a group of entities.
   * @param entities Vector of entities to check
   * @return Vector of pairs of entities that are colliding
   */
  CollidingEntityPair checkCollisions(const std::vector<Entity> &entities)
    const;

  /**
   * @brief Handles collision response between two entities.
   * @param a First entity
   * @param b Second entity
   */
  void handleCollision(Entity &a, Entity &b);
};

#endif  // COLLISION_HANDLER_HPP
