// Copyright 2025 Jason Montenegro-Navarro

#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "raylib.h"

/**
 * @brief Set of identifiers for every game state available.
 */
enum class GameStateID {
  Null,
  MainMenu,
  AboutMenu,
  GameOver,
  Paused,
  LevelOne,
};

/**
 * @brief Abstract game state interface. Sets game states API.
 */
class GameState {
 protected:
  /// @brief State identifier
  GameStateID stateID{GameStateID::Null};
  bool loaded{false};

 public:
  /**
   * @brief Deleted copy constructor.
   * @param other Other app
   */
  GameState(const GameState &other) = delete;

  /**
   * @brief Deleted copy-assignment operator.
   * @param other Other app
   */
  GameState& operator=(const GameState &other) = delete;

  /**
   * @brief Constructor
   */
  GameState() = default;

  /**
   * @brief Destructor
   */
  virtual ~GameState() = default;

  /**
   * @brief Gets the state ID of this.
   * @return this state ID
   */
  inline GameStateID getStateID() const { return this->stateID; }

  /**
   * @brief Updates its internal object state.
   * @return Next state that this game state transitions to.
   * @note The return value should return this state ID if no transition
   * is required.
   */
  virtual GameStateID update() {
    return this->stateID;
  };

  /**
   * @brief Initializes this object members.
   */
  virtual void init() {}

  /**
   * @brief Draws its internal object state to window.
   */
  virtual void draw() = 0;
};

#endif  // GAME_STATE_HPP
