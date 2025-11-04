// Copyright 2025 Jason Montenegro-Navarro

#ifndef COLLISION_HANDLER_HPP
#define COLLISION_HANDLER_HPP

#include "raylib.h"

namespace cave_mummies::handlers {

/**
 * @brief Interface for handling collisions between game entities
 */
class CollisionHandler {
 public:
  /**
   * @brief Checks collision between two entities
   * @param a First entity
   * @param b Second entity
   * @return true if entities collide, otherwise false
   */
  inline bool checkCollision(const Rectangle a, const Rectangle b) const {
   return CheckCollisionRecs(a, b);
  }
};

}  // cave_mummies::handlers

#endif  // COLLISION_HANDLER_HPP
