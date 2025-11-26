// Copyright 2025 Jason Montenegro-Navarro

#include <algorithm>
#include "raylib.h"
#include "MenuBuilder.hpp"
#include "CollisionHandler.hpp"
#include "Game.hpp"
#include "GameStateHandler.hpp"
#include "InputHandler.hpp"
#include "StageOneState.hpp"

using MenuOptionFlag = cave_mummies::states::menu::MenuElementFlag;
using MenuElementTag = cave_mummies::states::menu::MenuElementTag;
using GameStateID = cave_mummies::core::GameStateID;

namespace cave_mummies::states::menu {

MenuBuilder::MenuBuilder(cave_mummies::core::Game& game
  , cave_mummies::core::GameStateID clientState)
  : game(game)
  , clientState(clientState) { }

MenuBuilder::~MenuBuilder() {
  // Unload all loaded game assets
  if (this->menuOptionFont.texture.id != 0) {
    UnloadFont(this->menuOptionFont);
  }
  if (this->selectMenuOptionSFX.frameCount > 0) {
    UnloadSound(this->selectMenuOptionSFX);
  }
  if (this->submitMenuOptionSFX.frameCount > 0) {
    UnloadSound(this->submitMenuOptionSFX);
  }
}

bool MenuBuilder::loadFont(const char* filename) {
  if (this->menuOptionFont.texture.id != 0) {
    UnloadFont(this->menuOptionFont);
  }
  this->menuOptionFont = LoadFont(filename);
  return (this->menuOptionFont.texture.id != 0) ? true : false;
}

bool MenuBuilder::loadSelectMenuOption(const char* filename) {
  if (this->selectMenuOptionSFX.frameCount > 0) {
    UnloadSound(this->selectMenuOptionSFX);
  }
  this->selectMenuOptionSFX = LoadSound(filename);
  return (this->selectMenuOptionSFX.frameCount > 0) ? true : false;
}

bool MenuBuilder::loadSubmitMenuOption(const char* filename) {
  if (this->submitMenuOptionSFX.frameCount > 0) {
    UnloadSound(this->submitMenuOptionSFX);
  }
  this->submitMenuOptionSFX = LoadSound(filename);
  return (this->submitMenuOptionSFX.frameCount > 0) ? true : false;
}

const Font& MenuBuilder::getLoadedFont() const {
  return this->menuOptionFont;
}

bool MenuBuilder::insertMenuElement(menu::MenuElement element
  , Collection collection) {
  bool result{false};
  switch (collection) {
  case Collection::Titles:
    this->menuTitles.push_back(element);
    result = true;
    break;
  case Collection::optionList:
    this->menuOptions.push_back(element);
    result = true;
    break;
  default:
    result = false;
  }
  return result;
}

bool MenuBuilder::insertTextBox(menu::TextBox textBox) {
  textBox.scrollY = 0;
  textBoxes.push_back(textBox);
  return true;
}

cave_mummies::core::GameStateID MenuBuilder::update() {
  this->updateOptionListHighlight();
  this->updateTextBoxBehaviour();
  return this->listenToOptionListSelection();
}

void MenuBuilder::updateOptionListHighlight() {
  auto& input{this->game.getInputHandler()};
  const int32_t optionQuantity{static_cast<int32_t>(this->menuOptions.size())};
  // Check what direction should the option selector move
  int32_t direction{0};  // -1 = up, +1 = down
  if (input.isPressed(KEY_W) || input.isPressed(KEY_UP)
    || input.getCurrentMouseWheelMove() > 0) {
    direction = -1;
  } else if (input.isPressed(KEY_S) || input.isPressed(KEY_DOWN)
    || input.getCurrentMouseWheelMove() < 0) {
    direction = 1;
  }
  // Update the option highlighting
  if (direction != 0) {
    for (int32_t index = 0; index < optionQuantity; ++index) {
      if (this->menuOptions[index].flag == MenuOptionFlag::Highlight2) {
        // Changes the highlighting to the next option selected
        this->menuOptions[index].flag = MenuOptionFlag::None;
        // Calculates the next menu option without overflow
        const int32_t nextIndex{std::clamp<int32_t>(index + direction
          , 0, optionQuantity - 1)};
        this->menuOptions[nextIndex].flag = MenuOptionFlag::Highlight2;
        PlaySound(this->selectMenuOptionSFX);
        break;
      }
    }
  }
}

void MenuBuilder::updateTextBoxBehaviour() {
  auto& input{this->game.getInputHandler()};
  // Fetch mouse input
  Rectangle mousePos{.x = static_cast<float>(input.getMouseX())
    , .y = static_cast<float>(input.getMouseY()), .width = 1.0f
    , .height = 1.0f};
  const int32_t wheelMove{input.getCurrentMouseWheelMove()};

  for (menu::TextBox& box : this->textBoxes) {
    if (input.isMouseLeftPressed()) {
      box.focused = this->game.getCollisionHandler().checkCollision(mousePos
        , box.rect);
    }
    // Scroll movement on text box
    if (box.focused && !box.text.empty() && wheelMove != 0) {
      box.scrollY -= wheelMove * 20.0f;  // 20 for default scroll speed

      // Limit content to show on text box
      Vector2 textSize{MeasureTextEx(this->menuOptionFont, box.text.c_str(),
        static_cast<float>(box.fontSize), 1.0f)};
      const float maxScroll{std::max(0.0f
        , textSize.y - box.rect.height + 10.0f)};
      box.scrollY = std::clamp<float>(box.scrollY, 0.0f, maxScroll);
    }
  }
}

cave_mummies::core::GameStateID MenuBuilder::listenToOptionListSelection() {
  auto& input{this->game.getInputHandler()};
  if (input.isPressed(KEY_ENTER) || input.isMouseLeftPressed()) {
    // Perform state change on user behaviour depending on the current
    // menu option selected
    PlaySound(this->submitMenuOptionSFX);
    for (const menu::MenuElement& option : this->menuOptions) {
      if (option.flag == MenuOptionFlag::Highlight2) {
        this->game.getGameStateHandler().removeState(this->clientState);
        this->game.getGameStateHandler().registerState(option.gameState);
        return option.gameState;
      }
    }
  }
  return this->clientState;
}

void MenuBuilder::draw() {
  this->drawTitles();
  this->drawOptionList();
  this->drawTextBoxes();
}

void MenuBuilder::drawTitles() {
  for (const menu::MenuElement& option : this->menuTitles) {
    this->drawMenuOption(option, Vector2{option.position.x
      , option.position.y}, option.fontSize);
  }
}

void MenuBuilder::drawOptionList() {
  for (const menu::MenuElement& option : this->menuOptions) {
    this->drawMenuOption(option, Vector2{option.position.x
      , option.position.y}, option.fontSize);
  }
}

void MenuBuilder::drawMenuOption(const menu::MenuElement& option
  , Vector2 coords, float fontSize) {
  if (!option.text.empty()) {
    Vector2 pos{coords};
    if (option.flag == MenuOptionFlag::Highlight2
      || option.flag == MenuOptionFlag::Highlight1) {
      Color outlineColor{menu::pickOutlineColor(option.flag)};
      const int32_t outlineThickness{menu::pickOutlineThickness(option.tag)};
      // Draw the same text to simulate an outline effect on texts
      for (int32_t x = -outlineThickness; x <= outlineThickness; ++x) {
        for (int32_t y = -outlineThickness; y <= outlineThickness; ++y) {
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

void MenuBuilder::drawTextBoxes() {
  for (const menu::TextBox& box : this->textBoxes) {
    if (box.drawContainer) {
      DrawRectangleRec(box.rect, Fade(box.containerColor, 0.6f));
      DrawRectangleLinesEx(box.rect, 2.0f, box.containerBorderColor);
    }
    // Update box position relative to the current scroll level
    Vector2 textPos{.x = box.rect.x + 10.0f
      , .y = box.rect.y + 10.0f - box.scrollY};
    DrawTextEx(this->menuOptionFont, box.text.c_str(), textPos
      , static_cast<float>(box.fontSize), 1.0f, RAYWHITE);
  }
}

}  // namespace cave_mummies::states::menu
