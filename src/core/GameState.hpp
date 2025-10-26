// Copyright 2025 Jason Montenegro-Navarro

#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "raylib.h"

namespace cave_mummies::core {
  class Game;
};

namespace cave_mummies::core {

/**
 * @enum GameStateID
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
 * @brief Abstract game state interface. Sets game states API.
 */
class GameState {
 protected:
  /// @brief State identifier
  GameStateID stateID{GameStateID::Null};
  /// @brief Main menu background texture
  Texture2D background;
  /// @brief Is state currently loaded
  bool loaded{false};
  /// @brief Game controller object
  cave_mummies::core::Game& game;

 public:
  /**
   * @brief Constructor
   */
  GameState(cave_mummies::core::Game& game);

  /**
   * @brief Destructor
   */
  virtual ~GameState() = default;

  /**
   * @brief Getter of state id
   * @return this state id
   */
  GameStateID getStateID() const;

  /**
   * @brief Updates its internal object state
   * @return Next state that this game state transitions to
   * @note If no transition is required, return this state id
   */
  virtual GameStateID update();

  /**
   * @brief Initializes this game state
   */
  virtual void init() { }

  /**
   * @brief Draws its internal object state to window
   */
  virtual void draw() = 0;

 protected:
  /**
   * @brief Draws background image to state screen
   */
  virtual void drawBackground();
};

}  // namespace cave_mummies::core

#endif  // GAME_STATE_HPP
