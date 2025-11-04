// Copyright 2025 Jason Montenegro-Navarro

#include "GameState.hpp"

namespace cave_mummies::core {

GameState::GameState(cave_mummies::core::Game& game)
  : game(game) { }

GameStateID GameState::getStateID() const {
  return this->stateID;
}

GameStateID GameState::update() {
  return this->stateID;
}

void GameState::drawBackground() {
  ClearBackground(BLACK);
  // Calculate the math for extending background to whole game screen
  Rectangle sourceRec{0.0f, 0.0f, static_cast<float>(this->background.width)
    , static_cast<float>(this->background.height)};
  Rectangle destRec{0.0f, 0.0f, static_cast<float>(GetScreenWidth())
    , static_cast<float>(GetScreenHeight())};
  Vector2 origin{0.0f, 0.0f};
  DrawTexturePro(this->background, sourceRec, destRec, origin, 0.0f, WHITE);
}

}  // namespace cave_mummies::core
