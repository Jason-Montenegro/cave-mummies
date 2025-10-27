// Copyright 2025 Jason Montenegro-Navarro

#include "MenuStateUtils.hpp"

namespace cave_mummies::states::menu {

Color pickOutlineColor(MenuElementFlag flag) {
  switch (flag) {
  case MenuElementFlag::Highlight1: return DARKGREEN;
  case MenuElementFlag::Highlight2: return LIME;
  default: return WHITE;
  }
}

int pickOutlineThickness(MenuElementTag tag) {
  switch (tag) {
  case MenuElementTag::h1: return 8;  // Thick outline
  case MenuElementTag::h2: return 5;  // Medium-thickness outline
  case MenuElementTag::li: return 3;  // Thin outline
  default: return 1;  // Default outline value
  }
}

}  // namespace cave_mummies::states::menu
