// Copyright 2025 Jason Montenegro-Navarro

#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "raylib.h"

namespace cave_mummies::core {
  class Game;

/// @enum GameStateID
/// @brief Set of identifiers for every game state available.
enum class GameStateID {
  Null,
  MainMenu,
  AboutMenu,
  PausedMenu,
  GameOver,
  StageOne,
  Scoreboard,
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
  Game& game;

 public:
  /**
   * @brief Constructor
   */
  GameState(Game &game)
    : game(game) { }

  /**
   * @brief Destructor
   */
  virtual ~GameState() = default;

  /**
   * @brief Gets the state ID of this.
   * @return this StateID
   */
  inline GameStateID getStateID() const {
    return this->stateID;
  }

  /**
   * @brief Updates its internal object state.
   * @return Next state that this game state transitions to.
   * @note The return value should return this state ID if no transition
   * is required.
   */
  virtual GameStateID update() {
    return this->stateID;
  }

  /**
   * @brief Initializes this object members.
   */
  virtual void init() {}

  /**
   * @brief Draws its internal object state to window.
   */
  virtual void draw() = 0;

 protected:
  /**
   * @brief Draws background image to state screen.
   */
  virtual void drawBackground() {
    ClearBackground(BLACK);
    // Calculate the math for extending background to whole game screen
    Rectangle sourceRec{0.0f, 0.0f, static_cast<float>(this->background.width)
      , static_cast<float>(this->background.height)};
    Rectangle destRec{0.0f, 0.0f, static_cast<float>(GetScreenWidth())
      , static_cast<float>(GetScreenHeight())};
    Vector2 origin{0.0f, 0.0f};
    DrawTexturePro(this->background, sourceRec, destRec, origin, 0.0f, WHITE);
  };
};

}  // namespace cave_mummies::core

#endif  // GAME_STATE_HPP
