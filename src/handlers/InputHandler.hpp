// Copyright 2025 Jason Montenegro-Navarro

#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include <memory>

#include "raylib.h"

namespace cave_mummies::handlers {
  class InputSource;
  enum class InputSourceType;
}

namespace cave_mummies::handlers {

/**
 * @brief Interface for handling player input via input sources
 * 
 * It currently supports input from keyboard and joystick
 * 
 * Mouse input is independent from keyboard or joystick input
 */
class InputHandler {
 private:
  /// @brief Source to fetch input from
  std::unique_ptr<InputSource> source;

 public:
  /**
   * @brief Constructor
   * @param source Input source pointer
   */
  explicit InputHandler(InputSourceType source);

  /**
   * @brief Destructor
   */
  ~InputHandler() = default;

  /**
   * @brief Updates the status of the key bindings of the input source
   */
  void update();

  /**
   * @brief Queries whether a specific key / button is pressed once
   * @param key Key / button identifier
   * @return true if pressed, otherwise false
   * @note Should be used when input source does not provide an interface
   * for a specific key that is mapped on the keyboard
   */
  bool keyboardIsPressed(int key) const;

  /**
   * @brief Queries whether a specific key / button is pressed once
   * @param key Key / button identifier
   * @return true if pressed, otherwise false
   */
  bool isPressed(int key) const;

  /**
   * @brief Queries whether a specific key / button is currently being held down
   * @param key Key / button identifier
   * @return true if down, otherwise false
   */
  bool isKeyDown(int key) const;

  /**
   * @brief Queries whether a specific key / button was released
   * @param key Key / button identifier
   * @return true if released, otherwise false
   */
  bool isKeyReleased(int key) const;

  /**
   * @brief Queries whether the left mouse button was pressed once
   * @return true if pressed, otherwise false
   * @note Special method for computer mouse
   */
  bool isMouseLeftPressed() const;

  /**
   * @brief Queries whether the right mouse button was pressed once
   * @return true if pressed, otherwise false
   * @note Special method for computer mouse
   */
  bool isMouseRightPressed() const;

  /**
   * @brief Queries whether the left mouse button is currently being held down
   * @return true if down, otherwise false
   * @note Special method for computer mouse
   */
  bool isMouseLeftDown() const;

  /**
   * @brief Queries whether the right mouse button is currently being held down
   * @return true if down, otherwise false
   * @note Special method for computer mouse
   */
  bool isMouseRightDown() const;

  /**
   * @brief Queries whether the left mouse button was released
   * @return true if released, otherwise false
   * @note Special method for computer mouse
   */
  bool isMouseLeftReleased() const;

  /**
   * @brief Queries whether the right mouse button was released
   * @return true if released, otherwise false
   * @note Special method for computer mouse
   */
  bool isMouseRightReleased() const;

  /**
   * @brief Queries the movement of the mouse wheel
   * @return Scroll movement (positive number indicates UP,
   * negative number indicates DOWN, zero indicates no movement)
   * @note Special method for computer mouse
   */
  int getCurrentMouseWheelMove() const;

  /**
   * @brief Getter of the current mouse position
   * @return Vector2 containing x and y coordinates
   * @note Special method for computer mouse
   */
  Vector2 getCurrentMousePosition() const;

  /**
   * @brief Getter of the x coordinate of the mouse
   * @return X position of mouse
   * @note Special method for computer mouse
   */
  int getMouseX() const;

  /**
   * @brief Getter of the y coordinate of the mouse
   * @return Y position of mouse
   * @note Special method for computer mouse
   */
  int getMouseY() const;
};

}  // namespace cave_mummies::handlers

#endif  // INPUT_HANDLER_HPP
