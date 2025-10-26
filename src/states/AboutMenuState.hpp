// Copyright 2025 Jason Montenegro-Navarro

#ifndef ABOUT_MENU_STATE_HPP
#define ABOUT_MENU_STATE_HPP

#include "GameState.hpp"
#include "MenuBuilder.hpp"

namespace cave_mummies::states {

/**
 * @brief Game state for about menu screen in game
 */
class AboutMenuState : public cave_mummies::core::GameState {
 private:
  /// @brief Menu builder
  cave_mummies::states::menu::MenuBuilder menuBuilder;

 public:
  /**
   * @brief Constructor
   */
  AboutMenuState(cave_mummies::core::Game& game);

  /**
   * @brief Destructor
   */
  ~AboutMenuState() override = default;

  /**
   * @brief Updates main menu logic
   * @return New game state ID if a transition occurs
   */
  cave_mummies::core::GameStateID update() override;

  /**
   * @brief Builds menu interface and initializes it
   */
  void init() override;

  /**
   * @brief Renders all menu elements to the screen
   */
  void draw() override;
 private:
  /**
   * @brief Builds about text box
   */
  void buildAboutTextBox();

  /**
   * @brief Adds options to menu option list
   */
  void buildMenuOptions();
};

}  // namespace cave_mummies::states

#endif  // ABOUT_MENU_STATE_HPP
