// Copyright 2025 Jason Montenegro-Navarro

#ifndef GAME_HPP
#define GAME_HPP

#include <cstdlib>
#include <string>

#include "Application.hpp"
#include "Log.hpp"

/**
 * @brief Game application that acts as a game controller. Holds the game loop.
 */
class Game : public Application {
 private:
  /// @brief Default game configurations
  static constexpr int32_t defaultWindowWidth{640};
  static constexpr int32_t defaultWindowHeight{480};
  static constexpr const char *const defaultWindowTitle{"My Game"};
  /// @brief Window related members
  bool isWindowFullscreen{false};
  int32_t windowWidth{Game::defaultWindowWidth};
  int32_t windowHeight{Game::defaultWindowHeight};
  std::string windowTitle{""};
  /// @brief Log raylib messages
  static Log &log;

 public:
  /**
   * @brief Windowed game constructor
   * @param windowWidth Game window width
   * @param windowHeight Game window height
   * @param windowTitle Game window title
   */
  explicit Game(const int32_t windowWidth = Game::defaultWindowWidth
    , const int32_t windowHeight = Game::defaultWindowHeight
    , std::string_view windowTitle = Game::defaultWindowTitle)
    : isWindowFullscreen(false), windowTitle(windowTitle) {
    setWindowWidth(windowWidth);
    setWindowHeight(windowHeight);
  }

  /**
   * @brief Fullscreen game constructor
   * @param windowTitle Game window title
   */
  explicit Game(std::string_view windowTitle = Game::defaultWindowTitle)
    : isWindowFullscreen(true), windowTitle(windowTitle) { }

  /**
   * @brief Starts the game loop.
   * @return EXIT_SUCCESS on successful run, EXIT_FAILURE otherwise
   */
  int run() override;

  /**
   * @brief Sets the Window Width.
   * @param windowWidth New window width
   */
  inline void setWindowWidth(const int32_t windowWidth) {
    this->windowWidth = (windowWidth < 0) ? -windowWidth : windowWidth;
  }

  /**
   * @brief Sets the Window Height.
   * @param windowHeight New window height
   */
  inline void setWindowHeight(const int32_t windowHeight) {
    this->windowHeight = (windowHeight < 0) ? -windowHeight : windowHeight;
  }

 private:
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
   */
  void update() override;

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
};

#endif  // GAME_HPP
