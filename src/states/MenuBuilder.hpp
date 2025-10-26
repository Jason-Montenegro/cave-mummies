// Copyright 2025 Jason Montenegro-Navarro

#ifndef MENU_BUILDER_HPP
#define MENU_BUILDER_HPP

#include <string>
#include <vector>

#include "GameState.hpp"
#include "MenuStateUtils.hpp"

namespace cave_mummies::core {
  class Game;
}

namespace cave_mummies::states::menu {

/**
 * @brief Menu builder for creating state menus
 */
class MenuBuilder {
 private:
  /// @brief Font used for menu options
  Font menuOptionFont{};
  /// @brief Sound played when switching options
  Sound selectMenuOptionSFX{};
  /// @brief Sound played when menu option is submitted with return key
  Sound submitMenuOptionSFX{};
  ///@brief List of titles
  std::vector<menu::MenuElement> menuTitles;
  /// @brief List of interactive menu options
  std::vector<menu::MenuElement> menuOptions;
  /// @brief List of text boxes
  std::vector<menu::TextBox> textBoxes;
  /// @brief Game controller
  cave_mummies::core::Game& game;
  /// @brief Client game state id
  cave_mummies::core::GameStateID clientState;

 public:
  /**
   * @enum Collection
   * @brief Menu collection type
   */
  enum class Collection {
    Titles,
    optionList
  };

  /**
   * @brief Constructor
   * @param game Game controller
   * @param clientState client object state that uses this builder
   */
  explicit MenuBuilder(cave_mummies::core::Game& game
    , cave_mummies::core::GameStateID clientState);

  /**
   * @brief Destructor
   */
  ~MenuBuilder();

  /**
   * @brief Loads font to builder
   * @param filename Font filename
   * @return true if the font was loaded, otherwise false
   */
  bool loadFont(const char* filename);

  /**
   * @brief Loads select menu option sound
   * @param filename Sound filename
   * @return true if the sound was loaded, otherwise false
   */
  bool loadSelectMenuOption(const char* filename);

  /**
   * @brief Loads submit menu option sound
   * @param filename Sound filename
   * @return true if the sound was loaded, otherwise false
   */
  bool loadSubmitMenuOption(const char* filename);

  /**
   * @brief Inserts a menu element into the specified collection
   * @param element The menu element to insert
   * @param collection The collection where the element should be added
   * @return true if the element was inserted successfully, otherwise false
   */
  bool insertMenuElement(menu::MenuElement element, Collection collection);

  /**
   * @brief Inserts a text box into the menu
   * 
   * @param textBox The text box to insert
   * @return true
   */
  bool insertTextBox(menu::TextBox textBox);

  /**
   * @brief Getter of loaded font
   * @return Loaded menu option font
   * @note If no font was loaded previously, an empty font object is returned
   */
  const Font& getLoadedFont() const;

  /**
   * @brief Updates menu logic
   * @return GameStateID::Null if no state change is due, otherwise a unique
   * GameStateID
   */
  cave_mummies::core::GameStateID update();

  /**
   * @brief Renders built menu to the screen
   */
  void draw();

 private:
  /**
   * @brief Moves the highlight between menu options based on input
   */
  void updateOptionListHighlight();

  /**
   * @brief Updates the text boxes based on user behaviour
   */
  void updateTextBoxBehaviour();

  /**
   * @brief Listens to option selection events
   * @return The client state id if no option selected, otherwise a different
   * GameStateID than the client state
   */
  cave_mummies::core::GameStateID listenToOptionListSelection();

  /**
   * @brief Draws all stored titles in this builder titles collection
   */
  void drawTitles();

  /**
   * @brief Draws all stored options in this builder option list collection
   * below the middle of the screen in the center
   */
  void drawOptionList();

  /**
   * @brief Draws all stored text boxes in this builder text boxes collection
   */
  void drawTextBoxes();

  /**
   * @brief Draws a single menu option with optional outline, for menu option
   * list
   * @param option Menu option to draw
   * @param coords Screen coordinates
   * @param fontSize Font size to use
   */
  void drawMenuOption(const menu::MenuElement& option, Vector2 coords
    , float fontSize);
};

}  // namespace cave_mummies::states::menu

#endif  // MENU_BUILDER_HPP
