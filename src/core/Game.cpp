// Copyright 2025 Jason Montenegro-Navarro

#include <exception>
#include <memory>
#include <string>

#include "raylib.h"

#include "CollisionHandler.hpp"
#include "Game.hpp"
#include "GameStateHandler.hpp"
#include "Log.hpp"
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
}

void Game::init() {
  SetConfigFlags(FLAG_FULLSCREEN_MODE | FLAG_WINDOW_HIGHDPI);
  InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), Game::defaultWindowTitle);
  ToggleFullscreen();
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
  if (score < 0) {
    score = -score;
  }
  this->currentGameScore = score;
}

void Game::setHighestGameScore(int64_t score) {
  if (score < 0) {
    score = -score;
  }
  this->currentHighestGameScore = score;
}

uint64_t Game::getCurrentGameScore() const {
  return this->currentGameScore;
}

uint64_t Game::getHighestGameScore() const {
  return this->currentHighestGameScore;
}

cave_mummies::entities::GameTextures& Game::getGameTextures() {
  return this->gameTextures;
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

void Game::setInputSource(InputSourceType type) {
  this->inputHandler =
    std::make_unique<cave_mummies::handlers::InputHandler>(type);
}

}  // namespace cave_mummies::core
