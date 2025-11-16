// Copyright 2025 Jason Montenegro-Navarro

#ifndef CAVE_MUMMIES_STATES_MAIN_MENU_STATE_HPP
#define CAVE_MUMMIES_STATES_MAIN_MENU_STATE_HPP

#include "GameState.hpp"
#include "MenuBuilder.hpp"

namespace cave_mummies::states {

/**
 * @brief Game state for main menu screen in game.
 */
class MainMenuState : public cave_mummies::core::GameState {
 private:
  /// @brief Menu interface builder.
  cave_mummies::states::menu::MenuBuilder menuBuilder;

 public:
  /**
   * @brief Construct a new Main Menu State object.
   * @param game Game controller.
   */
  MainMenuState(cave_mummies::core::Game& game);

  /**
   * @brief Destroy the Main Menu State object.
   */
  ~MainMenuState() override = default;

  /**
   * @brief Updates menu user interaction.
   * @return New game state ID if a transition occurs, otherwise
   * this->gameState.
   */
  cave_mummies::core::GameStateID update() override;

  /**
   * @brief Builds menu interface.
   */
  void init() override;

  /**
   * @brief Renders all menu elements to the screen.
   */
  void draw() override;

 private:
  /**
   * @brief Builds main menu title.
   */
  void buildMainTitle();

  /**
   * @brief Builds score title on screen.
   */
  void buildScoreTitle();

  /**
   * @brief Adds options to menu option list.
   */
  void buildMenuOptions();
};

}  // namespace cave_mummies::states

#endif  // CAVE_MUMMIES_STATES_MAIN_MENU_STATE_HPP
