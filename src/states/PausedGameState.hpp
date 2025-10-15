// Copyright 2025 Jason Montenegro-Navarro

#ifndef PAUSED_GAME_STATE_HPP
#define PAUSED_GAME_STATE_HPP

#include "GameState.hpp"

/**
 * @brief Game state for paused screen in game.
 */
class PausedGameState : public GameState {
 private:
  /// @brief Private members of state

 public:
  /**
   * @brief Constructor
   */
  PausedGameState(Game &game)
    : GameState(game) {
    this->stateID = GameStateID::Paused;
  }

  /**
   * @brief Destructor
   */
  ~PausedGameState() override;

  /**
   * @brief Updates the paused state objects.
   */
  GameStateID update() override;

  /**
   * @brief Draws the paused menu on screen.
   */
  void draw() override;
};

#endif  // PAUSED_GAME_STATE_HPP
