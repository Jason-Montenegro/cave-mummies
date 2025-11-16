// Copyright 2025 Jason Montenegro-Navarro

#include <string>
#include <utility>
#include <vector>
#include "GameOverState.hpp"
#include "Game.hpp"
#include "GameStateHandler.hpp"

using MenuOptionFlag = cave_mummies::states::menu::MenuElementFlag;
using MenuElementTag = cave_mummies::states::menu::MenuElementTag;
using Collection = cave_mummies::states::menu::MenuBuilder::Collection;
using GameStateID = cave_mummies::core::GameStateID;

namespace cave_mummies::states {

GameOverState::GameOverState(cave_mummies::core::Game& game)
  : GameState(game)
  , menuBuilder(game, GameStateID::GameOver) {
  this->stateID = GameStateID::GameOver;
}

void GameOverState::init() {
  const char* basePath{GetApplicationDirectory()};
  this->background = LoadTexture((std::string(basePath)
    + "../assets/background/game_bg.png").c_str());
  // Build interface with builder
  this->menuBuilder.loadFont((std::string(basePath)
    + "../assets/fonts/PixelOperatorMono-Bold.ttf").c_str());
  this->menuBuilder.loadSelectMenuOption((std::string(basePath)
    + "../assets/audio/sfx/throw1-sfx.wav").c_str());
  this->menuBuilder.loadSubmitMenuOption((std::string(basePath)
    + "../assets/audio/sfx/throw5-sfx.wav").c_str());
  this->buildMainTitle();
  this->buildScoreTitle();
  this->buildMenuOptions();
}

void GameOverState::buildMainTitle() {
  const std::string title{"GAME OVER"};
  // Calculate the location where to place the title
  const float screenW{static_cast<float>(GetScreenWidth())};
  const float screenH{static_cast<float>(GetScreenHeight())};
  const float fontSize{screenH * 0.12f};  // 12% relative height of the screen
  Vector2 textSize{MeasureTextEx(this->menuBuilder.getLoadedFont()
    , title.c_str(), fontSize, 1.0f)};
  const float x{screenW / 2.0f - textSize.x / 2.0f};
  const float y{screenH * 0.1f};  // Upper side margin of 10%

  menu::MenuElement titleElement{.text = title, .color = WHITE
    , .flag = MenuOptionFlag::Highlight1, .tag = MenuElementTag::h1
    , .fontSize = fontSize, .position = Vector2{.x = x, .y = y}
    , .gameState = GameStateID::Null};
  this->menuBuilder.insertMenuElement(titleElement, Collection::Titles);
}

void GameOverState::buildScoreTitle() {
  std::string scoreTitle{"Final score: "};
  scoreTitle += std::to_string(this->game.getCurrentGameScore());
  // Calculate the location where to place the title
  const float screenW{static_cast<float>(GetScreenWidth())};
  const float screenH{static_cast<float>(GetScreenHeight())};
  const float fontSize{screenH * 0.08f};  // 8% relative height of the screen
  Vector2 textSize{MeasureTextEx(this->menuBuilder.getLoadedFont()
    , scoreTitle.c_str(), fontSize, 1.0f)};
  const float x{screenW / 2.0f - textSize.x / 2.0f};
  const float y{screenH * 0.3f};  // Upper side margin of 30%

  menu::MenuElement titleElement{.text = scoreTitle, .color = WHITE
    , .flag = MenuOptionFlag::None, .tag = MenuElementTag::h2
    , .fontSize = fontSize, .position = Vector2{.x = x, .y = y}
    , .gameState = GameStateID::Null};
  this->menuBuilder.insertMenuElement(titleElement, Collection::Titles);
}

void GameOverState::buildMenuOptions() {
  // Set screen details to position menu option section
  const float screenW{static_cast<float>(GetScreenWidth())};
  const float screenH{static_cast<float>(GetScreenHeight())};
  const float spacing{screenH * 0.08f};
  const float fontSize{screenH * 0.06f};  // 6% relative height of the screen
  // 2 because that's how many options are in the menu option list
  const float totalHeight{2 * spacing};
  const float startY{(screenH / 2.0f - totalHeight / 2.0f) + 100};

  const std::vector<std::pair<std::string, GameStateID>> options{
    {"Play again", GameStateID::StageOne},
    {"Save and quit", GameStateID::MainMenu},
  };

  for (int32_t i = 0; i < options.size(); ++i) {
    // Measure text size relative to screen
    Vector2 textSize{MeasureTextEx(this->menuBuilder.getLoadedFont(),
      options[i].first.c_str(), fontSize, 1.0f)};
    const float x{screenW / 2.0f - textSize.x / 2.0f};
    const float y{startY + i * spacing};
    // Configure element and insert it in the list
    this->menuBuilder.insertMenuElement(menu::MenuElement{
      .text = options[i].first, .color = WHITE
      , .flag = ((i == 0) ? MenuOptionFlag::Highlight2 : MenuOptionFlag::None)
      , .tag = MenuElementTag::li, .fontSize = fontSize
      , .position = Vector2{.x = x, .y = y}, .gameState = options[i].second,
    }, Collection::optionList);
  }
}

cave_mummies::core::GameStateID GameOverState::update() {
  GameStateID newState{this->menuBuilder.update()};
  this->updateHighestGameScore();
  this->game.setCurrentGameScore(0);
  if (newState == GameStateID::StageOne) {
    this->game.getGameStateHandler().removeState(GameStateID::StageOne);
    this->game.getGameStateHandler().registerState(GameStateID::StageOne);
  } else if (newState == GameStateID::MainMenu) {
    this->game.getGameStateHandler().removeState(GameStateID::StageOne);
  }
  return newState;
}

void GameOverState::updateHighestGameScore() {
  const uint64_t currentGameScore{this->game.getCurrentGameScore()};
  if (currentGameScore > this->game.getHighestGameScore()) {
    this->game.setHighestGameScore(currentGameScore);
  }
}

void GameOverState::draw() {
  GameState::drawBackground();
  this->menuBuilder.draw();
}

}  // namespace cave_mummies::states
