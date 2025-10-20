// Copyright 2025 Jason Montenegro-Navarro

#include "Game.hpp"

int main() {
  cave_mummies::core::Game game(InputSourceType::Keyboard);
  return game.run();
}
