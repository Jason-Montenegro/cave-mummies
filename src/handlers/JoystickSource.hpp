// Copyright 2025 Jason Montenegro-Navarro

#ifndef JOYSTICK_SOURCE_HPP
#define JOYSTICK_SOURCE_HPP

#include "InputSource.hpp"

namespace cave_mummies::handlers {

/**
 * @brief Interface for joystick input in the game.
 */
class JoystickSource : public cave_mummies::handlers::InputSource {
 public:
  /**
   * @brief Checks if a key is currently pressed.
   * @param key Key identifier
   * @return true if pressed, false otherwise
   */
  bool isPressed(int key) const override;
};

}  // namespace cave_mummies::handlers

#endif  // JOYSTICK_SOURCE_HPP
