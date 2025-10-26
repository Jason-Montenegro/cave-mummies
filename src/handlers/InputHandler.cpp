// Copyright 2025 Jason Montenegro-Navarro

#include <memory>
#include <utility>

#include "InputHandler.hpp"
#include "InputSource.hpp"
#include "JoystickSource.hpp"
#include "KeyboardSource.hpp"

namespace cave_mummies::handlers {

InputHandler::InputHandler(InputSourceType source) {
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

void InputHandler::update() {
  this->source->update();
}

bool InputHandler::keyboardIsPressed(int key) const {
  return isPressed(key);
}

bool InputHandler::isPressed(int key) const {
  return this->source->isPressed(key);
}

bool InputHandler::isKeyDown(int key) const {
  return this->source->isKeyDown(key);
}

bool InputHandler::isKeyReleased(int key) const {
  return this->source->isKeyReleased(key);
}

bool InputHandler::isMouseLeftPressed() const {
  return isPressed(MOUSE_LEFT_BUTTON);
}

bool InputHandler::isMouseRightPressed() const {
  return isPressed(MOUSE_RIGHT_BUTTON);
}

bool InputHandler::isMouseLeftDown() const {
  return isKeyDown(MOUSE_LEFT_BUTTON);
}

bool InputHandler::isMouseRightDown() const {
  return isKeyDown(MOUSE_RIGHT_BUTTON);
}

bool InputHandler::isMouseLeftReleased() const {
  return isKeyReleased(MOUSE_LEFT_BUTTON);
}

bool InputHandler::isMouseRightReleased() const {
  return isKeyReleased(MOUSE_RIGHT_BUTTON);
}

int InputHandler::getCurrentMouseWheelMove() const {
  return GetMouseWheelMove();
}

Vector2 InputHandler::getCurrentMousePosition() const {
  return GetMousePosition();
}

int InputHandler::getMouseX() const {
  return GetMousePosition().x;
}

int InputHandler::getMouseY() const {
  return GetMousePosition().y;
}

}  // namespace cave_mummies::handlers
