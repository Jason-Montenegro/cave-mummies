// Copyright 2025 Jason Montenegro-Navarro

#ifndef GAME_HPP
#define GAME_HPP

#include <cstdlib>
#include <memory>
#include <string>

#include "Application.hpp"
#include "CollisionHandler.hpp"
#include "GameStateHandler.hpp"
#include "InputHandler.hpp"
#include "JoystickSource.hpp"
#include "KeyboardSource.hpp"
#include "Log.hpp"
#include "SpawnHandler.hpp"

/**
 * @brief Input source type for playing the game.
 */
enum class InputSourceType {
  Keyboard,
  Joystick
};

/**
 * @brief Game application that acts as a game controller. Holds the game loop.
 */
class Game : public Application {
 private:
  /// @brief Default game configurations
  static constexpr int32_t defaultWindowWidth{640};
  static constexpr int32_t defaultWindowHeight{480};
  ///< Top window title
  static constexpr const char *const defaultWindowTitle{"My Game"};
  /// @brief Window related members
  bool isWindowFullscreen{false};
  int32_t windowWidth{Game::defaultWindowWidth};
  int32_t windowHeight{Game::defaultWindowHeight};
  std::string windowTitle{""};
  /// @brief Log raylib messages
  static Log &log;
  /// @brief Game handlers
  std::unique_ptr<GameStateHandler> gameStateHandler;
  std::unique_ptr<InputHandler> inputHandler;
  std::unique_ptr<CollisionHandler> collisionHandler;
  std::unique_ptr<SpawnHandler> spawnHandler;
  bool loadedGame{false};

 public:
  /**
   * @brief Windowed game constructor
   * @param inputType User input type for game
   * @param windowWidth Game window width
   * @param windowHeight Game window height
   * @param windowTitle Game window title
   */
  explicit Game(InputSourceType inputType = InputSourceType::Keyboard
    ,const int32_t windowWidth = Game::defaultWindowWidth
    , const int32_t windowHeight = Game::defaultWindowHeight
    , std::string_view windowTitle = Game::defaultWindowTitle)
    : isWindowFullscreen(false), windowTitle(windowTitle)
    , gameStateHandler(std::make_unique<GameStateHandler>())
    , inputHandler(nullptr)
    , collisionHandler(std::make_unique<CollisionHandler>())
    , spawnHandler(std::make_unique<SpawnHandler>())
    , loadedGame(false) {
    this->setWindowWidth(windowWidth);
    this->setWindowHeight(windowHeight);
    this->setInputSource(inputType);
    this->createGameStates();
  }

  /**
   * @brief Fullscreen game constructor
   * @param inputType User input type for game
   * @param windowTitle Game window title
   */
  explicit Game(InputSourceType inputType
    , std::string_view windowTitle = Game::defaultWindowTitle)
    : isWindowFullscreen(true), windowTitle(windowTitle)
    , gameStateHandler(std::make_unique<GameStateHandler>())
    , inputHandler(nullptr)
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
   * @return EXIT_SUCCESS on successful run, EXIT_FAILURE otherwise
   */
  int run() override;

  /**
   * @brief Sets the Window Width.
   * @param windowWidth New window width
   */
  inline void setWindowWidth(int32_t windowWidth) {
    this->windowWidth = (windowWidth < 0) ? -windowWidth : windowWidth;
  }

  /**
   * @brief Sets the Window Height.
   * @param windowHeight New window height
   */
  inline void setWindowHeight(int32_t windowHeight) {
    this->windowHeight = (windowHeight < 0) ? -windowHeight : windowHeight;
  }

  /**
   * @brief Getter for GameStateHandler
   */
  inline GameStateHandler& getGameStateHandler() {
    return *this->gameStateHandler;
  }

  /**
   * @brief Getter for InputHandler
   */
  inline InputHandler& getInputHandler() {
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
  /**
   * @brief Sets the input source for playing the game.
   * @param type Input source (Keyboard or joystick)
   */
  inline void setInputSource(InputSourceType type = InputSourceType::Keyboard) {
    std::shared_ptr<InputSource> source;
    switch (type) {
    case InputSourceType::Keyboard:
      source = std::make_shared<KeyboardSource>(); break;
    case InputSourceType::Joystick:
      source = std::make_shared<JoystickSource>(); break;
    default: 
      source = std::make_shared<KeyboardSource>(); break;
    }
    this->inputHandler = std::make_unique<InputHandler>(source);
  }

  /**
   * @brief Initializes application configuration.
   */
  void init() override;

  /**
   * @brief Checks if the set window dimensions are valid.
   * @return true Dimensions are greater than zero
   * @return false Any other case
   */
  inline bool validWindowDimension() const {
    return this->windowWidth > 0 && this->windowHeight > 0;
  }

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
  static inline void traceLogCallback(int /* logType */, const char *raylibMsg
    , va_list /* va_list */) {
    Log::append(Log::DEBUGGING, "Raylib", raylibMsg);
  }

  /**
   * @brief Creates all game state objects for this game
   */
  inline void createGameStates() {
    if (this->gameStateHandler) {
      this->gameStateHandler->registerState(GameStateID::MainMenu
        , std::make_shared<MainMenuState>(*this));
      this->gameStateHandler->registerState(GameStateID::AboutMenu
        , std::make_shared<AboutMenuState>(*this));
      this->gameStateHandler->registerState(GameStateID::Scoreboard
        , std::make_shared<ScoreboardState>(*this));
      this->gameStateHandler->registerState(GameStateID::Paused
        , std::make_shared<PausedGameState>(*this));
      this->gameStateHandler->registerState(GameStateID::GameOver
        , std::make_shared<GameOverState>(*this));
        this->gameStateHandler->registerState(GameStateID::LevelOne
        , std::make_shared<LevelOneState>(*this));
    }
  }
};

#endif  // GAME_HPP
