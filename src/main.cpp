// Copyright 2025 Jason Montenegro-Navarro

#include "Game.hpp"
#include "KeyboardSource.hpp"

int main() {
  cave_mummies::core::Game game(
    cave_mummies::handlers::InputSourceType::Keyboard);
  return game.run();
}
