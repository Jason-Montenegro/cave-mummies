// Copyright 2025 Jason Montenegro-Navarro

#ifndef GAME_STATE_CONTROLLER_HPP
#define GAME_STATE_CONTROLLER_HPP

#include <map>
#include <memory>
#include <utility>

#include "GameState.hpp"
#include "MainMenuState.hpp"
#include "AboutMenuState.hpp"
#include "GameOverState.hpp"
#include "PausedGameState.hpp"
#include "ScoreboardState.hpp"
#include "LevelOneState.hpp"

/**
 * @brief Game state handler for switching game states on screen.
 */
class GameStateHandler {
 private:
  /// @brief States data members
  std::map<GameStateID, std::shared_ptr<GameState>> states;
  std::shared_ptr<GameState> currentState{nullptr};

 public:
  /**
   * @brief Deleted copy constructor.
   * @param other Other app
   */
  GameStateHandler(const GameStateHandler &other) = delete;

  /**
   * @brief Deleted move constructor.
   * @param other Other app
   */
  GameStateHandler(GameStateHandler &&other) = delete;

  /**
   * @brief Deleted copy-assignment operator.
   * @param other Other app
   */
  GameStateHandler& operator=(const GameStateHandler &other) = delete;

  /**
   * @brief Deleted move-assignment operator.
   * @param other Other app
   */
  GameStateHandler& operator=(GameStateHandler &&other) = delete;

  /**
   * @brief Constructor
   */
  GameStateHandler() = default;

  /**
   * @brief Destructor
   */
  ~GameStateHandler() = default;

  /**
   * @brief Sets the current state to stateID.
   * @param stateID New state to set
   */
  inline void setCurrentState(GameStateID stateID) {
    if (this->states.find(stateID) != this->states.end()) {
      this->currentState = this->states[stateID];
      initCurrentState();
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
   * @brief Cleans all stored states from memory.
   */
  inline void cleanStates() {
    for (auto &pair : this->states) {
      pair.second.reset();
    }
    this->states.clear();
    this->currentState = nullptr;
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
  inline bool update() {
    if (!this->currentState) {
      return true;
    }
    GameStateID nextState{this->currentState->update()};

    // Close game
    if (nextState == GameStateID::Null) {
      return false;
    }

    // Change game state
    if (nextState != this->currentState->getStateID()) {
      setCurrentState(nextState);
    }

    return true;
  }

 private:
  /**
   * @brief Initializes current state.
   * @return true if the state was initialized, false otherwise
   */
  inline bool initCurrentState() {
    if (this->currentState) {
      this->currentState->init();
      return true;
    }
    return false;
  }
};

#endif  // GAME_STATE_CONTROLLER_HPP
