// Copyright 2025 Jason Montenegro-Navarro

#include "Game.hpp"
#include "Log.hpp"

/**
 * @brief Callback to allow Raylib to redirect its log messages to a logger.
 * @param raylibMsg Raylib log message.
 */
void traceLogCallback(int /* logType */, const char* raylibMsg
  , va_list /* variable args */) {
  cave_mummies::utils::Log::append(cave_mummies::utils::Log::DEBUGGING
    , "Raylib", raylibMsg);
}

/**
 * @brief Program entry point.
 * @return EXIT_SUCCESS on successful run, otherwise EXIT_FAILURE.
 */
int main() {
  cave_mummies::utils::Log::getInstance().start("cave_mummies.log");
  SetTraceLogCallback(traceLogCallback);
  try {
    cave_mummies::core::Game game;
    game.run();
  } catch (const std::exception& e) {
    cave_mummies::utils::Log::append(cave_mummies::utils::Log::ERROR, "Main"
      , e.what());
  }
  cave_mummies::utils::Log::getInstance().stop();
  return EXIT_SUCCESS;
}
