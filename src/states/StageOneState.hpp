// Copyright 2025 Jason Montenegro-Navarro

#ifndef STAGE_ONE_STATE_HPP
#define STAGE_ONE_STATE_HPP

#include "GameState.hpp"

namespace cave_mummies::states {

/**
 * @brief Game state for level one screen in game.
 */
class StageOneState : public cave_mummies::core::GameState {
 private:
  /// @brief Private members of state

 public:
  /**
   * @brief Constructor
   */
  StageOneState(cave_mummies::core::Game &game)
    : GameState(game) {
    this->stateID = cave_mummies::core::GameStateID::StageOne
    ;
  }

  /**
   * @brief Destructor
   */
  ~StageOneState() override;

  /**
   * @brief Updates the level one state objects.
   */
  cave_mummies::core::GameStateID update() override;

  /**
   * @brief Draws the level one objects to screen.
   */
  void draw() override;
};

}  // namespace cave_mummies::states

#endif  // STAGE_ONE_STATE_HPP
