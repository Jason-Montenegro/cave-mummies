// Copyright 2025 Jason Montenegro-Navarro

#include "Game.hpp"

/**
 * @brief Starts Cat mummies game.
 * @return EXIT_SUCCESS on successful run, EXIT_FAILURE otherwise
 */
int main() {
  Game game(720, 720, "Cat Mummies");
  return game.run();
}
