// Copyright 2025 Jason Montenegro-Navarro

#ifndef JOYSTICK_SOURCE_HPP
#define JOYSTICK_SOURCE_HPP

#include "InputSource.hpp"

#include <unordered_map>

namespace cave_mummies::handlers {

/**
 * @brief Interface for joystick input in the game.
 */
class JoystickSource : public cave_mummies::handlers::InputSource {
 private:
  /// @brief Key bindings that hold the current state of the keys
  std::unordered_map<int, bool> buttonState; 
  /// @brief Key bindings that hold the previous state of the keys
  std::unordered_map<int, bool> previousButtonState; 

 public:
  /**
   * @brief Constructor that sets the key bindings and opens arudino serial port
   */
  JoystickSource();

  /**
   * @brief Checks if a key is currently pressed.
   * @param key Key identifier
   * @return true if pressed, false otherwise
   */
  bool isPressed(int key) const override;

  /**
   * @brief Checks if a key / button is currently pressed.
   * @param key Key or button identifier
   * @return true if down, false otherwise
   */
  bool isKeyDown(int key) const override;

  /**
   * @brief Checks if a key / button was released.
   * @param key Key or button identifier
   * @return true if released, false otherwise
   */ 
  bool isKeyReleased(int key) const override;

  /**
   * @brief Updates button states from the input status of the connected
   * Arduino device
   */
  void update() override;

 private:
  /**
   * @brief Setter for key bindings
   */
  void setKeyBindings();
};

}  // namespace cave_mummies::handlers

#endif  // JOYSTICK_SOURCE_HPP
