// Copyright 2025 Jason Montenegro-Navarro

#ifndef KEYBOARD_SOURCE_HPP
#define KEYBOARD_SOURCE_HPP

#include "InputSource.hpp"

namespace cave_mummies::handlers {

/**
 * @brief Interface for keyboard input source
 */
class KeyboardSource : public InputSource {
 public:
  /**
   * @brief Checks if a key / button is pressed once
   * @param key Key or button identifier
   * @return true if pressed, otherwise false
   */
  inline bool isPressed(int key) const override {
    return IsKeyPressed(key);
  }

  /**
   * @brief Checks if a key / button is currently being held down
   * @param key Key or button identifier
   * @return true if down, otherwise false
   */
  inline bool isKeyDown(int key) const override {
    return IsKeyDown(key);
  }

  /**
   * @brief Checks if a key / button was released
   * @param key Key or button identifier
   * @return true if released, otherwise false
   */ 
  bool isKeyReleased(int key) const override {
    return IsKeyReleased(key);
  }

  /**
   * @brief Updates the status of the key bindings of the input source
   */
  void update() override {
    // Does nothing because the keyboard updates by itself
  }
};

}  // namespace cave_mummies::handlers

#endif  // KEYBOARD_SOURCE_HPP
