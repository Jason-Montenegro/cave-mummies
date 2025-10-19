// Copyright 2025 Jason Montenegro-Navarro

#ifndef ABOUT_MENU_STATE_HPP
#define ABOUT_MENU_STATE_HPP

#include "GameState.hpp"

namespace cave_mummies::states {

/**
 * @brief Game state for about menu screen in game.
 */
class AboutMenuState : public cave_mummies::core::GameState {
 private:
  /// @brief Private members of state

 public:
  /**
   * @brief Constructor
   */
  AboutMenuState(cave_mummies::core::Game &game)
    : GameState(game) {
    this->stateID = cave_mummies::core::GameStateID::AboutMenu;
  }

  /**
   * @brief Destructor
   */
  ~AboutMenuState() override;

  /**
   * @brief Updates the about menu state objects.
   */
  cave_mummies::core::GameStateID update() override;

  /**
   * @brief Draws the about menu on the screen.
   */
  void draw() override;
};

}  // namespace cave_mummies::states

#endif  // ABOUT_MENU_STATE_HPP
