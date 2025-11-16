// Copyright 2025 Jason Montenegro-Navarro

#ifndef CAVE_MUMMIES_HANDLERS_INPUT_HANDLER_HPP
#define CAVE_MUMMIES_HANDLERS_INPUT_HANDLER_HPP

#include <termios.h>
#include <memory>
#include <unordered_map>
#include "raylib.h"

namespace cave_mummies::handlers {

/**
 * @brief Handler for player input via input sources (mouse, keyboard,
 * arduino joystick).
 */
class InputHandler {
 private:
 // Arduino portability implementation is only for Linux-based systems
 #ifdef __linux__
  /// @brief Arduino file descriptor for joystick connection.
  int arduinoFileDescriptor{-1};
  /// @brief Original termios configuration for arduino connection.
  termios oldConfiguration{};
  /// @brief Modifiable termios configuration for arduino connection.
  termios newConfiguration{};
  /// @brief Key bindings that hold the current state of the keys for joystick.
  std::unordered_map<int, bool> buttonState{}; 
  /// @brief Key bindings that hold the previous state of the keys for joystick.
  std::unordered_map<int, bool> previousButtonState{};
  #endif

 public:
  /**
   * @brief Construct a new Input Handler object.
   */
  explicit InputHandler();

  /**
   * @brief Destructor
   */
  ~InputHandler();

  /**
   * @brief Updates the status of the key bindings of the input source
   */
  void update();

  /**
   * @brief Queries whether a specific key/button is pressed once
   * @param key Key/button identifier.
   * @return true if pressed, otherwise false.
   */
  bool isPressed(int key) const;

  /**
   * @brief Queries whether a specific key/button is currently being held down.
   * @param key Key/button identifier.
   * @return true if down, otherwise false.
   */
  bool isKeyDown(int key) const;

  /**
   * @brief Queries whether a specific key/button was released.
   * @param key Key/button identifier.
   * @return true if released, otherwise false.
   */
  bool isKeyReleased(int key) const;

  /**
   * @brief Queries whether the left mouse button was pressed once.
   * @return true if pressed, otherwise false.
   * @note Special method for computer mouse.
   */
  bool isMouseLeftPressed() const;

  /**
   * @brief Queries whether the right mouse button was pressed once.
   * @return true if pressed, otherwise false.
   * @note Special method for computer mouse.
   */
  bool isMouseRightPressed() const;

  /**
   * @brief Queries whether the left mouse button is currently being held down.
   * @return true if down, otherwise false.
   * @note Special method for computer mouse.
   */
  bool isMouseLeftDown() const;

  /**
   * @brief Queries whether the right mouse button is currently being held down.
   * @return true if down, otherwise false.
   * @note Special method for computer mouse.
   */
  bool isMouseRightDown() const;

  /**
   * @brief Queries whether the left mouse button was released.
   * @return true if released, otherwise false.
   * @note Special method for computer mouse.
   */
  bool isMouseLeftReleased() const;

  /**
   * @brief Queries whether the right mouse button was released.
   * @return true if released, otherwise false.
   * @note Special method for computer mouse.
   */
  bool isMouseRightReleased() const;

  /**
   * @brief Get the current mouse wheel movement.
   * @return Scroll movement (positive number indicates UP,
   * negative number indicates DOWN, zero indicates no movement).
   * @note Special method for computer mouse.
   */
  int getCurrentMouseWheelMove() const;

  /**
   * @brief Get the current mouse screen positition.
   * @return Vector2 containing x and y coordinates.
   * @note Special method for computer mouse.
   */
  Vector2 getCurrentMousePosition() const;

  /**
   * @brief Get the mouse X coordinate.
   * @return X coordinate position of mouse.
   * @note Special method for computer mouse.
   */
  int getMouseX() const;

  /**
   * @brief Get the mouse Y coordinate.
   * @return X coordinate position of mouse.
   * @note Special method for computer mouse.
   */
  int getMouseY() const;

 private:
  /**
   * @brief Set the arduino key bindings.
   */
  void setKeyBindings();

  #ifdef __linux__
  /**
   * @brief Checks if the passed argument is an arduino key query.
   * @return true if it is, otherwise false.
   */
  bool checkArduinoQuery(int key) const;
  #endif
};

}  // namespace cave_mummies::handlers

#endif  // CAVE_MUMMIES_HANDLERS_INPUT_HANDLER_HPP
