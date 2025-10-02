// Copyright 2025 Jason Montenegro-Navarro

#include "raylib.h"
#include "Game.hpp"

int Game::run() {
  if (this->validWindowDimension()) {
    this->init();

    while (!WindowShouldClose()) {
      this->update();
      this->draw();
    }
    this->cleanup();
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

void Game::init() {
  Log::getInstance().start("cat_mummies.log");
  SetTraceLogCallback(Game::traceLogCallback);

  if (isWindowFullscreen) {
    this->windowWidth = GetMonitorWidth(0);
    this->windowHeight = GetMonitorWidth(0);
  }

  InitWindow(this->windowWidth, this->windowWidth, this->windowTitle.c_str());
  SetTargetFPS(60);

  if (isWindowFullscreen) {
    ToggleFullscreen();
  }
}

void Game::update() {
  // Section to update game objects state. No game objects yet.
}

void Game::draw() {
  BeginDrawing();
  // Section to draw game objects. No game objects yet.

  EndDrawing();
}

void Game::cleanup() {
  CloseWindow();
  Log::getInstance().stop();
}
