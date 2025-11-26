// Copyright 2025 Jason Montenegro-Navarro

#include <string>
#include <utility>
#include <vector>
#include "MainMenuState.hpp"
#include "Game.hpp"

using MenuOptionFlag = cave_mummies::states::menu::MenuElementFlag;
using MenuElementTag = cave_mummies::states::menu::MenuElementTag;
using Collection = cave_mummies::states::menu::MenuBuilder::Collection;
using GameStateID = cave_mummies::core::GameStateID;

namespace cave_mummies::states {

MainMenuState::MainMenuState(cave_mummies::core::Game& game)
  : GameState(game, game.getTextureManager().getTexture(
    cave_mummies::core::TextureID::GameBackground))
  , menuBuilder(game, GameStateID::MainMenu) {
  this->stateID = GameStateID::MainMenu;
}

void MainMenuState::init() {
  const char* basePath{GetApplicationDirectory()};
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

void MainMenuState::buildMainTitle() {
  const std::string title{"Cave Mummies"};
  // Calculate the location where to place the title
  const float screenW{static_cast<float>(GetScreenWidth())};
  const float screenH{static_cast<float>(GetScreenHeight())};
  const float fontSize{screenH * 0.12f};  // 12% relative height of the screen
  Vector2 textSize{MeasureTextEx(this->menuBuilder.getLoadedFont()
    , title.c_str(), fontSize, 1.0f)};
  const float x{screenW / 2.0f - textSize.x / 2.0f};
  const float y{screenH * 0.1f};  // Upper side margin of 10%

  menu::MenuElement titleElement{.text = title, .color = WHITE
    , .flag = MenuOptionFlag::Highlight2, .tag = MenuElementTag::li
    , .fontSize = fontSize, .position = Vector2{.x = x, .y = y}
    , .gameState = GameStateID::Null};
  this->menuBuilder.insertMenuElement(titleElement, Collection::Titles);
}

void MainMenuState::buildScoreTitle() {
  std::string scoreTitle{"Highest score: "};
  scoreTitle += std::to_string(this->game.getHighestGameScore());

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

void MainMenuState::buildMenuOptions() {
  // Set screen details to position menu option section
  const float screenW{static_cast<float>(GetScreenWidth())};
  const float screenH{static_cast<float>(GetScreenHeight())};
  const float spacing{screenH * 0.08f};
  const float fontSize{screenH * 0.06f};  // 6% relative height of the screen
  // 3 because that's how many options are in the menu option list
  const float totalHeight{3 * spacing};
  const float startY{(screenH / 2.0f - totalHeight / 2.0f) + 100};

  const std::vector<std::pair<std::string, GameStateID>> options{
    {"Start", GameStateID::StageOne},
    {"About", GameStateID::AboutMenu},
    {"Quit", GameStateID::QuitGame}
  };

  for (size_t i = 0; i < options.size(); ++i) {
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
      , .position = Vector2{.x = x, .y = y}, .gameState = options[i].second}
      , Collection::optionList);
  }
}

cave_mummies::core::GameStateID MainMenuState::update() {
  return this->menuBuilder.update();
}

void MainMenuState::draw() {
  GameState::drawBackground();
  this->menuBuilder.draw();
}

}  // namespace cave_mummies::states
