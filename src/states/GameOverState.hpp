// Copyright 2025 Jason Montenegro-Navarro

#ifndef GAME_OVER_STATE_HPP
#define GAME_OVER_STATE_HPP

#include "GameState.hpp"
#include "MenuBuilder.hpp"

namespace cave_mummies::states {

/**
 * @brief Game state for game over screen in game
 */
class GameOverState : public cave_mummies::core::GameState {
 private:
  /// @brief Menu builder
  cave_mummies::states::menu::MenuBuilder menuBuilder;

 public:
  /**
   * @brief Constructor
   */
  GameOverState(cave_mummies::core::Game& game);

  /**
   * @brief Destructor
   */
  ~GameOverState() override = default;
  
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
   * @brief Builds main menu title
   */
  void buildMainTitle();

  /**
   * @brief Builds score title on screen
   */
  void buildScoreTitle();

  /**
   * @brief Adds options to menu option list
   */
  void buildMenuOptions();

  /**
   * @brief Checks if the current game score is the highest overall, and if so,
   * it updates it in the game controller
   */
  void updateHighestGameScore();
};

} // namespace cave_mummies::states

#endif  // GAME_OVER_STATE_HPP
