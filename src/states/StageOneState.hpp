// Copyright 2025 Jason Montenegro-Navarro

#ifndef STAGE_ONE_STATE_HPP
#define STAGE_ONE_STATE_HPP

#include <memory>
#include <list>

#include "GameState.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

namespace cave_mummies::states {

/**
 * @brief Game state for level one screen in game.
 */
class StageOneState : public cave_mummies::core::GameState {
 private:
  /// @brief Stage one background
  Texture2D stageBackground;
  /// @brief Floor tile component
  Texture2D floorTile;
  /// @brief Text fond  
  Font textFont;
  /// @brief Player character
  std::unique_ptr<cave_mummies::entities::Player> player{nullptr};
  /// @brief Current enemy collection
  std::list<std::shared_ptr<cave_mummies::entities::Enemy>> enemyCollection;

 public:
  /**
   * @brief Constructor
   */
  StageOneState(cave_mummies::core::Game& game)
    : GameState(game) {
    this->stateID = cave_mummies::core::GameStateID::StageOne;
  }

  /**
   * @brief Destructor
   */
  ~StageOneState() override;

  /**
   * @brief Initializes resources (textures and entities).
   */
  void init() override;

  /**
   * @brief Updates the level one state objects.
   */
  cave_mummies::core::GameStateID update() override;

  /**
   * @brief Draws the level one objects to screen.
   */
  void draw() override;

 private:
  /**
   * @brief Draws the background to the stage screen.
   */
  void drawBackground();

  /**
   * @brief Draws floor tiles on the stage screen.
   */
  void drawFloor();
};

}  // namespace cave_mummies::states

#endif  // STAGE_ONE_STATE_HPP
