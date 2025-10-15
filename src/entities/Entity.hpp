// Copyright 2025 Jason Montenegro-Navarro

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "raylib.h"

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
 * @brief Abstract entity interface. Sets entities API.
 */
class Entity {
 protected:
  Rectangle bounds;  ///< Includes (x, y) coordinates, width and height
  Texture2D texture;  ///< Image texture
  Vector2 velocity;

 public:
  /**
   * @brief Constructor
   * @param assetFilename File name of sprite texture
   */
  explicit Entity(const char *const assetFilename)
    : bounds{0, 0, 0, 0}, velocity{0,0} {
    this->texture = LoadTexture(assetFilename);
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
    DrawTexture(texture, static_cast<int>(this->bounds.x)
      , static_cast<int>(this->bounds.y), RAYWHITE);
  }

  /**
   * @brief Gets the bounds member
   * @return this bounds object
   */
  inline Rectangle getBounds() const { return this->bounds; }

  /**
   * @brief Sets the bounds member
   * @param b New bounds object
   */
  inline void setBounds(const Rectangle &b) { this->bounds = b; }

  /**
   * @brief Gets the velocity member
   * @return this velocity object
   */
  inline Vector2 getVelocity() const { return this->velocity; }

  /**
   * @brief Sets the velocity member
   * @param b New velocity object
   */
  inline void setVelocity(const Vector2 &v) { this->velocity = v; }

  /**
   * @brief Gets the texture member
   * @return this texture object
   */
  inline Texture2D getTexture() const { return this->texture; }
  
  /**
   * @brief Sets the texture member
   * @param b New texture object
   */
  inline void setTexture(const Texture2D &t) { this->texture = t; }
};

#endif  // ENTITY_HPP
