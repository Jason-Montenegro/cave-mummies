// Copyright 2025 Jason Montenegro-Navarro

#include "raylib.h"
#include "Game.hpp"

Game::~Game() {
  gameStateController.cleanStates();

  if (this->loadedGame) {
    CloseAudioDevice();
    CloseWindow();
    this->loadedGame = false;
  }

  Log::getInstance().stop();
}

int Game::run() {
  if (this->validWindowDimension()) {
    this->init();

    while (!WindowShouldClose()) {
      if (!this->update()) {
        break;
      }
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
  SetExitKey(0);
  InitAudioDevice();
  SetMasterVolume(1.0f);  // 1.0 = 100%

  if (isWindowFullscreen) {
    ToggleFullscreen();
  }
  this->loadedGame = true;
  gameStateController.setCurrentState(GameStateID::MainMenu);
}

bool Game::update() {
  if (!gameStateController.update()) {
    return false;
  }
  return true;
}

void Game::draw() {
  BeginDrawing();
  gameStateController.draw();
  EndDrawing();
}

void Game::cleanup() {
}
