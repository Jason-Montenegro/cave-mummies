// Copyright 2025 Jason Montenegro-Navarro

#include <memory>
#include <utility>

#include "GameStateHandler.hpp"
#include "Game.hpp"
#include "MainMenuState.hpp"
#include "AboutMenuState.hpp"
#include "GameOverState.hpp"
#include "PausedMenuGameState.hpp"
#include "StageOneState.hpp"

namespace cave_mummies::handlers {

GameStateHandler::GameStateHandler(cave_mummies::core::Game& game)
  : game(game) { }

void GameStateHandler::setCurrentState(GameStateID stateID) {
  if (this->states.find(stateID) != this->states.end()) {
    this->currentState = this->states[stateID];
    this->initCurrentState();
  }
}

bool GameStateHandler::initCurrentState() {
  if (this->currentState) {
    this->currentState->init();
    return true;
  }
  return false;
}

GameStateID GameStateHandler::getCurrentState() const {
  if (this->currentState) {
    return this->currentState->getStateID();
  }
  return GameStateID::Null;
}

void GameStateHandler::registerState(GameStateID stateID) {
  if (this->states.find(stateID) == this->states.end()) {
    std::shared_ptr<cave_mummies::core::GameState> newState{nullptr};

    switch (stateID) {
    case GameStateID::MainMenu:
      newState =
        std::make_shared<cave_mummies::states::MainMenuState>(this->game);
      break;
    case GameStateID::AboutMenu:
      newState =
        std::make_shared<cave_mummies::states::AboutMenuState>(this->game);
      break;
    case GameStateID::GameOver:
      newState =
        std::make_shared<cave_mummies::states::GameOverState>(this->game);
      break;
    case GameStateID::PausedMenu:
      newState =
        std::make_shared<cave_mummies::states::PausedMenuGameState>(this->game);
      break;
    case GameStateID::StageOne:
      newState =
        std::make_shared<cave_mummies::states::StageOneState>(this->game);
      break;
    default:
        return;
    }
    this->states[stateID] = std::move(newState);
  }
}

void GameStateHandler::cleanStates() {
  for (auto& pair : this->states) {
    pair.second.reset();
  }
  this->states.clear();
  this->currentState = nullptr;
}

void GameStateHandler::removeState(GameStateID stateID) {
  if (this->states.find(stateID) != this->states.end()) {
    this->states.erase(stateID);
  }
}

void GameStateHandler::draw() {
  if (this->currentState) {
    this->currentState->draw();
  }
}

bool GameStateHandler::update() {
  GameStateID nextState{this->currentState->update()};

  // Close game
  if (nextState == GameStateID::QuitGame) {
    return false;
  } else if (nextState != this->currentState->getStateID()) {
    this->setCurrentState(nextState);
  }

  return true;
}

}  // namespace cave_mummies::handlers
