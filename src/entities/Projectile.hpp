// Copyright 2025 Jason Montenegro-Navarro

#ifndef CAVE_MUMMIES_ENTITIES_PROJECTILE_HPP
#define CAVE_MUMMIES_ENTITIES_PROJECTILE_HPP

#include "Entity.hpp"

namespace cave_mummies::entities {

/**
 * @brief Player projectile.
 */
struct Projectile {
 public:
  /// @brief Projectile position on the screen.
  Vector2 position;
  /// @brief Projectile velocity vector.
  Vector2 velocity;
  /// @brief Projectile radius in pixels.
  float radius{1.0f};
  /// @brief Projectile display color.
  Color color;

  /**
   * @brief Construct a new Projectile object.
   * @param pos Initial position.
   * @param vel Movement velocity.
   * @param r Projectile radius (negative values turn to 1.0f)
   * @param c Projectile color.
   */
  explicit Projectile(Vector2 pos, Vector2 vel, float r, Color c)
    : position(pos)
    , velocity(vel)
    , radius((r < 0) ? 1.0f : r)
    , color(c) { }

  /**
   * @brief Updates this projectile’s position according to its velocity.
   */
  inline void update() {
    this->position.x += this->velocity.x;
    this->position.y += this->velocity.y;
  }

  /**
   * @brief Draws this projectile on the screen.
   */
  inline void draw() const {
    DrawCircleV(this->position, this->radius, this->color);
  }

  /**
   * @brief Gets the bounding rectangle of this projectile.
   * @return Rectangle representing this projectile bounds.
   */
  inline Rectangle getBounds() const {
    return {position.x - radius, position.y - radius, radius * 1.0f
      , radius * 1.0f};
  }

  /**
   * @brief Equality operator.
   * @param other Projectile to compare with.
   * @return true if both refer to the same object, otherwise false.
   */
  inline bool operator==(const Projectile& other) const {
    return this == &other;
  }
};

}  // namespace cave_mummies::entities

#endif  // CAVE_MUMMIES_ENTITIES_PROJECTILE_HPP
