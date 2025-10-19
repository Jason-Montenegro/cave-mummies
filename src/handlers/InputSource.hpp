// Copyright 2025 Jason Montenegro-Navarro

#ifndef INPUT_SOURCE_HPP
#define INPUT_SOURCE_HPP

#include "raylib.h"

namespace cave_mummies::handlers {

/// @enum InputSourceType
/// @brief Input source type for playing the game (Keyboard or Joystick)
enum class InputSourceType {
  Keyboard,
  Joystick
};

/**
 * @brief Interface for any source of input in the game. Such as keyboard or
 * joystick.
 */
class InputSource {
 public:
  /**
   * @brief Destructor
   */
  virtual ~InputSource() = default;

  /**
   * @brief Checks if a key/button is currently pressed.
   * @param key Key or button identifier
   * @return true if pressed, false otherwise
   */
  virtual bool isPressed(int key) const = 0;
};

}  // namespace cave_mummies::handlers

#endif  // INPUT_SOURCE_HPP
