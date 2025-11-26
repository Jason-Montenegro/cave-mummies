// Copyright 2025 Jason Montenegro-Navarro

#ifndef CAVE_MUMMIES_HANDLERS_GAME_STATE_HANDLER_HPP
#define CAVE_MUMMIES_HANDLERS_GAME_STATE_HANDLER_HPP

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
  /// @brief Created mapped states.
  std::map<GameStateID, std::shared_ptr<cave_mummies::core::GameState>>
    states{};
  /// @brief Currently loaded state.
  std::shared_ptr<cave_mummies::core::GameState> currentState{nullptr};
  /// @brief Game controller.
  cave_mummies::core::Game& game;

 public:
  /**
   * @brief Construct a new Game State Handler object.
   * @param game Game controller.
   */
  explicit GameStateHandler(cave_mummies::core::Game& game);

  /**
   * @brief Destroy the Game State Handler object
   */
  ~GameStateHandler() = default;

  /**
   * @brief Updates the current game state.
   * @return true if a game state update was possible, otherwise false.
   * @note If no game state update was possible, the game should close as no
   * other updates will be possible further on. Closing the game should be done
   * by the caller.
   */
  bool update();

  /**
   * @brief Draws the current game state.
   */
  void draw();

  /**
   * @brief Registers a new game state into the collection of states, only if
   * the state does not exist yet.
   * @param stateID New state ID.
   * @throw std::bad_alloc if the state could not be initialized.
   */
  void registerState(GameStateID stateID);

  /**
   * @brief Removes a state from the registered states.
   * @param stateID Game state to remove.
   */
  void removeState(GameStateID stateID);

  /**
   * @brief Sets the current game state.
   * @param stateID New state ID.
   */
  void setCurrentState(GameStateID stateID);

  /**
   * @brief Gets the current state ID
   * @return Current game state ID
   */
  GameStateID getCurrentState() const;

  /**
   * @brief Cleans all created and currently stored states.
   */
  void cleanStates();

 private:
  /**
   * @brief Initializes current game state.
   * @return true if the game state was initialized, otherwise false.
   */
  bool initCurrentState();
};

}  // cave_mummies::handlers

#endif  // CAVE_MUMMIES_HANDLERS_GAME_STATE_HANDLER_HPP
