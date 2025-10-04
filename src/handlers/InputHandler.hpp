// Copyright 2025 Jason Montenegro-Navarro

#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include <memory>

#include "InputSource.hpp"

/**
 * @brief Interface for handling player input via an input source.
 * The class is intended to handle input for keyboard and joystick sources only.
 */
class InputHandler {
 private:
    std::shared_ptr<InputSource> source;  ///< Input source to fetch data from

 public:
  /**
   * @brief Constructor
   * @param source Pointer to an input source (keyboard, joystick, etc.)
   */
  explicit InputHandler(std::shared_ptr<InputSource> source)
    : source(std::move(source)) { }

  /**
   * @brief Destructor
   */
  ~InputHandler() = default;

  /**
   * @brief Sets a new input source.
   * @param newSource Shared pointer to the new input source
   */
  inline void setInputSource(std::shared_ptr<InputSource> newSource) {
      source = std::move(newSource);
  }

  /**
   * @brief Queries whether a specific key/button is pressed.
   * @param key Key/button identifier
   * @return true if pressed, false otherwise
   */
  inline bool isPressed(int key) const {
    return (source) ? source->isPressed(key) : false;
  }
};

#endif  // INPUT_HANDLER_HPP
