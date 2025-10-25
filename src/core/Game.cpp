// Copyright 2025 Jason Montenegro-Navarro

#include <memory>
#include <string>

#include "raylib.h"

#include "Game.hpp"

namespace cave_mummies::core {

Game::~Game() {
  if (this->loadedGame) {
    UnloadMusicStream(this->backgroundSoundtrack);
    CloseAudioDevice();
    CloseWindow();
    this->loadedGame = false;
  }

  cave_mummies::utils::Log::getInstance().stop();
}

int Game::run() {
  if (!this->gameStateHandler || !this->inputHandler
      || !this->collisionHandler) {
    return EXIT_FAILURE;
  }

  this->init();
  PlayMusicStream(this->backgroundSoundtrack);

  while (!WindowShouldClose()) {
    if (!this->update()) {
      break;
    }
    this->updateSoundtrackStatus();
    UpdateMusicStream(this->backgroundSoundtrack);
    this->draw();
  }
  this->cleanup();
  return EXIT_SUCCESS;
}

void Game::updateSoundtrackStatus() {
  if (this->inputHandler->isPressed(KEY_M)) {
    if (this->musicPaused) {
      ResumeMusicStream(this->backgroundSoundtrack);
      this->musicPaused = false;
    } else {
      PauseMusicStream(this->backgroundSoundtrack);
      this->musicPaused = true;
    }
  }
}

void Game::init() {
  cave_mummies::utils::Log::getInstance().start(Game::logFilename);
  SetTraceLogCallback(Game::traceLogCallback);
  SetConfigFlags(FLAG_FULLSCREEN_MODE | FLAG_WINDOW_HIGHDPI);
  InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), Game::defaultWindowTitle);
  SetTargetFPS(60);
  SetExitKey(0);  // Deactive Esc key as exit program key
  SetMousePosition(GetScreenWidth()/2, GetScreenHeight()/2);
  InitAudioDevice();
  SetMasterVolume(1.0f);  // 1.0 = 100%
  const char* basePath{GetApplicationDirectory()};
  this->backgroundSoundtrack = LoadMusicStream((std::string(basePath)
    + std::string(this->soundtrackPath)).c_str());
  this->loadedGame = true;
  this->gameStateHandler->setCurrentState(GameStateID::MainMenu);
}

bool Game::update() {
  if (!this->gameStateHandler->update()) {
    return false;
  }
  return true;
}

void Game::draw() {
  BeginDrawing();
  this->gameStateHandler->draw();
  EndDrawing();
}

void Game::cleanup() {
  // Currently nothing to clean up
}

}  // namespace cave_mummies::core
