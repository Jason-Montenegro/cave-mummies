// Copyright 2025 Jason Montenegro-Navarro

#ifndef KEYBOARD_SOURCE_HPP
#define KEYBOARD_SOURCE_HPP

#include "InputSource.hpp"

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
  bool isPressed(int key) const override;
};

#endif  // KEYBOARD_SOURCE_HPP
