// Copyright 2025 Jason Montenegro-Navarro

#ifndef GAME_OVER_STATE_HPP
#define GAME_OVER_STATE_HPP

#include "GameState.hpp"

namespace cave_mummies::states {

/**
 * @brief Game state for game over screen in game.
 */
class GameOverState : public cave_mummies::core::GameState {
 private:
  /// @brief Private members of state

 public:
  /**
   * @brief Constructor
   */
  GameOverState(cave_mummies::core::Game &game)
    : GameState(game) {
    this->stateID = cave_mummies::core::GameStateID::GameOver;
  }

  /**
   * @brief Destructor
   */
  ~GameOverState() override;

  /**
   * @brief Updates the game over state objects.
   */
  cave_mummies::core::GameStateID update() override;

  /**
   * @brief Draws game over menu to screen.
   */
  void draw() override;
};

} // namespace cave_mummies::states

#endif  // GAME_OVER_STATE_HPP
