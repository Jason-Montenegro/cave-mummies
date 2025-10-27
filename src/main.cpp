// Copyright 2025 Jason Montenegro-Navarro

#include "Game.hpp"
#include "KeyboardSource.hpp"
#include "Log.hpp"

using Game = cave_mummies::core::Game;

/**
 * @brief Callback to allow Raylib to redirect its log messages to a logger
 * @param raylibMsg Raylib log message
 */
void traceLogCallback(int /* logType */, const char* raylibMsg
  , va_list /* variable args */) {
  cave_mummies::utils::Log::append(cave_mummies::utils::Log::DEBUGGING,
    "Raylib", raylibMsg);
}

/**
 * @brief Program entry point
 * @return EXIT_SUCCESS on successful run, otherwise EXIT_FAILURE
 */
int main() {
  cave_mummies::utils::Log::getInstance().start("cave_mummies.log");
  SetTraceLogCallback(traceLogCallback);

  try {
    Game game(cave_mummies::handlers::InputSourceType::Keyboard);
    game.run();
  } catch (const std::exception& e) {
    cave_mummies::utils::Log::append(cave_mummies::utils::Log::ERROR,
      "Main", e.what());
    return EXIT_FAILURE;
  }

  cave_mummies::utils::Log::getInstance().stop();
  return EXIT_SUCCESS;
}
