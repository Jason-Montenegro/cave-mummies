// Copyright 2025 Jason Montenegro-Navarro

#ifndef MENU_STATE_UTILS_HPP
#define MENU_STATE_UTILS_HPP

#include <string>

#include "raylib.h"
#include "GameState.hpp"

namespace cave_mummies::states::menu {

/**
 * @enum MenuOptionFlag
 * @brief Visual state flags for each menu option.
 */
enum class MenuElementFlag {
  Highlight1,  ///< Primary highlight
  Highlight2,  ///< Secondary highlight
  None  ///< No effect
};

/**
 * @enum MenuOptionTag
 * @brief Types of elements that can be displayed in the menu.
 */
enum class MenuElementTag {
  h1,  ///< Main title
  h2,  ///< Secondary title
  li  ///< List item
};

/**
 * @brief Represents an element in a menu state
 * 
 * Stores the text, highlight state, type, and color information
 * needed to render and interact with a menu item
 */
struct MenuElement {
  /// @brief Displayed text
  std::string text;
  /// @brief Base text color
  Color color;
  /// @brief Highlight state
  MenuElementFlag flag;
  /// @brief Element type
  MenuElementTag tag;
  /// @brief Font size
  float fontSize;
  /// @brief Screen position
  Vector2 position;
  /// @brief Game state to which it corresponds
  cave_mummies::core::GameStateID gameState;
};

/**
 * @brief Represents a text box in a menu state
 */
struct TextBox {
  /// @brief Box element
  Rectangle rect;
  /// @brief Content
  std::string text;
  /// @brief Scroll degree
  float scrollY{0};
  /// @brief Text font size
  int32_t fontSize{20};
  /// @brief Focus flag
  bool focused{false};
  /// @brief Box container condition
  bool drawContainer{false};
  /// @brief Container color
  Color containerColor;
  /// @brief Container border color
  Color containerBorderColor;
};

/**
 * @brief Returns the outline color based on the highlight flag.
 */
Color pickOutlineColor(MenuElementFlag flag);

/**
 * @brief Returns the outline thickness based on the element type.
 */
int pickOutlineThickness(MenuElementTag tag);

}  // namespace namespace cave_mummies::states::menu

#endif  // MENU_STATE_UTILS_HPP
