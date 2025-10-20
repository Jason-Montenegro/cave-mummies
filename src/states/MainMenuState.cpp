// Copyright 2025 Jason Montenegro-Navarro

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
    this->background = LoadTexture("assets/background/game_bg.png");
    this->menuOptionFont = LoadFont("assets/fonts/PixelOperatorMono-Bold.ttf");
    this->selectMenuOptionSFX = LoadSound("assets/audio/sfx/throw1-sfx.wav");
    this->submitMenuOptionSFX = LoadSound("assets/audio/sfx/throw5-sfx.wav");
    // Create all options that are displayed on main menu
    this->menuOptions.emplace_back("Start", MenuOptionFlag::Highlight2
      , MenuOptionTag::li, WHITE);
    this->menuOptions.emplace_back("About", MenuOptionFlag::None
      , MenuOptionTag::li, WHITE);
    this->menuOptions.emplace_back("Scoreboard", MenuOptionFlag::None
      , MenuOptionTag::li, WHITE);
    this->menuOptions.emplace_back("Quit", MenuOptionFlag::None
      , MenuOptionTag::li, WHITE);
    this->loaded = true;
  }
}

cave_mummies::core::GameStateID MainMenuState::update() {
  moveMenuOptionHighlight();
  cave_mummies::core::GameStateID newState{addMenuOptionEventListener()};
  return newState;
}

void MainMenuState::moveMenuOptionHighlight() {
  const size_t optionsSize{this->menuOptions.size()};
  if (this->game.getInputHandler().isPressed(KEY_W)
      || this->game.getInputHandler().isPressed(KEY_UP)) {
    // Move option selector up
    for (size_t index{0}; index < optionsSize; ++index) {
      if (this->menuOptions[index].flag == MenuOptionFlag::Highlight2
          && index > 0) {
        this->menuOptions[index].flag = MenuOptionFlag::None;
        this->menuOptions[index - 1].flag = MenuOptionFlag::Highlight2;
        PlaySound(this->selectMenuOptionSFX);
        break;
      }
    }
  }
  if (this->game.getInputHandler().isPressed(KEY_S)
    || this->game.getInputHandler().isPressed(KEY_DOWN)) {
    // Move option selector down
    for (size_t index{0}; index < optionsSize; ++index) {
      if (this->menuOptions[index].flag == MenuOptionFlag::Highlight2
          && index + 1 < optionsSize) {
        this->menuOptions[index].flag = MenuOptionFlag::None;
        this->menuOptions[index + 1].flag = MenuOptionFlag::Highlight2;
        PlaySound(this->selectMenuOptionSFX);
        break;
      }
    }
  }
}

cave_mummies::core::GameStateID MainMenuState::addMenuOptionEventListener() {
  if (this->game.getInputHandler().isPressed(KEY_ENTER)) {
    // Change game state event listener for every menu option
    PlaySound(this->submitMenuOptionSFX);
    for (const auto &option : this->menuOptions) {
      if (option.flag == MenuOptionFlag::Highlight2) {
        if (option.text == "Start")
          return cave_mummies::core::GameStateID::StageOne;
        if (option.text == "About")
          return cave_mummies::core::GameStateID::AboutMenu;
        if (option.text == "Scoreboard")
          return cave_mummies::core::GameStateID::Scoreboard;
        if (option.text == "Quit")
          return cave_mummies::core::GameStateID::Null;
      }
    }
  }
  return this->stateID;
}

void MainMenuState::draw() {
  drawBackground();
  drawMainTitle();
  drawMenuOptionSection();
}

void MainMenuState::drawBackground() {
  ClearBackground(BLACK);
  // Calculate the math for extending background to whole game screen
  Rectangle sourceRec{0.0f, 0.0f, static_cast<float>(this->background.width)
    , static_cast<float>(this->background.height)};
  Rectangle destRec{0.0f, 0.0f, static_cast<float>(GetScreenWidth())
    , static_cast<float>(GetScreenHeight())};
  Vector2 origin{0.0f, 0.0f};
  DrawTexturePro(this->background, sourceRec, destRec, origin, 0.0f, WHITE);
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
  drawMenuOption(this->mainTitle, {x, y}, fontSize);
}


void MainMenuState::drawMenuOption(const MenuOption &option, Vector2 coords
  , float fontSize) {
  if (!option.text.empty()) {
    Vector2 pos{coords};
    if (option.flag == MenuOptionFlag::Highlight2
        || option.flag == MenuOptionFlag::Highlight1) {
      Color outlineColor{this->pickOutlineColor(option.flag)};
      const int outlineThickness{this->pickOutlineThickness(option.tag)};
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

Color MainMenuState::pickOutlineColor(MenuOptionFlag flag) {
  switch (flag) {
  case MenuOptionFlag::Highlight1: return DARKGREEN;
  case MenuOptionFlag::Highlight2: return LIME;
  default: return WHITE;
  }
}

int MainMenuState::pickOutlineThickness(MenuOptionTag tag) {
  switch (tag) {
  case MenuOptionTag::h1: return 8;  // Thick outline
  case MenuOptionTag::li: return 3;  // Thin outline
  default: return 1;  // Default outline value
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
