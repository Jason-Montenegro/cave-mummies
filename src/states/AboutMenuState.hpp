// Copyright 2025 Jason Montenegro-Navarro

#ifndef ABOUT_MENU_STATE_HPP
#define ABOUT_MENU_STATE_HPP

#include "GameState.hpp"

/**
 * @brief Game state for about menu screen in game.
 */
class AboutMenuState : public GameState {
 private:
  /// @brief Private members of state

 public:
  /**
   * @brief Constructor
   */
  AboutMenuState() {
    this->stateID = GameStateID::AboutMenu;
  }

  /**
   * @brief Destructor
   */
  ~AboutMenuState() override;

  /**
   * @brief Updates the about menu state objects.
   */
  GameStateID update() override;

  /**
   * @brief Draws the about menu on the screen.
   */
  void draw() override;
};

#endif  // ABOUT_MENU_STATE_HPP
