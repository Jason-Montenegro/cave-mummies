// Copyright 2025 Jason Montenegro-Navarro

#ifndef CAVE_MUMMIES_STATES_ABOUT_MENU_STATE_HPP
#define CAVE_MUMMIES_STATES_ABOUT_MENU_STATE_HPP

#include "GameState.hpp"
#include "MenuBuilder.hpp"

namespace cave_mummies::states {

/**
 * @brief Game state for about menu screen in game.
 */
class AboutMenuState : public cave_mummies::core::GameState {
 private:
  /// @brief Menu interface builder.
  cave_mummies::states::menu::MenuBuilder menuBuilder;

 public:
  /**
   * @brief Construct a new About Menu State object.
   * @param game Game controller.
   */
  AboutMenuState(cave_mummies::core::Game& game);

  /**
   * @brief Destroy the About Menu State object.
   */
  ~AboutMenuState() override = default;

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
   * @brief Builds about text box.
   */
  void buildAboutTextBox();

  /**
   * @brief Adds options to menu option list.
   */
  void buildMenuOptions();
};

}  // namespace cave_mummies::states

#endif  // CAVE_MUMMIES_STATES_ABOUT_MENU_STATE_HPP
