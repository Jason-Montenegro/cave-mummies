// Copyright 2025 Jason Montenegro-Navarro

#ifndef MENU_STATE_UTILS_HPP
#define MENU_STATE_UTILS_HPP

#include <string>

#include "raylib.h"

namespace cave_mummies::states::menu {

/// @enum MenuOptionFlag
/// @brief Visual state flags for each menu option.
enum class MenuOptionFlag {
  Highlight1,  ///< Primary highlight
  Highlight2,  ///< Secondary highlight
  None  ///< No effect
};

/// @enum MenuOptionFlag
/// @brief Types of elements that can be displayed in the menu.
enum class MenuOptionTag {
  h1, ///< Main header
  li  ///< List item
};

/**
 * @brief Represents a single option in the main menu.
 * Stores the text, highlight state, type, and color information
 * needed to render and interact with a menu item.
 */
struct MenuOption {
  /// @brief Displayed text
  std::string text;
  /// @brief Highlight state
  MenuOptionFlag flag;
  /// @brief Element type
  MenuOptionTag tag;
  /// @brief Base text color
  Color color;

  /**
   * @brief Constructor
   * @param text The text to display for this menu option
   * @param flag The initial highlight state of the option
   * @param tag The type of menu element
   * @param color The base color of the text
   * @see MenuOptionTag
   * @see MenuOptionFlag
   */
  explicit MenuOption(std::string_view text, MenuOptionFlag flag
    , MenuOptionTag tag, Color color)
    : text(text), flag(flag), tag(tag), color(color) { }
};

/**
 * @brief Returns the outline color based on the highlight flag.
 */
Color pickOutlineColor(MenuOptionFlag flag);

/**
 * @brief Returns the outline thickness based on the element type.
 */
int pickOutlineThickness(MenuOptionTag tag);

}  // namespace namespace cave_mummies::states::menu

#endif  // MENU_STATE_UTILS_HPP
