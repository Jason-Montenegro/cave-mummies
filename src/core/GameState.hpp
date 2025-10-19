// Copyright 2025 Jason Montenegro-Navarro

#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "raylib.h"

namespace cave_mummies::core {
  class Game;

/// @enum GameStateID
/// @brief Set of identifiers for every game state available.
enum class GameStateID {
  Null,
  MainMenu,
  AboutMenu,
  GameOver,
  Paused,
  StageOne,
  Scoreboard,
};

/**
 * @brief Abstract game state interface. Sets game states API.
 */
class GameState {
 protected:
  /// @brief State identifier
  GameStateID stateID{GameStateID::Null};
  bool loaded{false};
  /// @brief Game controller object
  Game& game;

 public:
  /**
   * @brief Constructor
   */
  GameState(Game &game)
    : game(game) { }

  /**
   * @brief Destructor
   */
  virtual ~GameState() = default;

  /**
   * @brief Gets the state ID of this.
   * @return this StateID
   */
  inline GameStateID getStateID() const {
    return this->stateID;
  }

  /**
   * @brief Updates its internal object state.
   * @return Next state that this game state transitions to.
   * @note The return value should return this state ID if no transition
   * is required.
   */
  virtual GameStateID update() {
    return this->stateID;
  }

  /**
   * @brief Initializes this object members.
   */
  virtual void init() {}

  /**
   * @brief Draws its internal object state to window.
   */
  virtual void draw() = 0;
};

}  // namespace cave_mummies::core

#endif  // GAME_STATE_HPP
