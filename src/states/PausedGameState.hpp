// Copyright 2025 Jason Montenegro-Navarro

#ifndef PAUSED_GAME_STATE_HPP
#define PAUSED_GAME_STATE_HPP

#include "GameState.hpp"

namespace cave_mummies::states {

/**
 * @brief Game state for paused screen in game.
 */
class PausedGameState : public cave_mummies::core::GameState {
 private:
  /// @brief Private members of state

 public:
  /**
   * @brief Constructor
   */
  PausedGameState(cave_mummies::core::Game &game)
    : GameState(game) {
    this->stateID = cave_mummies::core::GameStateID::Paused;
  }

  /**
   * @brief Destructor
   */
  ~PausedGameState() override;

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

#endif  // PAUSED_GAME_STATE_HPP
