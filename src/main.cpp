// Copyright 2025 Jason Montenegro-Navarro

#include "Game.hpp"
#ifdef DEBUG
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
#endif

/**
 * @brief Program entry point.
 * @return EXIT_SUCCESS on successful run, otherwise EXIT_FAILURE.
 */
int main() {
  #ifdef DEBUG
  cave_mummies::utils::Log::getInstance().start("cave_mummies.log");
  SetTraceLogCallback(traceLogCallback);
  #endif
  try {
    cave_mummies::core::Game game;
    game.run();
  } catch (const std::exception& e) {
    #ifdef DEBUG
    cave_mummies::utils::Log::append(cave_mummies::utils::Log::ERROR, "Main"
      , e.what());
    #endif
  }
  #ifdef DEBUG
  cave_mummies::utils::Log::getInstance().stop();
  #endif
  return EXIT_SUCCESS;
}
