// Copyright 2025 Jason Montenegro-Navarro

#ifndef STAGE_ONE_STATE_HPP
#define STAGE_ONE_STATE_HPP

#include <memory>
#include <list>

#include "GameState.hpp"
#include "Projectile.hpp"

namespace cave_mummies::core {
  class Game;
}

namespace cave_mummies::entities {
  class Player;
  class Enemy;
}

namespace cave_mummies::states {

/**
 * @brief Game state for level one screen in game.
 */
class StageOneState : public cave_mummies::core::GameState {
 private:
  /// @brief Floor tile component
  Texture2D floorTile;
  /// @brief Text fond  
  Font textFont;
  /// @brief Player character
  std::unique_ptr<cave_mummies::entities::Player> player{nullptr};
  /// @brief Current enemy collection
  std::list<std::shared_ptr<cave_mummies::entities::Enemy>> enemyCollection;
  /// @brief Current projectiles shot
  std::vector<cave_mummies::entities::Projectile> projectiles;
  /// @brief Minute counter for enemy spawn pattern
  double lastSpawnMinute{0.0};
  /// @brief Game paused condition
  bool isGamePaused{false};
  /// @brief Game over condition
  bool isPlayerDead{false};
  /// @brief Paused time difference
  std::chrono::time_point<std::chrono::high_resolution_clock> pausedTime;
  /// @brief Game start time clock
  std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
  /// @brief Label font size
  float fontSize{36.0f};
  /// @brief Label text height
  float textHeight{0.0f};

 public:
  /**
   * @brief Constructor
   */
  explicit StageOneState(cave_mummies::core::Game& game);

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
   * @brief Pauses the current game time.
   */
  void pauseGameTime();

  /**
   * @brief Pauses the current game time.
   */
  void continueGameTime();

  /**
   * @brief Checks if the player shot a bullet, and checks if it impacted.
   */
  void checkPlayerGunshot();

  /**
   * @brief Draws floor tiles on the stage screen.
   */
  void drawFloor();

  /**
   * @brief Draws score label on the stage screen.
   */
  void drawScore();

  /**
   * @brief Draws duration clock on the stage screen.
   */
  void drawClock();

  /**
   * @brief Draws ammunition label on the stage screen.
   */
  void drawAmmunitionLabel();

  /**
   * @brief Generates game enemies, depending on the elapsed time and current
   * enemy count on the stage screen.
   */
  void generateEnemies();

  /**
   * @brief Spawns enemies on the stage screen.
   */
  void spawnEnemies();
};

}  // namespace cave_mummies::states

#endif  // STAGE_ONE_STATE_HPP
