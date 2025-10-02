// Copyright 2025 Jason Montenegro-Navarro

#ifndef GAME_STATE_CONTROLLER_HPP
#define GAME_STATE_CONTROLLER_HPP

#include <memory>
#include <map>
#include <utility>

#include "GameState.hpp"
#include "MainMenuState.hpp"
#include "AboutMenuState.hpp"
#include "GameOverState.hpp"
#include "PausedGameState.hpp"
#include "PlayingGameState.hpp"

/**
 * @brief Game state controller for switching game states or screens.
 */
class GameStateController {
 private:
  /// @brief States data members
  std::map<GameStateID, std::shared_ptr<GameState>> states;
  std::shared_ptr<GameState> currentState{nullptr};

 public:
  /**
   * @brief Deleted copy constructor.
   * @param other Other app
   */
  GameStateController(const GameStateController &other) = delete;

  /**
   * @brief Deleted move constructor.
   * @param other Other app
   */
  GameStateController(GameStateController &&other) = delete;

  /**
   * @brief Deleted copy-assignment operator.
   * @param other Other app
   */
  GameStateController& operator=(const GameStateController &other) = delete;

  /**
   * @brief Deleted move-assignment operator.
   * @param other Other app
   */
  GameStateController& operator=(GameStateController &&other) = delete;

  /**
   * @brief Constructor
   */
  GameStateController() = default;

  /**
   * @brief Destructor
   */
  ~GameStateController() = default;

  /**
   * @brief Sets the current state to stateID.
   * @param stateID New state to set
   */
  inline void setCurrentState(GameStateID stateID) {
    if (this->states.find(stateID) != this->states.end()) {
      this->currentState = this->states[stateID];
    }
  }

  /**
   * @brief Gets the current state ID
   * @return Current game state ID
   */
  inline GameStateID getCurrentState() const {
    if (this->currentState) {
      return this->currentState->getStateID();
    }
    return GameStateID::Null;
  }

  /**
   * @brief Registers a new GameState object into the collection of states,
   * only if the state does not exist yet. Moving the passed gameState into a
   * game states collection.
   * @param stateID Unique state identifier
   * @param gameState New game state object
   */
  inline void registerState(GameStateID stateID
    , std::shared_ptr<GameState> gameState) {
    if (this->states.find(stateID) == this->states.end()) {
      this->states[stateID] = std::move(gameState);
    }
  }

  /**
   * @brief Commands that the current state draws its state.
   */
  inline void draw() {
    if (this->currentState) {
      this->currentState->draw();
    }
  }

  /**
   * @brief Commands that the current state updates its state.
   */
  inline void update() {
    if (this->currentState) {
      this->currentState->update();
    }
  }
};

#endif  // GAME_STATE_CONTROLLER_HPP
