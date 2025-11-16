// Copyright 2025 Jason Montenegro-Navarro

#ifndef CAVE_MUMMIES_HANDLERS_COLLISION_HANDLER_HPP
#define CAVE_MUMMIES_HANDLERS_COLLISION_HANDLER_HPP

#include "raylib.h"

#ifdef __linux__
/**
 * @brief Checks collision between rectangles using AABB.
 * @return true if rectangles are collinding, otherwise false.
 * @note This assembly function assumes arguments are always valid.
 */
extern "C" bool checkCollisionRecs(bool* result, float rec1x, float rec1y
  , float rec1width, float rec1height, float rec2x, float rec2y
  , float rec2width, float rec2height);
#endif

namespace cave_mummies::handlers {

/**
 * @brief Handler for collisions between game entities.
 */
class CollisionHandler {
 public:
  /**
   * @brief Checks collision between two entities.
   * @param a First entity.
   * @param b Second entity.
   * @return true if entities collide, otherwise false.
   */
  inline bool checkCollision(const Rectangle& a, const Rectangle& b) const {
    #ifdef __linux__
    bool result{false};
    checkCollisionRecs(&result, a.x, a.y, a.width, a.height, b.x, b.y, b.width
      , b.height);
    return result;
    #else
    return CheckCollisionRecs(a, b);
    #endif
  }
};

}  // cave_mummies::handlers

#endif  // CAVE_MUMMIES_HANDLERS_COLLISION_HANDLER_HPP
