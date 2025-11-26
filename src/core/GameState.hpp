// Copyright 2025 Jason Montenegro-Navarro

#ifndef CAVE_MUMMIES_CORE_GAME_STATE_HPP
#define CAVE_MUMMIES_CORE_GAME_STATE_HPP

#include "raylib.h"

namespace cave_mummies::core {

class Game;

/**
 * @brief Set of identifiers for every game state available.
 */
enum class GameStateID {
  Null,
  QuitGame,
  MainMenu,
  AboutMenu,
  PausedMenu,
  GameOver,
  StageOne
};

/**
 * @brief Abstract game state interface.
 */
class GameState {
 protected:
  /// @brief This object game state ID.
  GameStateID stateID{GameStateID::Null};
  /// @brief Game controller.
  cave_mummies::core::Game& game;
  /// @brief Background texture for this state.
  const Texture2D& background;
  /// @brief Indicates whether this state is currently loaded.
  bool loaded{false};

 public:
  /**
   * @brief Construct a new Game State object.
   * @param game Game controller.
   * @param background State background.
   */
  GameState(cave_mummies::core::Game& game, const Texture2D& background);

  /**
   * @brief Destroy the Game State object.
   */
  virtual ~GameState() = default;

  /**
   * @brief Gets the identifier of this game state.
   * @return State identifier.
   */
  GameStateID getStateID() const;

  /**
   * @brief Updates the internal state logic.
   * @return The next state to transition to.
   * @note If no transition is required, it returns this state's ID.
   */
  virtual GameStateID update();

  /**
   * @brief Initializes the game state.
   */
  virtual void init() = 0;

  /**
   * @brief Draws the current state to the window.
   */
  virtual void draw() = 0;

 protected:
  /**
   * @brief Draws the background image for this state.
   */
  virtual void drawBackground();
};

}  // namespace cave_mummies::core

#endif  // CAVE_MUMMIES_CORE_GAME_STATE_HPP
