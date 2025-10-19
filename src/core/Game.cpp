// Copyright 2025 Jason Montenegro-Navarro

#include <memory>

#include "raylib.h"

#include "Game.hpp"

namespace cave_mummies::core {

Game::~Game() {
  this->gameStateHandler->cleanStates();

  if (this->loadedGame) {
    UnloadMusicStream(this->backgroundSoundtrack);
    CloseAudioDevice();
    CloseWindow();
    this->loadedGame = false;
  }

  cave_mummies::utils::Log::getInstance().stop();
}

int Game::run() {
  this->init();
  PlayMusicStream(this->backgroundSoundtrack);

  while (!WindowShouldClose()) {
    if (!this->update()) {
      break;
    }
    if (IsMusicStreamPlaying(this->backgroundSoundtrack) == 0) {
      PlayMusicStream(this->backgroundSoundtrack);
    }
    UpdateMusicStream(this->backgroundSoundtrack);
    this->draw();
  }
  this->cleanup();
  return EXIT_SUCCESS;
}

void Game::init() {
  cave_mummies::utils::Log::getInstance().start("cave_mummies.log");
  SetTraceLogCallback(Game::traceLogCallback);
  // InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), this->windowTitle.c_str());
  InitWindow(1280, 720, this->windowTitle.c_str());
  // ToggleFullscreen();
  SetTargetFPS(60);
  SetExitKey(0);
  InitAudioDevice();
  SetMasterVolume(1.0f);  /// 1.0 = 100%
  this->backgroundSoundtrack = LoadMusicStream(
    "assets/audio/music/game_soundtrack.mp3");
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

void Game::createGameStates() {
  if (this->gameStateHandler) {
    this->gameStateHandler->registerState(GameStateID::MainMenu
      , std::make_shared<cave_mummies::states::MainMenuState>(*this));
    this->gameStateHandler->registerState(GameStateID::AboutMenu
      , std::make_shared<cave_mummies::states::AboutMenuState>(*this));
    this->gameStateHandler->registerState(GameStateID::Scoreboard
      , std::make_shared<cave_mummies::states::ScoreboardState>(*this));
    this->gameStateHandler->registerState(GameStateID::Paused
      , std::make_shared<cave_mummies::states::PausedGameState>(*this));
    this->gameStateHandler->registerState(GameStateID::GameOver
      , std::make_shared<cave_mummies::states::GameOverState>(*this));
    this->gameStateHandler->registerState(GameStateID::StageOne
      , std::make_shared<cave_mummies::states::StageOneState>(*this));
  }
}

}  // namespace cave_mummies::core
