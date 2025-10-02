// Copyright 2025 Jason Montenegro-Navarro

#ifndef PLAYING_GAME_STATE_HPP
#define PLAYING_GAME_STATE_HPP

#include "GameState.hpp"

/**
 * @brief Game state for level one screen in game.
 */
class LevelOneState : public GameState {
 private:
  /// @brief Private members of state

 public:
  /**
   * @brief Constructor
   */
  LevelOneState() {
    this->stateID = GameStateID::LevelOne;
  }

  /**
   * @brief Destructor
   */
  ~LevelOneState() override;

  /**
   * @brief Updates the level one state objects.
   */
  void update() override;

  /**
   * @brief Draws the level one objects to screen.
   */
  void draw() override;
};

#endif  // PLAYING_GAME_STATE_HPP
