// Copyright 2025 Jason Montenegro-Navarro

#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "Entity.hpp"

namespace cave_mummies::entities {

/**
 * @brief Projectile structure for player to shoot.
 */
struct Projectile {
 public:
  Vector2 position;
  Vector2 velocity;
  float radius;
  Color color;

  /**
   * @brief Constructor
   * @param pos Start position
   * @param vel Projectile velocity
   * @param r Projectile radius
   * @param c Projectile color
   */
   Projectile(Vector2 pos
      , Vector2 vel
      , float r
      , Color c)
      : position(pos)
      , velocity(vel)
      , radius(r)
      , color(c){ }

  /**
   * @brief Updates this projectile coordinates.
   */
  inline void update() {
    position.x += velocity.x;
    position.y += velocity.y;
  }

  /**
   * @brief Draws projectile on the screen.
   */
  inline void draw() const {
    DrawCircleV(position, radius, color);
  }

  /**
   * @brief Getter for projectile coordinates and size.
   * @return Projectile bounds
   */
  Rectangle getBounds() const {
    return {position.x - radius, position.y - radius, radius * 2, radius * 2};
  }
};

}  // namespace cave_mummies::entities

#endif  // PROJECTILE_HPP
