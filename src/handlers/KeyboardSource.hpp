// Copyright 2025 Jason Montenegro-Navarro

#ifndef KEYBOARD_SOURCE_HPP
#define KEYBOARD_SOURCE_HPP

#include "InputSource.hpp"

namespace cave_mummies::handlers {

/**
 * @brief Interface for keyboard input in the game.
 */
class KeyboardSource : public InputSource {
 public:
  /**
   * @brief Checks if a key is currently pressed.
   * @param key Key identifier
   * @return true if pressed, false otherwise
   */
  inline bool isPressed(int key) const override {
    return IsKeyPressed(key);
  }

  /**
   * @brief Checks if a key / button is currently pressed.
   * @param key Key or button identifier
   * @return true if down, false otherwise
   */
  inline bool isKeyDown(int key) const override {
    return IsKeyDown(key);
  }

  /**
   * @brief Checks if a key / button was released.
   * @param key Key or button identifier
   * @return true if released, false otherwise
   */ 
  bool isKeyReleased(int key) const override {
    return IsKeyReleased(key);
  }
};

}  // namespace cave_mummies::handlers

#endif  // KEYBOARD_SOURCE_HPP
