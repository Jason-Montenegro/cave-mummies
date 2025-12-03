// Copyright 2025 Jason Montenegro-Navarro

#include <fcntl.h>
#include <unistd.h>
#include <memory>
#include "InputHandler.hpp"

#ifdef DEBUG
#include "Log.hpp"
#endif

namespace cave_mummies::handlers {

InputHandler::InputHandler() {
  this->setKeyBindings();
  this->openArduinoFile();
}

void InputHandler::setKeyBindings() {
  // Set all available key bindings for arduino joystick
  this->buttonState[KEY_W] = false;
  this->buttonState[KEY_UP] = false;
  this->buttonState[KEY_S] = false;
  this->buttonState[KEY_DOWN] = false;
  this->buttonState[KEY_SPACE] = false;
  this->buttonState[KEY_A] = false;
  this->buttonState[KEY_LEFT] = false;
  this->buttonState[KEY_D] = false;
  this->buttonState[KEY_RIGHT] = false;
  this->buttonState[KEY_LEFT_SHIFT] = false;
  this->previousButtonState = this->buttonState;
}

void InputHandler::openArduinoFile() {
  // Adapted from ChatGPT. Date: Saturday 15 November 2025
  // Prompt:how to connect arduino in unix systems for receiving joystick signal
  #ifdef __linux__
  this->arduinoFileDescriptor = open("/dev/ttyACM0", O_RDONLY
    | O_NOCTTY | O_NONBLOCK);
  #elif __APPLE__
  this->arduinoFileDescriptor = open("/dev/cu.usbmodem1401", O_RDONLY
    | O_NOCTTY | O_NONBLOCK);
  #endif
  if (this->arduinoFileDescriptor < 0) {
    #ifdef DEBUG
    cave_mummies::utils::Log::append(
      cave_mummies::utils::Log::MessageType::ERROR, "Arduino Joystick"
      , "could not open arduino port.");
    #endif
    this->arduinoInputAvailable = false;
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
    this->arduinoInputAvailable = true;
  }
}

InputHandler::~InputHandler() {
  // Adapted from ChatGPT. Date: Saturday 15 November 2025
  // Prompt:how to connect arduino in unix systems for receiving joystick signal
  if (this->arduinoInputAvailable) {
    tcsetattr(this->arduinoFileDescriptor, TCSANOW, &this->oldConfiguration);
    close(this->arduinoFileDescriptor);
  }
}

bool InputHandler::isArduinoConnected() {
  return this->arduinoInputAvailable;
}

void InputHandler::update() {
  this->buttonState[KEY_S] = false;
  this->buttonState[KEY_DOWN] = false;
  if (!this->arduinoInputAvailable) {
    this->openArduinoFile();
  }
  if (this->arduinoInputAvailable) {
    char movement{'\0'};
    const ssize_t n{read(this->arduinoFileDescriptor, &movement, 1)};
    if (n > 0) {
      if (movement == 'd') {
        this->buttonState[KEY_D] = true;
        this->buttonState[KEY_RIGHT] = true;
        this->buttonState[KEY_A] = false;
        this->buttonState[KEY_LEFT] = false;
      } else if (movement == 'a') {
        this->buttonState[KEY_A] = true;
        this->buttonState[KEY_LEFT] = true;
        this->buttonState[KEY_D] = false;
        this->buttonState[KEY_RIGHT] = false;
      } else if (movement == 'c') {
        this->buttonState[KEY_A] = false;
        this->buttonState[KEY_LEFT] = false;
        this->buttonState[KEY_D] = false;
        this->buttonState[KEY_RIGHT] = false;
      }
      if (movement == 'w') {
        this->buttonState[KEY_W] = true;
        this->buttonState[KEY_UP] = true;
        this->buttonState[KEY_SPACE] = true;
      } else if (movement == 'e') {
        this->buttonState[KEY_W] = false;
        this->buttonState[KEY_UP] = false;
        this->buttonState[KEY_SPACE] = false;
        this->buttonState[KEY_A] = false;
        this->buttonState[KEY_LEFT] = false;
        this->buttonState[KEY_D] = false;
        this->buttonState[KEY_RIGHT] = false;
      }
      if (movement == 's') {
        this->buttonState[KEY_S] = true;
        this->buttonState[KEY_DOWN] = true;
      }
      if (movement == 'z') {
        this->buttonState[KEY_LEFT_SHIFT] = true;
      } else if (movement == 'x') {
        this->buttonState[KEY_LEFT_SHIFT] = false;
      }
    } else if (n == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
      return;
    } else {
      this->arduinoInputAvailable = false;
      close(this->arduinoFileDescriptor);
    }
  }
}

bool InputHandler::checkArduinoQuery(int key) const {
  return key == KEY_W || key == KEY_UP || key == KEY_SPACE || key == KEY_A
    || key == KEY_LEFT || key == KEY_D || key == KEY_RIGHT
    || key == KEY_LEFT_SHIFT || key == KEY_S || key == KEY_DOWN;
}

bool InputHandler::isPressed(int key) const {
  if (this->arduinoInputAvailable && this->checkArduinoQuery(key)) {
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
}

bool InputHandler::isKeyDown(int key) const {
  if (this->arduinoInputAvailable && this->checkArduinoQuery(key)) {
    // Check for joystick input
    // current == true
    auto current{this->buttonState.find(key)};
    return current != this->buttonState.end() && current->second;
  } else {
    return IsKeyDown(key);
  }
}

bool InputHandler::isKeyReleased(int key) const {
  if (this->arduinoInputAvailable && this->checkArduinoQuery(key)) {
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

void InputHandler::resetPlayerMovement() {
  this->buttonState[KEY_A] = false;
  this->buttonState[KEY_LEFT] = false;
  this->buttonState[KEY_D] = false;
  this->buttonState[KEY_RIGHT] = false;
  this->buttonState[KEY_LEFT_SHIFT] = false;
}

}  // namespace cave_mummies::handlers
