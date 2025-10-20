// Copyright 2025 Jason Montenegro-Navarro

#include <memory>
#include <string>

#include "Game.hpp"
#include "MainMenuState.hpp"

namespace cave_mummies::states {

MainMenuState::~MainMenuState() {
  if (this->loaded) {
    // Unload all loaded game assets
    UnloadFont(this->menuOptionFont);
    UnloadTexture(this->background);
    UnloadSound(this->submitMenuOptionSFX);
    UnloadSound(this->selectMenuOptionSFX);
    this->loaded = false;
  }
  // Clear all menu options from collection
  this->menuOptions.clear();
}

void MainMenuState::init() {
  if (!this->loaded) {
    // Load all game assets
    const char* basePath{GetApplicationDirectory()};
    this->background = LoadTexture((std::string(basePath)
      + "../assets/background/game_bg.png").c_str());
    this->menuOptionFont = LoadFont((std::string(basePath)
      + "../assets/fonts/PixelOperatorMono-Bold.ttf").c_str());
    this->selectMenuOptionSFX = LoadSound((std::string(basePath)
      + "../assets/audio/sfx/throw1-sfx.wav").c_str());
    this->submitMenuOptionSFX = LoadSound((std::string(basePath)
      + "../assets/audio/sfx/throw5-sfx.wav").c_str());
    // Create all options that are displayed on main menu
    this->menuOptions.emplace_back("Start", menu::MenuOptionFlag::Highlight2
      , menu::MenuOptionTag::li, WHITE);
    this->menuOptions.emplace_back("About", menu::MenuOptionFlag::None
      , menu::MenuOptionTag::li, WHITE);
    this->menuOptions.emplace_back("Scoreboard", menu::MenuOptionFlag::None
      , menu::MenuOptionTag::li, WHITE);
    this->menuOptions.emplace_back("Quit", menu::MenuOptionFlag::None
      , menu::MenuOptionTag::li, WHITE);
    this->loaded = true;
  }
}

cave_mummies::core::GameStateID MainMenuState::update() {
  moveMenuOptionHighlight();
  cave_mummies::core::GameStateID newState{addMenuOptionEventListener()};
  return newState;
}

void MainMenuState::moveMenuOptionHighlight() {
  auto& input{this->game.getInputHandler()};

  const int32_t optionsSize{static_cast<int32_t>(this->menuOptions.size())};
  int32_t direction{0};  // -1 = up, +1 = down
  if (input.isPressed(KEY_W) || input.isPressed(KEY_UP)) {
    direction = -1;
  } else if (input.isPressed(KEY_S) || input.isPressed(KEY_DOWN)) {
    direction = 1;
  }

  if (direction != 0) {
    for (int32_t index{0}; index < optionsSize; ++index) {
      if (menuOptions[index].flag == menu::MenuOptionFlag::Highlight2) {
        menuOptions[index].flag = menu::MenuOptionFlag::None;
        // Calculates the next menu option without overflow
        const int32_t nextIndex{std::clamp<int32_t>(index + direction
          , 0, optionsSize - 1)};
        menuOptions[nextIndex].flag = menu::MenuOptionFlag::Highlight2;

        PlaySound(selectMenuOptionSFX);
        break;
      }
    }
  }
}

cave_mummies::core::GameStateID MainMenuState::addMenuOptionEventListener() {
  if (this->game.getInputHandler().isPressed(KEY_ENTER)) {
    // Change game state event listener for every menu option
    PlaySound(this->submitMenuOptionSFX);
    for (const auto& option : this->menuOptions) {
      if (option.flag == menu::MenuOptionFlag::Highlight2) {
        if (option.text == "Start") {
          this->game.getGameStateHandler().removeState(
            cave_mummies::core::GameStateID::MainMenu);
          this->game.getGameStateHandler().registerState(GameStateID::StageOne
            , std::make_shared<cave_mummies::states::StageOneState>(
              this->game));
          return cave_mummies::core::GameStateID::StageOne;
        }
        if (option.text == "About") {
          this->game.getGameStateHandler().removeState(
            cave_mummies::core::GameStateID::MainMenu);
          this->game.getGameStateHandler().registerState(GameStateID::AboutMenu
            , std::make_shared<cave_mummies::states::AboutMenuState>(
              this->game));
          return cave_mummies::core::GameStateID::AboutMenu;
        }
        if (option.text == "Scoreboard") {
          this->game.getGameStateHandler().removeState(
            cave_mummies::core::GameStateID::MainMenu);
          this->game.getGameStateHandler().registerState(GameStateID::Scoreboard
            , std::make_shared<cave_mummies::states::ScoreboardState>(
              this->game));
          return cave_mummies::core::GameStateID::Scoreboard;
        }
        if (option.text == "Quit") {
          this->game.getGameStateHandler().removeState(
            cave_mummies::core::GameStateID::MainMenu);
          return cave_mummies::core::GameStateID::Null;
        }
      }
    }
  }
  return this->stateID;
}

void MainMenuState::draw() {
  GameState::drawBackground();
  this->drawMainTitle();
  this->drawMenuOptionSection();
}

void MainMenuState::drawMainTitle() {
  // Calculate the location where to place the title
  const float screenW{static_cast<float>(GetScreenWidth())};
  const float screenH{static_cast<float>(GetScreenHeight())};
  const float fontSize{screenH * 0.12f};  // 12% relative height of the screen
  Vector2 textSize{MeasureTextEx(this->menuOptionFont
    , this->mainTitle.text.data(), fontSize, 1.0f)};

  const float x{screenW / 2.0f - textSize.x / 2.0f};
  const float y{screenH * 0.1f};  // Upper side margin of 10%
  this->drawMenuOption(this->mainTitle, {x, y}, fontSize);
}


void MainMenuState::drawMenuOption(const menu::MenuOption& option
  , Vector2 coords, float fontSize) {
  if (!option.text.empty()) {
    Vector2 pos{coords};
    if (option.flag == menu::MenuOptionFlag::Highlight2
        || option.flag == menu::MenuOptionFlag::Highlight1) {
      Color outlineColor{menu::pickOutlineColor(option.flag)};
      const int outlineThickness{menu::pickOutlineThickness(option.tag)};
      // Draw the same text to simulate an outline effect on texts
      for (int x{-outlineThickness}; x <= outlineThickness; ++x) {
        for (int y{-outlineThickness}; y <= outlineThickness; ++y) {
          if (x != 0 || y != 0) {
            DrawTextEx(this->menuOptionFont, option.text.data(),
              {pos.x + x, pos.y + y}, fontSize, 1.0f, outlineColor);
          }
        }
      }
    }
    // Draw text to screen
    DrawTextEx(this->menuOptionFont, option.text.data(), pos, fontSize, 1.0f
      , option.color);
  }
}

void MainMenuState::drawMenuOptionSection() {
  // Set screen details to position menu option section
  const float screenW{static_cast<float>(GetScreenWidth())};
  const float screenH{static_cast<float>(GetScreenHeight())};
  const float spacing{screenH * 0.08f};
  const float fontSize{screenH * 0.06f};
  const float totalHeight{this->menuOptions.size() * spacing};
  const float startY{(screenH / 2.0f - totalHeight / 2.0f) + 100};

  // Draw options in their respective position
  size_t index{0};
  for (const auto &option : this->menuOptions) {
    const float y{startY + index * spacing};
    ++index;
    Vector2 textSize{MeasureTextEx(this->menuOptionFont, option.text.data()
      , fontSize, 1.0f)};
    const float x{screenW / 2.0f - textSize.x / 2.0f};

    drawMenuOption(option, {x, y}, fontSize);
  }
}

}  // namespace cave_mummies::states
