// Copyright 2025 Jason Montenegro-Navarro

#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <string>

#include "Entity.hpp"

/**
 * @brief Projectile entity
 */
class Projectile : public Entity {
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
};

#endif  // PROJECTILE_HPP
