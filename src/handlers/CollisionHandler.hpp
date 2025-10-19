// Copyright 2025 Jason Montenegro-Navarro

#ifndef COLLISION_HANDLER_HPP
#define COLLISION_HANDLER_HPP

#include <utility>
#include <vector>

#include "Entity.hpp"

using CollidingEntityPair =
  std::vector<std::pair<cave_mummies::entities::Entity*
  , cave_mummies::entities::Entity*>>;

namespace cave_mummies::handlers {

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
  bool checkCollision(const cave_mummies::entities::Entity& a
    , const cave_mummies::entities::Entity& b) const;

  /**
   * @brief Checks collisions for a group of entities.
   * @param entities Vector of entities to check
   * @return Vector of pairs of entities that are colliding
   */
  CollidingEntityPair checkCollisions(
    const std::vector<cave_mummies::entities::Entity> &entities) const;

  /**
   * @brief Handles collision response between two entities.
   * @param a First entity
   * @param b Second entity
   */
  void handleCollision(cave_mummies::entities::Entity& a
    , cave_mummies::entities::Entity& b);
};

}  // cave_mummies::handlers

#endif  // COLLISION_HANDLER_HPP
