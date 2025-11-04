// Copyright 2025 Jason Montenegro-Navarro

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>

#include "raylib.h"

// Class forward declaration
namespace cave_mummies::core {
  class Game;
}

namespace cave_mummies::entities {

/**
 * @enum Direction
 * @brief Set of possible entity directions
 */
enum class Direction {
  Up,
  Down,
  Right,
  Left
};

/**
 * @brief Abstract entity interface. Sets entities API.
 */
class Entity {
 protected:
  /// @brief Includes (x, y) coordinates, width and height
  Rectangle bounds{0, 0, 0, 0};
  /// @brief Entity speed
  float currentSpeed{1.0f};
  /// @brief Speed velocity
  float velocity{1.0f};
  /// @brief Base velocity value
  float baseVelocity{1.0f};
  /// @brief Frame counter for displaying sprite more extendedly
  int32_t gameFrameCounter;
  /// @brief Sprite frame
  int32_t currentSpriteFrame{0};
  /// @brief Sprite frame count
  int32_t spriteFrameCount{4};
  /// @brief Game controller
  cave_mummies::core::Game& game;
  /// @brief Default sprite pixel width
  static constexpr float DefaultSpritePixelWidth{32.0};
  /// @brief Sprite direction
  cave_mummies::entities::Direction currentDirection{
    cave_mummies::entities::Direction::Right};

 public:
  /**
   * @brief Constructor
   * @param game Game controller
   */
  explicit Entity(cave_mummies::core::Game& game)
    : game(game) { }

  /**
   * @brief Destructor
   */
  virtual ~Entity() { }

  /**
   * @brief Updates this entity state
   */
  virtual void update() = 0;

  /**
   * @brief Draws texture to screen
   */
  inline virtual void draw() = 0;

  /**
   * @brief Getter of bounds member
   * @return this bounds member
   */
  inline Rectangle getBounds() const {
    return this->bounds;
  }

  /**
   * @brief Setter of bounds member
   * @param b New bounds object
   */
  inline void setBounds(const Rectangle& b) {
    this->bounds = b;
  }

  /**
   * @brief Getter of velocity member
   * @return this velocity object
   */
  inline float getVelocity() const {
    return this->velocity;
  }

  /**
   * @brief Setter of velocity member
   * @param v New velocity value
   */
  inline void setVelocity(float v) {
    this->velocity = v;
  }

  /**
   * @brief Setter of current speed member
   * @param speed New speed value
   */
  inline void setCurrentSpeed(float speed) {
    this->currentSpeed = speed;
  }

  /**
   * @brief Getter of the current sprite direction
   * @return this current direction
   */
  inline Direction getDirection() const {
    return this->currentDirection;
  }

  /**
   * @brief Setter of texture frame count
   * @param count Spritesheet frame count
   */
  inline void setTextureFrameCount(int32_t count) {
    this->spriteFrameCount = count;
  }
};

}  // cave_mummies::entities

#endif  // ENTITY_HPP
