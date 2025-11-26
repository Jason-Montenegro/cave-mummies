// Copyright 2025 Jason Montenegro-Navarro

#include <string>
#include <utility>
#include "AboutMenuState.hpp"
#include "AboutText.hpp"
#include "Game.hpp"
#include "TextureManager.hpp"

using MenuOptionFlag = cave_mummies::states::menu::MenuElementFlag;
using MenuElementTag = cave_mummies::states::menu::MenuElementTag;
using Collection = cave_mummies::states::menu::MenuBuilder::Collection;
using GameStateID = cave_mummies::core::GameStateID;

namespace cave_mummies::states {

AboutMenuState::AboutMenuState(cave_mummies::core::Game& game)
  : GameState(game, game.getTextureManager().getTexture(
    cave_mummies::core::TextureID::GameBackground))
  , menuBuilder(game, GameStateID::AboutMenu) {
  this->stateID = GameStateID::AboutMenu;
}

void AboutMenuState::init() {
  const char* basePath{GetApplicationDirectory()};
  // Build interface with builder
  this->menuBuilder.loadFont((std::string(basePath)
    + "../assets/fonts/PixelOperatorMono-Bold.ttf").c_str());
  this->buildAboutTextBox();
  this->buildMenuOptions();
}

void AboutMenuState::buildAboutTextBox() {
  const float screenW{static_cast<float>(GetScreenWidth())};
  const float screenH{static_cast<float>(GetScreenHeight())};
  // 0.032f is an arbitrary constant for sizing
  const int32_t fontSize{static_cast<int32_t>(screenH * 0.032f)};

  // Box sizing: floating values represent a margin percentage relative
  // to the side of the screen
  Rectangle boxSizing{ .x = screenW * 0.05f, .y = screenH * 0.1f
    , .width = screenW * 0.9f, .height = screenH * 0.8f};

  menu::TextBox textBox{.rect = boxSizing
    , .text = cave_mummies::states::menu::aboutText
    , .scrollY = 0.0f, .fontSize = fontSize, .focused = true
    , .drawContainer = false, .containerColor = WHITE
    , .containerBorderColor = WHITE};
  this->menuBuilder.insertTextBox(textBox);
}

void AboutMenuState::buildMenuOptions() {
  const std::pair<std::string, GameStateID> returnOption{"Go back"
    , GameStateID::MainMenu};
  // Set screen details to position menu option section
  const float screenW{static_cast<float>(GetScreenWidth())};
  const float screenH{static_cast<float>(GetScreenHeight())};
  const float fontSize{screenH * 0.06f};  // 6% relative height of the screen
  Vector2 textSize{MeasureTextEx(this->menuBuilder.getLoadedFont(),
    returnOption.first.c_str(), fontSize, 1.0f)};
  const float x{screenW / 2.0f - textSize.x / 2.0f};
  const float y{screenH * 0.9f};  // Upper side margin of 90%

  this->menuBuilder.insertMenuElement(menu::MenuElement{
    .text = returnOption.first, .color = WHITE
    , .flag =  MenuOptionFlag::Highlight2
    , .tag = MenuElementTag::li, .fontSize = fontSize
    , .position = Vector2{.x = x, .y = y}, .gameState = returnOption.second}
    , Collection::optionList);
}

cave_mummies::core::GameStateID AboutMenuState::update() {
  return this->menuBuilder.update();
}

void AboutMenuState::draw() {
  GameState::drawBackground();
  this->menuBuilder.draw();
}

}  // namespace cave_mummies::states
