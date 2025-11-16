// Copyright 2025 Jason Montenegro-Navarro

#include <exception>
#include <memory>
#include <string>
#include "raylib.h"
#include "Game.hpp"
#include "CollisionHandler.hpp"
#include "GameStateHandler.hpp"
#include "InputHandler.hpp"
#include "MainMenuState.hpp"
#include "TextureManager.hpp"

using InputSourceType = cave_mummies::handlers::InputSourceType;

namespace cave_mummies::core {

Game::Game()
  : gameStateHandler(std::make_unique
      <cave_mummies::handlers::GameStateHandler>(*this))
  , inputHandler(std::make_unique
      <cave_mummies::handlers::InputHandler>())
  , collisionHandler(std::make_unique
      <cave_mummies::handlers::CollisionHandler>()) { }

Game::~Game() {
  if (this->loadedGame) {
    UnloadMusicStream(this->backgroundSoundtrack);
    CloseAudioDevice();
    CloseWindow();
    this->loadedGame = false;
  }
}

void Game::init() {
  SetTargetFPS(60);
  #ifdef DEBUG
  SetConfigFlags(FLAG_BORDERLESS_WINDOWED_MODE);
  InitWindow(1400, 800, Game::defaultWindowTitle);
  #else
  SetConfigFlags(FLAG_FULLSCREEN_MODE);
  InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), Game::defaultWindowTitle);
  #endif
  SetExitKey(0);  // Deactive Esc key as exit program key
  SetMousePosition(GetScreenWidth() / 2, GetScreenHeight() / 2);
  InitAudioDevice();
  SetMasterVolume(1.0f);  // 1.0 = 100%
  const char* basePath{GetApplicationDirectory()};
  std::string filename{basePath};
  filename += this->soundtrackPath;
  this->backgroundSoundtrack = LoadMusicStream(filename.c_str());
  this->gameStateHandler->registerState(GameStateID::MainMenu);
  this->gameStateHandler->setCurrentState(GameStateID::MainMenu);
  // Initialize all game textures
  this->textureManager = std::make_unique<cave_mummies::core::TextureManager>();
  this->loadedGame = true;
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

cave_mummies::core::TextureManager& Game::getTextureManager() {
  return *this->textureManager;
}

float Game::getGameStageFloorHeight() const {
  return (GetScreenHeight() / 2.0f) + GetScreenHeight() * 0.3f;
}

void Game::setCurrentGameScore(int64_t score) {
  this->currentGameScore = (score < 0) ? -score : score;
}

void Game::setHighestGameScore(int64_t score) {
  this->currentHighestGameScore = (score < 0) ? -score : score;
}

uint64_t Game::getCurrentGameScore() const {
  return this->currentGameScore;
}

uint64_t Game::getHighestGameScore() const {
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
  return EXIT_SUCCESS;
}

bool Game::update() {
  return this->gameStateHandler->update();
}

void Game::updateSoundtrackStatus() {
  if (this->inputHandler->isPressed(KEY_M)) {
    if (this->isMusicPaused) {
      ResumeMusicStream(this->backgroundSoundtrack);
      this->isMusicPaused = false;
    } else {
      PauseMusicStream(this->backgroundSoundtrack);
      this->isMusicPaused = true;
    }
  }
}

void Game::draw() {
  BeginDrawing();
  this->gameStateHandler->draw();
  EndDrawing();
}

}  // namespace cave_mummies::core
