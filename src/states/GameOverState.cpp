// Copyright 2025 Jason Montenegro-Navarro

#include "Game.hpp"
#include "GameOverState.hpp"

namespace cave_mummies::states {

GameOverState::~GameOverState() {
  // TODO(any): implement if necessary
}

cave_mummies::core::GameStateID GameOverState::update() {
  // TODO(any): implement
  return this->stateID;
}

void GameOverState::draw() {
  // TODO(any): implement
}

}  // namespace cave_mummies::states
