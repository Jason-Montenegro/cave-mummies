// Copyright 2025 Jason Montenegro-Navarro

#include "KeyboardSource.hpp"

#if defined(__linux__)
/**
 * @brief Checks if a raylib keyboard defined key is pressed.
 * @param key Keyboard key
 * @return 1 if it is pressed, 0 otherwise
 * @note Implemented in assembly
 */
extern "C" int asmIsKeyPressed(int /* key */);
#endif

bool KeyboardSource::isPressed(int key) const {
  #if defined(__APPLE__)
  return IsKeyPressed(key);
  #elif defined(__linux__)
  return (asmIsKeyPressed(key) == 1);
  #else
  return false;
  #endif
}
