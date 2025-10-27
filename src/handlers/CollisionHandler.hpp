// Copyright 2025 Jason Montenegro-Navarro

#ifndef COLLISION_HANDLER_HPP
#define COLLISION_HANDLER_HPP

#include "raylib.h"

/**
 * @brief Checks collision between two entities
 * @param a First entity
 * @param b Second entity
 * @param result Pointer to store result
 * @note Assembly (NASM) function for Linux-based machines
 */
extern "C" void check_collision_recs(Rectangle* a, Rectangle* b, int* result);

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
    #ifdef __linux__
      int result{0};
      check_collision_recs(&a, &b, &result);
      return result != 0;
    #else
      return CheckCollisionRecs(a, b);
    #endif
  }
};

}  // cave_mummies::handlers

#endif  // COLLISION_HANDLER_HPP
