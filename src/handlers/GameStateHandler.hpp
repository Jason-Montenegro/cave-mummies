// Copyright 2025 Jason Montenegro-Navarro

#ifndef GAME_STATE_CONTROLLER_HPP
#define GAME_STATE_CONTROLLER_HPP

#include <map>
#include <memory>

#include "GameState.hpp"

namespace cave_mummies::core {
  class Game;
}

using GameStateID = cave_mummies::core::GameStateID;

namespace cave_mummies::handlers {

/**
 * @brief Game state handler for switching game states on screen.
 */
class GameStateHandler {
 private:
  /// @brief All states collection
  std::map<GameStateID, std::shared_ptr<cave_mummies::core::GameState>> states;
  /// @brief Current loaded state
  std::shared_ptr<cave_mummies::core::GameState> currentState;
  /// @brief Game controller
  cave_mummies::core::Game& game;


 public:
  /**
   * @brief Constructor
   * @param game Game controller
   */
  explicit GameStateHandler(cave_mummies::core::Game& game);

  /**
   * @brief Destructor
   */
  ~GameStateHandler() = default;

  /**
   * @brief Sets the current state to stateID.
   * @param stateID New state to set
   */
  void setCurrentState(GameStateID stateID);

  /**
   * @brief Gets the current state ID
   * @return Current game state ID
   */
  GameStateID getCurrentState() const;

  /**
   * @brief Registers a new GameState object into the collection of states,
   * only if the state does not exist yet
   * @param stateID Unique state identifier
   */
  void registerState(GameStateID stateID);

  /**
   * @brief Cleans all stored states from memory.
   */
  void cleanStates();

  /**
   * @brief Removes a state from the registered states
   * @param stateID State identifier to remove
   */
  void removeState(GameStateID stateID);

  /**
   * @brief Commands that the current state draws its state.
   */
  void draw();

  /**
   * @brief Commands that the current state updates its state
   * @return true if a game update was possible, otherwise false (close program)
   */
  bool update();

 private:
  /**
   * @brief Initializes current state.
   * @return true if the state was initialized, false otherwise
   */
  bool initCurrentState();
};

}  // cave_mummies::handlers

#endif  // GAME_STATE_CONTROLLER_HPP
