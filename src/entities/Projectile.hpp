// Copyright 2025 Jason Montenegro-Navarro

#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <string>

#include "Entity.hpp"

/**
 * @brief Projectile entity
 */
class Projectile : public Entity {
 protected:
  Vector2 position;  ///< Screen position

 public:
  /**
   * @brief Constructor
   * @param assetPath Asset path for this object texture
   */
  explicit Projectile(const char *const assetPath)
    : Entity(assetPath) { }

  /**
   * @brief Updates this projectile state.
   */
  void update() override;

  /**
   * @brief Sets the projectile position on screen.
   * @param pos New position
   */
  inline void setPosition(Vector2 pos) {
    this->position.x = pos.x;
    this->position.y = pos.y;
  }
};

#endif  // PROJECTILE_HPP
