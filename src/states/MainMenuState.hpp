// Copyright 2025 Jason Montenegro-Navarro

#ifndef MAIN_MENU_STATE_HPP
#define MAIN_MENU_STATE_HPP

#include <string>
#include <vector>

#include "GameState.hpp"

/**
 * @brief Visual state flags for each menu option.
 */
enum class MenuOptionFlag {
  Highlight1,  ///< Primary highlight
  Highlight2,  ///< Secondary highlight
  None  ///< No effect
};

/**
 * @brief Types of elements that can be displayed in the menu.
 */
enum class MenuOptionTag {
  h1, ///< Main header
  li  ///< List item
};

/**
 * @brief Game state for main menu screen in game.
 */
class MainMenuState : public GameState {
 private:
  /**
   * @brief Represents a single option in the main menu.
   * Stores the text, highlight state, type, and color information
   * needed to render and interact with a menu item.
   */
  struct MenuOption {
    std::string text;  ///< Displayed text
    MenuOptionFlag flag;  ///< Highlight state
    MenuOptionTag tag;  ///< Element type
    Color color;  ///< Base text color

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

  Texture2D background;  ///< Main menu background texture
  Font menuOptionFont;  ///< Font used for menu options
  Sound selectMenuOptionSFX;  ///< Sound played when switching options
  Music backgroundMusic;  ///< Music played in main menu
  MenuOption mainTitle;  ///< Main menu title
  std::vector<MenuOption> menuOptions;  ///< List of interactive menu options

 public:
  /**
   * @brief Constructor. Initializes the main title and assigns the state ID.
   */
  MainMenuState(Game &game)
    : GameState(game)
    , mainTitle("Cave mummies", MenuOptionFlag::Highlight1, MenuOptionTag::h1
      , WHITE) {
    this->stateID = GameStateID::MainMenu;
  }

  /**
   * @brief Destructor. Frees resources loaded by this state.
   */
  ~MainMenuState() override;

  /**
   * @brief Updates main menu logic.
   * @return New game state ID if a transition occurs.
   */
  GameStateID update() override;

  /**
   * @brief Initializes resources (textures, fonts, sounds).
   */
  void init() override;

  /**
   * @brief Renders all menu elements to the screen.
   */
  void draw() override;

 private:
  /**
   * @brief Moves the highlight between menu options based on input.
   */
  void moveMenuOptionHighlight();

  /**
   * @brief Handles selection events (e.g., pressing Enter).
   * @return ID of the next game state if an option is selected.
   */
  GameStateID addMenuOptionEventListener();

  /**
   * @brief Draws the menu background.
   */
  void drawBackground();

  /**
   * @brief Draws the main title text.
   */
  void drawMainTitle();

  /**
   * @brief Draws a single menu option with optional outline.
   * @param option Menu option to draw
   * @param coords Screen coordinates
   * @param fontSize Font size to use
   */
  void drawMenuOption(const MenuOption &option, Vector2 coords, float fontSize);

  /**
   * @brief Draws all interactive menu options.
   */
  void drawMenuOptionSection();

  /**
   * @brief Returns the outline color based on the highlight flag.
   */
  Color pickOutlineColor(MenuOptionFlag flag);

  /**
   * @brief Returns the outline thickness based on the element type.
   */
  int pickOutlineThickness(MenuOptionTag tag);
};

#endif  // MAIN_MENU_STATE_HPP
