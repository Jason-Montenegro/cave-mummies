// Copyright 2025 Jason Montenegro-Navarro

#ifndef CAVE_MUMMIES_ENTITIES_ENTITY_HPP
#define CAVE_MUMMIES_ENTITIES_ENTITY_HPP

#include <string>
#include "raylib.h"

namespace cave_mummies::core {
  class Game;
}

namespace cave_mummies::entities {

/**
 * @brief Set of possible entity directions.
 */
enum class Direction {
  Up,
  Down,
  Right,
  Left
};

/**
 * @brief Abstract entity interface.
 */
class Entity {
 protected:
  /// @brief Entity bounds (x, y, width, height).
  Rectangle bounds{};
  /// @brief Current entity speed.
  float currentSpeed{1.0f};
  /// @brief Current velocity value.
  float velocity{1.0f};
  /// @brief Base velocity reference value.
  float baseVelocity{1.0f};
  /// @brief Frame counter used for sprite display.
  int32_t gameFrameCounter{0};
  /// @brief Current sprite frame.
  int32_t currentSpriteFrame{0};
  /// @brief Total sprite frames.
  const int32_t totalSpriteFrameCount{4};
  /// @brief Game controller.
  cave_mummies::core::Game& game;
  /// @brief Default sprite width in pixels.
  static constexpr float defaultSpritePixelWidth{32.0};
  /// @brief Current sprite direction.
  Direction currentDirection{Direction::Right};

 public:
  /**
   * @brief Construct a new Entity object.
   * @param game Game controller.
   */
  explicit Entity(cave_mummies::core::Game& game)
    : game(game) { }

  /**
   * @brief Destroy the Entity object.
   */
  virtual ~Entity() { }

  /**
   * @brief Updates this entity state.
   */
  virtual void update() = 0;

  /**
   * @brief Draws this entity to screen.
   */
  virtual void draw() = 0;

  /**
   * @brief Gets the entity bounds.
   * @return Rectangle representing the entity bounds.
   */
  inline Rectangle getBounds() const {
    return this->bounds;
  }

  /**
   * @brief Sets the entity bounds.
   * @param b New bounds rectangle.
   */
  inline void setBounds(const Rectangle& b) {
    this->bounds = b;
  }

  /**
   * @brief Gets the entity velocity.
   * @return Current velocity value.
   */
  inline float getVelocity() const {
    return this->velocity;
  }

  /**
   * @brief Sets the entity velocity.
   * @param v New velocity value.
   */
  inline void setVelocity(float v) {
    this->velocity = v;
  }

  /**
   * @brief Sets the current speed value.
   * @param speed New speed value.
   */
  inline void setCurrentSpeed(float speed) {
    this->currentSpeed = speed;
  }

  /**
   * @brief Gets the current movement direction.
   * @return Current direction.
   */
  inline Direction getDirection() const {
    return this->currentDirection;
  }
};

}  // namespace cave_mummies::entities

#endif  // CAVE_MUMMIES_ENTITIES_ENTITY_HPP
