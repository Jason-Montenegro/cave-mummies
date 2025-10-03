// Copyright 2025 Jason Montenegro-Navarro

#ifndef GAME_OVER_STATE_HPP
#define GAME_OVER_STATE_HPP

#include "GameState.hpp"

/**
 * @brief Game state for game over screen in game.
 */
class GameOverState : public GameState {
 private:
  /// @brief Private members of state

 public:
  /**
   * @brief Constructor
   */
  GameOverState() {
    this->stateID = GameStateID::GameOver;
  }

  /**
   * @brief Destructor
   */
  ~GameOverState() override;

  /**
   * @brief Updates the game over state objects.
   */
  GameStateID update() override;

  /**
   * @brief Draws game over menu to screen.
   */
  void draw() override;
};

#endif  // GAME_OVER_STATE_HPP
