// Copyright 2025 (author)

#include "Game.hpp"
#include "PausedGameState.hpp"

namespace cave_mummies::states {

PausedGameState::~PausedGameState() {
  // TODO(any): implement if necessary
}

cave_mummies::core::GameStateID PausedGameState::update() {
  // TODO(any): implement
  return this->stateID;
}

void PausedGameState::draw() {
  // TODO(any): implement
}

}  // namespace cave_mummies::states
