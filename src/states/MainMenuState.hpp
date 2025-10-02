// Copyright 2025 Jason Montenegro-Navarro

#ifndef MAIN_MENU_STATE_HPP
#define MAIN_MENU_STATE_HPP

#include "GameState.hpp"

/**
 * @brief Game state for main menu screen in game.
 */
class MainMenuState : public GameState {
 private:
  /// @brief Private members of state

 public:
  /**
   * @brief Constructor
   */
  MainMenuState() {
    this->stateID = GameStateID::MainMenu;
  }

  /**
   * @brief Destructor
   */
  ~MainMenuState() override;

  /**
   * @brief Updates the main menu state objects.
   */
  void update() override;

  /**
   * @brief Draws the main menu to screen.
   */
  void draw() override;
};

#endif  // MAIN_MENU_STATE_HPP
