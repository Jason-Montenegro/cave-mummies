// Copyright 2025 Jason Montenegro-Navarro

#include <string>

#include "JoystickSource.hpp"

namespace cave_mummies::handlers {

JoystickSource::JoystickSource() {
  this->setKeyBindings();
}

void JoystickSource::setKeyBindings() {
  // Set all available key bindings
  this->buttonState[KEY_W] = false;
  this->buttonState[KEY_A] = false;
  this->buttonState[KEY_S] = false;
  this->buttonState[KEY_D] = false;
  this->buttonState[KEY_UP] = false;
  this->buttonState[KEY_DOWN] = false;
  this->buttonState[KEY_LEFT] = false;
  this->buttonState[KEY_RIGHT] = false;
  this->buttonState[KEY_LEFT_SHIFT] = false;
  this->previousButtonState = this->buttonState;
}

bool JoystickSource::isPressed(int key) const {
  // Previous == false && current == true
  auto current{this->buttonState.find(key)};
  auto previous{this->previousButtonState.find(key)};
  return current != this->buttonState.end()
    && previous!= this->previousButtonState.end()
    && current->second && !previous->second;
}

bool JoystickSource::isKeyDown(int key) const {
  // current == true
  auto current{this->buttonState.find(key)};
  return current != this->buttonState.end() && current->second;
}

bool JoystickSource::isKeyReleased(int key) const {
  // Previous == true && current == false
  auto current{this->buttonState.find(key)};
  auto previous{this->previousButtonState.find(key)};
  return current != this->buttonState.end()
    && previous != this->previousButtonState.end()
    && !current->second && previous->second;
}

void JoystickSource::update() {
  this->previousButtonState = this->buttonState;
  // TODO(Jason): add arduino comptability to fetch input from joystick
}

}  // namespace cave_mummies::handlers
