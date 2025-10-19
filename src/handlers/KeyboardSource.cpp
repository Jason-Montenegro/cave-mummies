// Copyright 2025 Jason Montenegro-Navarro

#include "KeyboardSource.hpp"

namespace cave_mummies::handlers {

bool KeyboardSource::isPressed(int key) const {
  return IsKeyPressed(key);
}

}  // namespace cave_mummies::handlers
