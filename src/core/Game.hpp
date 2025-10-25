// Copyright 2025 Jason Montenegro-Navarro

#ifndef GAME_HPP
#define GAME_HPP

#include <exception>
#include <memory>
#include <string>

#include "Application.hpp"
#include "CollisionHandler.hpp"
#include "GameStateHandler.hpp"
#include "InputHandler.hpp"
#include "InputSource.hpp"
#include "Log.hpp"

using InputSourceType = cave_mummies::handlers::InputSourceType;

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

 public:
  /**
   * @brief Game contructor
   * @param inputType User input type for game
   */
  explicit Game(InputSourceType inputType)
    : gameStateHandler(std::make_unique
        <cave_mummies::handlers::GameStateHandler>())
    , inputHandler(std::make_unique
        <cave_mummies::handlers::InputHandler>(inputType))
    , collisionHandler(std::make_unique
        <cave_mummies::handlers::CollisionHandler>())
    , loadedGame(false) {
    this->setInputSource(inputType);
    this->gameStateHandler->registerState(GameStateID::MainMenu
        , std::make_shared<cave_mummies::states::MainMenuState>(*this));
  }

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
  inline cave_mummies::handlers::GameStateHandler& getGameStateHandler() {
    return *this->gameStateHandler;
  }

  /**
   * @brief Getter for InputHandler
   * @throw std::runtime_error: if no input handler object is available
   */
  inline cave_mummies::handlers::InputHandler& getInputHandler() {
    return *this->inputHandler;
  }

  /**
   * @brief Getter for CollisionHandler
   * @throw std::runtime_error: if no collision handler object is available
   */
  inline cave_mummies::handlers::CollisionHandler& getCollisionHandler() {
    return *this->collisionHandler;
  }

  /**
   * @brief Getter for deafult game stage floor height
   */
  inline float getGameStageFloorHeight() const {
    return (GetScreenHeight() / 2) + GetScreenHeight() * 0.3f;
  }

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
  static inline void traceLogCallback(int /* logType */, const char* raylibMsg
    , va_list /* variable args */) {
    cave_mummies::utils::Log::append(cave_mummies::utils::Log::DEBUGGING,
      "Raylib", raylibMsg);
  }

  /**
   * @brief Sets the input source for playing the game
   * @param type User input source
   */
  inline void setInputSource(InputSourceType type = InputSourceType::Keyboard) {
    this->inputHandler =
      std::make_unique<cave_mummies::handlers::InputHandler>(type);
  }
};

}  // namespace cave_mummies::core

#endif  // GAME_HPP
