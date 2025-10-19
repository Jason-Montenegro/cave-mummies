// Copyright 2025 Jason Montenegro-Navarro

#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <string>

#include "Application.hpp"
#include "CollisionHandler.hpp"
#include "GameStateHandler.hpp"
#include "InputHandler.hpp"
#include "InputSource.hpp"
#include "Log.hpp"
#include "SpawnHandler.hpp"

using InputSourceType = cave_mummies::handlers::InputSourceType;
namespace cave_mummies::core {

/**
 * @brief Game application that acts as a game controller.
 * Manages the game loop.
 */
class Game : public cave_mummies::core::Application {
 public:
  /**
   * @brief Fullscreen game constructor
   * @param inputType User input type for game
   * @param windowTitle Game window title
   */
  explicit Game(InputSourceType inputType
    , std::string_view windowTitle = Game::defaultWindowTitle)
    : windowTitle(windowTitle)
    , gameStateHandler(std::make_unique<GameStateHandler>())
    , inputHandler(std::make_unique<cave_mummies::handlers::InputHandler>(
        InputSourceType::Keyboard))
    , collisionHandler(std::make_unique<CollisionHandler>())
    , spawnHandler(std::make_unique<SpawnHandler>())
    , loadedGame(false) {
    this->setInputSource(inputType);
    this->createGameStates();
  }

  /**
   * @brief Destructor
   */
  ~Game() override;

  /**
   * @brief Starts the game loop.
   * @return EXIT_SUCCESS
   */
  int run() override;

  /**
   * @brief Getter for GameStateHandler
   */
  inline GameStateHandler& getGameStateHandler() {
    return *this->gameStateHandler;
  }

  /**
   * @brief Getter for InputHandler
   */
  inline cave_mummies::handlers::InputHandler& getInputHandler() {
    return *this->inputHandler;
  }

  /**
   * @brief Getter for CollisionHandler
   */
  inline CollisionHandler& getCollisionHandler() {
    return *this->collisionHandler;
  }

  /**
   * @brief Getter for SpawnHandler
   */
  inline SpawnHandler& getSpawnHandler() {
    return *this->spawnHandler;
  }

 private:
  /// @brief Default top window title
  static constexpr const char* const defaultWindowTitle{"Cave mummies"};
  std::string windowTitle{Game::defaultWindowTitle};
  int32_t windowWidth;
  int32_t windowHeight;
  /// @brief Log raylib messages
  static Log& log;
  /// @brief Game state handler
  std::unique_ptr<GameStateHandler> gameStateHandler;
  /// @brief Player input handler
  std::unique_ptr<cave_mummies::handlers::InputHandler> inputHandler;
  /// @brief Collision handler
  std::unique_ptr<CollisionHandler> collisionHandler;
  /// @brief Entitiy spawn handler
  std::unique_ptr<SpawnHandler> spawnHandler;
  bool loadedGame{false};

  /**
   * @brief Sets the input source for playing the game.
   * @param type Input source (Keyboard or joystick)
   */
  inline void setInputSource(InputSourceType type = InputSourceType::Keyboard) {
    this->inputHandler =
      std::make_unique<cave_mummies::handlers::InputHandler>(type);
  }

  /**
   * @brief Initializes application configuration.
   */
  void init() override;

  /**
   * @brief Creates all game state objects for this game
   */
  void createGameStates();

  /**
   * @brief Updates state of game objects.
   * @return true if an update was possible, false otherwise (program close)
   */
  bool update() override;

  /**
   * @brief Draws game objects sprites to screen.
   */
  void draw() override;

  /**
   * @brief Cleans game objects.
   */
  void cleanup() override;

  /**
   * @brief Callback to let Raylib redirect its log messages to a controlled
   * log object.
   * @param raylibMsg Raylib log message
   */
  static inline void traceLogCallback(int /* logType */, const char* raylibMsg
    , va_list /* va_list */) {
    Log::append(Log::DEBUGGING, "Raylib", raylibMsg);
  }
};

}  // namespace cave_mummies::core

#endif  // GAME_HPP
