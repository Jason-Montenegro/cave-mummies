// Copyright 2025 Jason Montenegro-Navarro

#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include <memory>

#include "InputSource.hpp"
#include "JoystickSource.hpp"
#include "KeyboardSource.hpp"

namespace cave_mummies::handlers {

/**
 * @brief Interface for handling player input via an input source.
 * The class is intended to handle input for keyboard and joystick sources only.
 */
class InputHandler {
 private:
    std::unique_ptr<InputSource> source;  ///< Input source to fetch data from

 public:
  /**
   * @brief Constructor
   * @param source Pointer to an input source (keyboard, joystick, etc.)
   */
  explicit InputHandler(InputSourceType source) {
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
   * @brief Queries whether a specific key / button is pressed once.
   * @param key Key / button identifier
   * @return true if pressed, false otherwise
   */
  inline bool isPressed(int key) const {
    return (source) ? source->isPressed(key) : false;
  }

  /**
   * @brief Queries whether a specific key / button is currently pressed.
   * @param key Key / button identifier
   * @return true if down, false otherwise
   */
  inline bool isKeyDown(int key) const {
    return (source) ? source->isKeyDown(key) : false;
  }

  /**
   * @brief Queries whether a specific key / button was released.
   * @param key Key / button identifier
   * @return true if released, false otherwise
   */
  inline bool isKeyReleased(int key) const {
    return (source) ? source->isKeyReleased(key) : false;
  }
};

}  // namespace cave_mummies::handlers

#endif  // INPUT_HANDLER_HPP
