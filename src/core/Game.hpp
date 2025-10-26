// Copyright 2025 Jason Montenegro-Navarro

#ifndef GAME_HPP
#define GAME_HPP

#include <memory>

#include "raylib.h"

#include "Application.hpp"
#include "Log.hpp"

// Forward declarations
namespace cave_mummies::handlers {
  class GameStateHandler;
  class InputHandler;
  class CollisionHandler;
  enum class InputSourceType;
}

namespace cave_mummies::core {

/**
 * @brief Game controller which contains the game loop
 */
class Game : public cave_mummies::core::Application {
 private:
  /// @brief Default window title
  static constexpr const char* const defaultWindowTitle{"Cave mummies"};
  /// @brief Program logger
  static cave_mummies::utils::Log& log;
  /// @brief Game soundtrack intended to be concatenated with raylib function:
  /// GetApplicationDirectory()
  const char* soundtrackPath{"../assets/audio/music/game_soundtrack.mp3"};
  Music backgroundSoundtrack;
  bool musicPaused{false};
  /// @brief Game state handler
  std::unique_ptr<cave_mummies::handlers::GameStateHandler> gameStateHandler;
  /// @brief Player input handler
  std::unique_ptr<cave_mummies::handlers::InputHandler> inputHandler;
  /// @brief Collision handler
  std::unique_ptr<cave_mummies::handlers::CollisionHandler> collisionHandler;
  bool loadedGame{false};
  /// @brief Log filename
  static constexpr const char* const logFilename{"cave_mummies.log"};
  /// @brief Highest game score
  int64_t currentHighestGameScore{0};
  /// @brief Current game score
  int64_t currentGameScore{0};

 public:
  /**
   * @brief Game contructor
   * @param inputType User input type for game
   */
  explicit Game(handlers::InputSourceType inputType);

  /**
   * @brief Destructor
   */
  ~Game() override;

  /**
   * @brief Starts the game loop
   * @return EXIT_SUCCESS if all dependencies were created, otherwise
   * EXIT_FAILURE
   */
  int run() override;

  /**
   * @brief Getter for GameStateHandler
   * @throw std::runtime_error: if no game state handler object is available
   */
  cave_mummies::handlers::GameStateHandler& getGameStateHandler();

  /**
   * @brief Getter for InputHandler
   * @throw std::runtime_error: if no input handler object is available
   */
  cave_mummies::handlers::InputHandler& getInputHandler();
  /**
   * @brief Getter for CollisionHandler
   * @throw std::runtime_error: if no collision handler object is available
   */
  cave_mummies::handlers::CollisionHandler& getCollisionHandler();

  /**
   * @brief Getter for default game stage floor height
   */
  float getGameStageFloorHeight() const;

  /**
   * @brief Setter for current game score
   * @param score New game score
   */
  void setCurrentGameScore(int64_t score);

  /**
   * @brief Setter for current highest game score
   * @param score New game score
   */
  void setHighestGameScore(int64_t score);

  /**
   * @brief Getter for current game score
   */
  int64_t getCurrentGameScore() const;

  /**
   * @brief Getter for current highest game score
   */
  int64_t getHighestGameScore() const;

 private:
  /**
   * @brief Initializes game dependencies
   */
  void init() override;

  /**
   * @brief Updates state of game objects
   * @return true if an update was possible, otherwise false (close program)
   */
  bool update() override;

  /**
   * @brief Updates the soundtrack status if a music halt or resume happend
   */
  void updateSoundtrackStatus();

  /**
   * @brief Draws game objects to screen
   */
  void draw() override;

  /**
   * @brief No implementation provided
   * 
   * This method does nothing
   */
  void cleanup() override;

  /**
   * @brief Callback to allow Raylib to redirect its log messages to a logger
   * @param raylibMsg Raylib log message
   */
  static void traceLogCallback(int /* logType */, const char* raylibMsg
    , va_list /* variable args */);

  /**
   * @brief Sets the input source for playing the game
   * @param type User input source
   */
  void setInputSource(handlers::InputSourceType type);
};

}  // namespace cave_mummies::core

#endif  // GAME_HPP
