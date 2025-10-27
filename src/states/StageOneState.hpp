// Copyright 2025 Jason Montenegro-Navarro

#ifndef STAGE_ONE_STATE_HPP
#define STAGE_ONE_STATE_HPP

#include <chrono>
#include <memory>
#include <list>
#include <random>

#include "GameState.hpp"

namespace cave_mummies::core {
  class Game;
}

namespace cave_mummies::entities {
  class Player;
  class Enemy;
  struct Projectile;
}

namespace cave_mummies::entities {
  enum class EnemyDifficulty;
}

namespace cave_mummies::states {

/**
 * @brief Game state for level one screen in game.
 */
class StageOneState : public cave_mummies::core::GameState {
 private:
  /// @brief Floor tile component
  Texture2D floorTile;
  /// @brief Text font
  Font textFont;
  /// @brief Player character
  std::unique_ptr<cave_mummies::entities::Player> player;
  /// @brief Current enemy collection
  std::list<std::shared_ptr<cave_mummies::entities::Enemy>> enemyCollection;
  /// @brief Current projectiles shot
  std::list<std::shared_ptr<cave_mummies::entities::Projectile>>
    projectileCollection;
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
  /// @brief Start reload ammunition timestamp
  std::chrono::time_point<std::chrono::high_resolution_clock> startReloadAmmo;
  /// @brief Currently reloading condition
  bool currentlyReloading{false};
  /// @brief Label font size
  float fontSize{36.0f};
  /// @brief Label text height
  float textHeight{0.0f};
  /// @brief Random number generator
  std::mt19937 gen{std::random_device{}()};
  /// @brief Enemy spawn randomizer device
  std::uniform_real_distribution<float> xDis{0.0f, 1.0f};
  /// @brief Last second value: for game score updating
  uint64_t lastSecond{0};
  /// @brief Last kill count value: for game score updating
  uint64_t lastKillCount{0};

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
   * @brief Initializes game resources (textures and entities)
   */
  void init() override;

  /**
   * @brief Updates the game objects' state
   */
  cave_mummies::core::GameStateID update() override;

  /**
   * @brief Draws the game objects on the screen
   */
  void draw() override;

 private:
  /**
   * @brief Pauses the current game time
   */
  void pauseGameTime();

  /**
   * @brief Continues the current game time
   */
  void continueGameTime();

  /**
   * @brief Checks if the player shot a bullet, and checks if it impacted
   * with an enemy to kill it
   */
  void checkProjectileShot();

  /**
   * @brief Draws floor tiles on the screen
   */
  void drawFloor();

  /**
   * @brief Draws score label on the screen
   */
  void drawScore();

  /**
   * @brief Draws the duration clock on the screen
   */
  void drawClock();

  /**
   * @brief Draws ammunition label on the screen
   */
  void drawAmmunitionLabel();

  /**
   * @brief Generates game enemies, depending on the elapsed time and current
   * enemy count on the screen
   */
  void generateEnemies();

  /**
   * @brief Spawns enemies on the screen
   */
  void spawnEnemies();

  /**
   * @brief Reloads player ammunition after the reload time has passed
   */
  void reloadPlayerAmmunition();

  /**
   * @brief Updates all projectiles shot by the player
   */
  void updateProjectilesShot();

  /**
   * @brief Updates the enemy and projectile collections by checking
   * collisions between them. Every killed enemy grants the player an extra
   * jump
   */
  void updateKilledEnemies();

  /**
   * @brief Updates the game score using the current player's statistics
   */
  void updateGameScore();

  /**
   * @brief Checks if the player is dead, and if so, it ends the current
   * game session
   */
  cave_mummies::core::GameStateID checkDeadPlayer();

  /**
   * @brief Calculates how many enemies to spawn depending on the minutes
   * elapsed in the current game session
   * @param minutesElapsed Minutes elapsed in game session
   * @return Enemy count to spawn
   */
  uint32_t calculateSpawnEnemyCount(uint32_t minutesElapsed);

  /**
   * @brief Calculates the enemy difficulty classification depending on the
   * minutes elapsed in the current game session
   * @param minutesElapsed Minutes elapsed in game session
   * @return Enemy difficulty classification
   */
  cave_mummies::entities::EnemyDifficulty calculateEnemyDifficulty(
    uint32_t minutesElapsed);

  /**
   * @brief Randomizes spawn points for spawning enemies and adds them to the
   * enemy collection
   * @param enemyCount Enemy count to spawn
   * @param enemyDifficulty Enemy difficulty classification
   */
  void randomizeEnemySpawn(uint32_t enemyCount
    , cave_mummies::entities::EnemyDifficulty enemyDifficulty);
};

}  // namespace cave_mummies::states

#endif  // STAGE_ONE_STATE_HPP
