// Copyright 2025 Jason Montenegro-Navarro

#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include <memory>

#include "InputSource.hpp"
#include "JoystickSource.hpp"
#include "KeyboardSource.hpp"

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
  explicit InputHandler(InputSourceType source = InputSourceType::Keyboard) {
    switch (source) {
    case InputSourceType::Joystick:
      this->source = std::make_unique<JoystickSource>();
      break;
    case InputSourceType::Keyboard:
    [[fallthrough]];
    default:
      this->source = std::make_unique<KeyboardSource>();
      break;
    }
  }

  /**
   * @brief Destructor
   */
  ~InputHandler() = default;

  /**
   * @brief Updates the status of the key bindings of the input source
   */
  inline void update() {
    this->source->update();
  }

  /**
   * @brief Queries whether a specific key / button is pressed once
   * @param key Key / button identifier
   * @return true if pressed, otherwise false
   * @note Should be used when input source does not provide an interface
   * for a specific key that is mapped on the keyboard
   */
  inline bool keyboardIsPressed(int key) const {
    return isPressed(key);
  }

  /**
   * @brief Queries whether a specific key / button is pressed once
   * @param key Key / button identifier
   * @return true if pressed, otherwise false
   */
  inline bool isPressed(int key) const {
    return this->source->isPressed(key);
  }

  /**
   * @brief Queries whether a specific key / button is currently being held down
   * @param key Key / button identifier
   * @return true if down, otherwise false
   */
  inline bool isKeyDown(int key) const {
    return this->source->isKeyDown(key);
  }

  /**
   * @brief Queries whether a specific key / button was released
   * @param key Key / button identifier
   * @return true if released, otherwise false
   */
  inline bool isKeyReleased(int key) const {
    return this->source->isKeyReleased(key);
  }

  /**
   * @brief Queries whether the left mouse button was pressed once
   * @return true if pressed, otherwise false
   * @note Special method for computer mouse
   */
  inline bool isMouseLeftPressed() const {
    return isPressed(MOUSE_LEFT_BUTTON);
  }

  /**
   * @brief Queries whether the right mouse button was pressed once
   * @return true if pressed, otherwise false
   * @note Special method for computer mouse
   */
  inline bool isMouseRightPressed() const {
    return isPressed(MOUSE_RIGHT_BUTTON);
  }

  /**
   * @brief Queries whether the left mouse button is currently being held down
   * @return true if down, otherwise false
   * @note Special method for computer mouse
   */
  inline bool isMouseLeftDown() const {
    return isKeyDown(MOUSE_LEFT_BUTTON);
  }

  /**
   * @brief Queries whether the right mouse button is currently being held down
   * @return true if down, otherwise false
   * @note Special method for computer mouse
   */
  inline bool isMouseRightDown() const {
    return isKeyDown(MOUSE_RIGHT_BUTTON);
  }

  /**
   * @brief Queries whether the left mouse button was released
   * @return true if released, otherwise false
   * @note Special method for computer mouse
   */
  inline bool isMouseLeftReleased() const {
    return isKeyReleased(MOUSE_LEFT_BUTTON);
  }

  /**
   * @brief Queries whether the right mouse button was released
   * @return true if released, otherwise false
   * @note Special method for computer mouse
   */
  inline bool isMouseRightReleased() const {
    return isKeyReleased(MOUSE_RIGHT_BUTTON);
  }

  /**
   * @brief Queries the movement of the mouse wheel
   * @return Scroll movement (positive number indicates UP,
   * negative number indicates DOWN, zero indicates no movement)
   * @note Special method for computer mouse
   */
  inline int getCurrentMouseWheelMove() const {
    return GetMouseWheelMove();
  }

  /**
   * @brief Getter of the current mouse position
   * @return Vector2 containing x and y coordinates
   * @note Special method for computer mouse
   */
  inline Vector2 getCurrentMousePosition() const {
    return GetMousePosition();
  }

  /**
   * @brief Getter of the x coordinate of the mouse
   * @return X position of mouse
   * @note Special method for computer mouse
   */
  inline int getMouseX() const {
    return GetMousePosition().x;
  }

  /**
   * @brief Getter of the y coordinate of the mouse
   * @return Y position of mouse
   * @note Special method for computer mouse
   */
  inline int getMouseY() const {
    return GetMousePosition().y;
  }
};

}  // namespace cave_mummies::handlers

#endif  // INPUT_HANDLER_HPP
