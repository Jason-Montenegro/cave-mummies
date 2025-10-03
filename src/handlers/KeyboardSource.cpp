// Copyright 2025 Jason Montenegro-Navarro

#include "KeyboardSource.hpp"

bool KeyboardSource::isPressed(int key) const {
  return IsKeyPressed(key);
}
