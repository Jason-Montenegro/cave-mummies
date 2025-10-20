// Copyright 2025 Jason Montenegro-Navarro

#ifndef SCOREBOARD_STATE_HPP
#define SCOREBOARD_STATE_HPP

#include "GameState.hpp"

namespace cave_mummies::states {

/**
 * @brief Game state for paused screen in game.
 */
class ScoreboardState : public cave_mummies::core::GameState {
 private:
  /// @brief Private members of state

 public:
  /**
   * @brief Constructor
   */
  ScoreboardState(cave_mummies::core::Game &game)
    : GameState(game) {
    this->stateID = cave_mummies::core::GameStateID::Scoreboard;
  }

  /**
   * @brief Destructor
   */
  ~ScoreboardState() override;

  /**
   * @brief Updates the paused state objects.
   */
  cave_mummies::core::GameStateID update() override;

  /**
   * @brief Draws the paused menu on screen.
   */
  void draw() override;
};

}  // namespace cave_mummies::states

#endif  // SCOREBOARD_STATE_HPP
