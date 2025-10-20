// Copyright 2025 Jason Montenegro-Navarro

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>

#include "raylib.h"


namespace cave_mummies::core {
class Game;
}

namespace cave_mummies::entities {

/// @brief Direction
/// @brief Set of possible entity directions.
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
  Rectangle bounds;
  /// @brief Image texture
  Texture2D texture;
  /// @brief Speed velocity
  float velocity;
  /// @brief Game controller
  cave_mummies::core::Game& game;
  /// @brief Current entity speed
  float currentSpeed{1.0};
  /// @brief Sprite pixel width
  static constexpr float spritePixelWidth{32.0};
  /// @brief Sprite direction
  cave_mummies::entities::Direction spriteDirection{
    cave_mummies::entities::Direction::Right};

 public:
  /**
   * @brief Constructor
   * @param game Game controller
   * @param assetFilename File name of sprite texture
   */
  explicit Entity(cave_mummies::core::Game& game
    , const char* const assetFilename)
    : bounds{0, 0, 0, 0}, velocity{1.0}, game(game) {
    const char* basePath{GetApplicationDirectory()};
    this->texture = LoadTexture((std::string(basePath)
      + assetFilename).c_str());
  }

  /**
   * @brief Destructor
   */
  virtual ~Entity() {
    UnloadTexture(this->texture);
  }

  /**
   * @brief Updates this entity state.
   */
  virtual void update() = 0;

  /**
   * @brief Draws texture to screen.
   */
  inline virtual void draw() {
    DrawTexture(this->texture, static_cast<int>(this->bounds.x)
      , static_cast<int>(this->bounds.y), RAYWHITE);
  }

  /**
   * @brief Gets the bounds member
   * @return this bounds object
   */
  inline Rectangle getBounds() const {
    return this->bounds;
  }

  /**
   * @brief Sets the bounds member
   * @param b New bounds object
   */
  inline void setBounds(const Rectangle& b) {
    this->bounds = b;
  }

  /**
   * @brief Gets the velocity member
   * @return this velocity object
   */
  inline float getVelocity() const {
    return this->velocity;
  }

  /**
   * @brief Sets the velocity member
   * @param v New velocity value
   */
  inline void setVelocity(float v) {
    this->velocity = v;
  }

  /**
   * @brief Sets the currentSpeed member
   * @param speed New speed value
   */
  inline void setCurrentSpeed(float speed) {
    this->currentSpeed = speed;
  }

  /**
   * @brief Gets the texture member
   * @return this texture object
   */
  inline Texture2D getTexture() const {
    return this->texture;
  }
  
  /**
   * @brief Sets the texture member
   * @param t New texture object
   */
  inline void setTexture(const Texture2D& t) {
    this->texture = t;
  }

  /**
   * @brief Gets the current sprite direction.
   * @return Current direction
   */
  inline Direction getDirection() const {
    return this->spriteDirection;
  }
};

}  // cave_mummies::entities

#endif  // ENTITY_HPP
