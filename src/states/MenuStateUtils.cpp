// Copyright 2025 Jason Montenegro-Navarro

#include "MenuStateUtils.hpp"

namespace cave_mummies::states::menu {

Color pickOutlineColor(MenuOptionFlag flag) {
  switch (flag) {
  case MenuOptionFlag::Highlight1: return DARKGREEN;
  case MenuOptionFlag::Highlight2: return LIME;
  default: return WHITE;
  }
}

int pickOutlineThickness(MenuOptionTag tag) {
  switch (tag) {
  case MenuOptionTag::h1: return 8;  // Thick outline
  case MenuOptionTag::li: return 3;  // Thin outline
  default: return 1;  // Default outline value
  }
}

}  // namespace cave_mummies::states::menu
