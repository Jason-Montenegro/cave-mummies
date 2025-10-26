// Copyright 2025 Jason Montenegro-Navarro

#include <exception>
#include <memory>
#include <string>

#include "raylib.h"

#include "CollisionHandler.hpp"
#include "Game.hpp"
#include "GameStateHandler.hpp"
#include "MainMenuState.hpp"
#include "InputHandler.hpp"
#include "InputSource.hpp"

using InputSourceType = cave_mummies::handlers::InputSourceType;

namespace cave_mummies::core {

Game::Game(InputSourceType inputType)
  : gameStateHandler(std::make_unique
      <cave_mummies::handlers::GameStateHandler>(*this))
  , inputHandler(std::make_unique
      <cave_mummies::handlers::InputHandler>(inputType))
  , collisionHandler(std::make_unique
      <cave_mummies::handlers::CollisionHandler>())
  , loadedGame(false) {
  this->setInputSource(inputType);
  this->gameStateHandler->registerState(GameStateID::MainMenu);
}

Game::~Game() {
  if (this->loadedGame) {
    UnloadMusicStream(this->backgroundSoundtrack);
    CloseAudioDevice();
    CloseWindow();
    this->loadedGame = false;
  }

  cave_mummies::utils::Log::getInstance().stop();
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

cave_mummies::handlers::GameStateHandler& Game::getGameStateHandler() {
  return *this->gameStateHandler;
}

cave_mummies::handlers::InputHandler& Game::getInputHandler() {
  return *this->inputHandler;
}

cave_mummies::handlers::CollisionHandler& Game::getCollisionHandler() {
  return *this->collisionHandler;
}


float Game::getGameStageFloorHeight() const {
  return (GetScreenHeight() / 2) + GetScreenHeight() * 0.3f;
}

void Game::setCurrentGameScore(int64_t score) {
  this->currentGameScore = score;
}

void Game::setHighestGameScore(int64_t score) {
  this->currentHighestGameScore = score;
}

int64_t Game::getCurrentGameScore() const {
  return this->currentGameScore;
}

int64_t Game::getHighestGameScore() const {
  return this->currentHighestGameScore;
}

int Game::run() {
  this->init();
  PlayMusicStream(this->backgroundSoundtrack);

  while (!WindowShouldClose()) {
    this->inputHandler->update();
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


bool Game::update() {
  return this->gameStateHandler->update();
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

void Game::draw() {
  BeginDrawing();
  this->gameStateHandler->draw();
  EndDrawing();
}

void Game::cleanup() {
  // Currently nothing to clean up
}

void Game::traceLogCallback(int /* logType */, const char* raylibMsg
  , va_list /* variable args */) {
  cave_mummies::utils::Log::append(cave_mummies::utils::Log::DEBUGGING,
    "Raylib", raylibMsg);
}

void Game::setInputSource(InputSourceType type) {
  this->inputHandler =
    std::make_unique<cave_mummies::handlers::InputHandler>(type);
}

}  // namespace cave_mummies::core
