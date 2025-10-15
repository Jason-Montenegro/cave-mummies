// Copyright 2025 Jason Montenegro-Navarro

#ifndef SCOREBOARD_STATE_HPP
#define SCOREBOARD_STATE_HPP

#include "GameState.hpp"

/**
 * @brief Game state for paused screen in game.
 */
class ScoreboardState : public GameState {
 private:
  /// @brief Private members of state

 public:
  /**
   * @brief Constructor
   */
  ScoreboardState(Game &game)
    : GameState(game) {
    this->stateID = GameStateID::Paused;
  }

  /**
   * @brief Destructor
   */
  ~ScoreboardState() override;

  /**
   * @brief Updates the paused state objects.
   */
  GameStateID update() override;

  /**
   * @brief Draws the paused menu on screen.
   */
  void draw() override;
};

#endif  // SCOREBOARD_STATE_HPP
