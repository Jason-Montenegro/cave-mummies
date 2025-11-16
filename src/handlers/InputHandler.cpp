// Copyright 2025 Jason Montenegro-Navarro

#include <fcntl.h>
#include <unistd.h>
#include <memory>
#include "InputHandler.hpp"
#include "Log.hpp"

namespace cave_mummies::handlers {

InputHandler::InputHandler() {
  #ifdef __linux__
  this->setKeyBindings();
  // Adapted from ChatGPT. Date: Saturday 15 November 2025
  // Prompt:how to connect arduino in unix systems for receiving joystick signal
  this->arduinoFileDescriptor = open("/dev/ttyACM0", O_RDONLY | O_NOCTTY
    | O_NONBLOCK);
  if (this->arduinoFileDescriptor < 0) {
    cave_mummies::utils::Log::append(
      cave_mummies::utils::Log::MessageType::ERROR, "Arduino Joystick"
      , "could not open arduino port.");
  } else {
    // Save current configuration
    tcgetattr(this->arduinoFileDescriptor, &this->oldConfiguration);
    // Copy base configuration
    tcgetattr(this->arduinoFileDescriptor, &this->newConfiguration);
    // Set velocity
    cfsetispeed(&this->newConfiguration, B9600);
    cfsetospeed(&this->newConfiguration, B9600);
    // Activates raw mode
    cfmakeraw(&this->newConfiguration);
    // Enables reading
    this->newConfiguration.c_cflag |= (CLOCAL | CREAD);
    // Applies new configuration
    tcsetattr(this->arduinoFileDescriptor, TCSANOW, &this->newConfiguration);
  }
  #endif
}

InputHandler::~InputHandler() {
  #ifdef __linux__
  // Adapted from ChatGPT. Date: Saturday 15 November 2025
  // Prompt:how to connect arduino in unix systems for receiving joystick signal
  if (this->arduinoFileDescriptor >= 0) {
    tcsetattr(this->arduinoFileDescriptor, TCSANOW, &this->oldConfiguration);
    close(this->arduinoFileDescriptor);
  }
  #endif
}

void InputHandler::setKeyBindings() {
  // Set all available key bindings for arduino joystick
  #ifdef __linux__
  this->buttonState[KEY_W] = false;
  this->buttonState[KEY_UP] = false;
  this->buttonState[KEY_SPACE] = false;
  this->buttonState[KEY_A] = false;
  this->buttonState[KEY_LEFT] = false;
  this->buttonState[KEY_D] = false;
  this->buttonState[KEY_RIGHT] = false;
  this->buttonState[KEY_LEFT_SHIFT] = false;
  this->previousButtonState = this->buttonState;
  #endif
}

void InputHandler::update() {
  #ifdef __linux__
  if (this->arduinoFileDescriptor >= 0) {
    this->previousButtonState = this->buttonState;
    for (auto &keyBinding : this->buttonState) {
      keyBinding.second = false;
    }
    char movement{'\0'};
    const ssize_t n{read(arduinoFileDescriptor, &movement, 1)};
    if (n == 1) {
      switch (movement) {
      case 'w':  // Jump player movement
        this->buttonState[KEY_W] = true;
        this->buttonState[KEY_UP] = true;
        this->buttonState[KEY_SPACE] = true;
        break;
      case 'a':  // Left player movement
        this->buttonState[KEY_A] = true;
        this->buttonState[KEY_LEFT] = true;
        break;
      case 'd':  // Right player movement
        this->buttonState[KEY_D] = true;
        this->buttonState[KEY_RIGHT] = true;
        break;
      case 'z':  // Shift movement
        this->buttonState[KEY_LEFT_SHIFT] = true;
        break;
      default:
        break;
      }
    }
  }
  #endif
  // Keyboard input does not need any updating
}

#ifdef __linux__
bool InputHandler::checkArduinoQuery(int key) const {
  return key == KEY_W || key == KEY_UP || key == KEY_SPACE || key == KEY_A
    || key == KEY_LEFT || key == KEY_D || key == KEY_RIGHT
    || key == KEY_LEFT_SHIFT;
}
#endif

bool InputHandler::isPressed(int key) const {
  #ifdef __linux__
  if (this->arduinoFileDescriptor >= 0 && this->checkArduinoQuery(key)) {
    // Check for joystick input
    // Previous == false && current == true
    auto current{this->buttonState.find(key)};
    auto previous{this->previousButtonState.find(key)};
    return current != this->buttonState.end()
      && previous!= this->previousButtonState.end()
      && current->second && !previous->second;
  } else {
    return IsKeyPressed(key);
  }
  #else
  return IsKeyPressed(key);
  #endif
}

bool InputHandler::isKeyDown(int key) const {
  #ifdef __linux__
  if (this->arduinoFileDescriptor >= 0 && this->checkArduinoQuery(key)) {
    // Check for joystick input
    // current == true
    auto current{this->buttonState.find(key)};
    return current != this->buttonState.end() && current->second;
  } else {
    return IsKeyDown(key);
  }
  #else
  return IsKeyDown(key);
  #endif
}

bool InputHandler::isKeyReleased(int key) const {
  #ifdef __linux__
  if (this->arduinoFileDescriptor >= 0 && this->checkArduinoQuery(key)) {
    // Check for joystick input
    // Previous == true && current == false
    auto current{this->buttonState.find(key)};
    auto previous{this->previousButtonState.find(key)};
    return current != this->buttonState.end()
      && previous != this->previousButtonState.end()
      && !current->second && previous->second;
  } else {
    return IsKeyReleased(key);
  }
  #else
  return IsKeyReleased(key);
  #endif
}

bool InputHandler::isMouseLeftPressed() const {
  return IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

bool InputHandler::isMouseRightPressed() const {
  return IsMouseButtonPressed(MOUSE_RIGHT_BUTTON);
}

bool InputHandler::isMouseLeftDown() const {
  return IsMouseButtonDown(MOUSE_LEFT_BUTTON);
}

bool InputHandler::isMouseRightDown() const {
  return IsMouseButtonDown(MOUSE_RIGHT_BUTTON);
}

bool InputHandler::isMouseLeftReleased() const {
  return IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
}

bool InputHandler::isMouseRightReleased() const {
  return IsMouseButtonReleased(MOUSE_RIGHT_BUTTON);
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
