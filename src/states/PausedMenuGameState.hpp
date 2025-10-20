// Copyright 2025 Jason Montenegro-Navarro

#ifndef PAUSED_GAME_STATE_HPP
#define PAUSED_GAME_STATE_HPP

#include <vector>

#include "GameState.hpp"

namespace cave_mummies::states {

/**
 * @brief Game state for paused screen in game.
 */
class PausedMenuGameState : public cave_mummies::core::GameState {
 private:
  /// @brief Font used for menu options
  Font menuOptionFont;
  /// @brief Sound played when switching options
  Sound selectMenuOptionSFX;
  /// @brief Sound played when menu option is submitted with return key
  Sound submitMenuOptionSFX;
  /// @brief Main menu title
  menu::MenuOption mainTitle;
  /// @brief List of interactive menu options
  std::vector<menu::MenuOption> menuOptions;

 public:
  /**
   * @brief Constructor
   */
  PausedMenuGameState(cave_mummies::core::Game& game)
    : GameState(game)
    , mainTitle("Paused"
    , menu::MenuOptionFlag::Highlight1, menu::MenuOptionTag::h1
    , WHITE) {
    this->stateID = cave_mummies::core::GameStateID::PausedMenu;
  }

  /**
   * @brief Destructor
   */
  ~PausedMenuGameState() override;

  /**
   * @brief Updates the paused state objects.
   */
  cave_mummies::core::GameStateID update() override;

  /**
   * @brief Initializes resources (textures, fonts, sounds).
   */
  void init() override;


  /**
   * @brief Draws the paused menu on screen.
   */
  void draw() override;

 private:
   /**
   * @brief Moves the highlight between menu options based on input.
   */
  void moveMenuOptionHighlight();

  /**
   * @brief Handles selection events (e.g., pressing Enter).
   * @return ID of the next game state if an option is selected.
   */
  cave_mummies::core::GameStateID addMenuOptionEventListener();

  /**
   * @brief Draws the main title text.
   */
  void drawMainTitle();

  /**
   * @brief Draws a single menu option with optional outline.
   * @param option Menu option to draw
   * @param coords Screen coordinates
   * @param fontSize Font size to use
   */
  void drawMenuOption(const menu::MenuOption& option, Vector2 coords
    , float fontSize);

  /**
   * @brief Draws all interactive menu options.
   */
  void drawMenuOptionSection();
};

}  // namespace cave_mummies::states

#endif  // PAUSED_GAME_STATE_HPP
