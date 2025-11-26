// Copyright 2025 Jason Montenegro-Navarro

#ifndef CAVE_MUMMIES_STATES_STAGE_ONE_STATE_HPP
#define CAVE_MUMMIES_STATES_STAGE_ONE_STATE_HPP

#include <chrono>
#include <memory>
#include <list>
#include <random>
#include "GameState.hpp"

#ifdef __linux__
extern "C" {
  /**
   * @brief Calculates the velocity vector of a projectile toward a target.
   * @param projectileVelocityX Pointer to store the x result of velocity.
   * @param projectileVelocityY Pointer to store the y result of velocity.
   * @param mousePositionX Mouse target x coordinate.
   * @param mousePositionY Mouse target y coordinate.
   * @param startPositionX Projectile start x coordinate.
   * @param startPositionY Projectile start y coordinate.
   * @param bulletSpeed Projectile speed.
   * @note This assembly function assumes arguments are always valid.
   */
  void calculateProjectileVelocity(float* projectileVelocityX
    , float* projectileVelocityY, float mousePositionX, float mousePositionY
    , float startPositionX, float startPositionY, float bulletSpeed);
}
#endif

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
 * @brief Game state for play game stage.
 */
class StageOneState : public cave_mummies::core::GameState {
 private:
  /// @brief Floor tile texture.
  const Texture& floorTile;
  /// @brief Text font for game text.
  Font textFont;
  /// @brief Player character.
  std::unique_ptr<cave_mummies::entities::Player> player;
  /// @brief Current enemy collection.
  std::list<std::shared_ptr<cave_mummies::entities::Enemy>> enemyCollection;
  /// @brief Current projectiles shot.
  std::list<std::shared_ptr<cave_mummies::entities::Projectile>>
    projectileCollection;
  /// @brief Minute counter for enemy spawn pattern.
  double lastSpawnMinute{0.0};
  /// @brief Game paused condition.
  bool isGamePaused{false};
  /// @brief Game over condition.
  bool isPlayerDead{false};
  /// @brief Paused time difference.
  std::chrono::high_resolution_clock::time_point pausedTime{};
  /// @brief Accumulated total paused time.
  std::chrono::high_resolution_clock::duration accumulatedPausedTime{0};
  /// @brief Game start time clock.
  std::chrono::high_resolution_clock::time_point startTime{};
  /// @brief Start reload ammunition timestamp.
  std::chrono::high_resolution_clock::time_point startReloadAmmo{};
  /// @brief Currently reloading condition.
  bool currentlyReloading{false};
  /// @brief Label font size.
  float fontSize{36.0f};
  /// @brief Label text height.
  float textHeight{0.0f};
  /// @brief Random number generator.
  std::mt19937 gen{std::random_device{}()};
  /// @brief Enemy spawn randomizer device.
  std::uniform_real_distribution<float> xDis{0.0f, 1.0f};
  /// @brief Last second value: for game score updating.
  uint64_t lastSecond{0};
  /// @brief Last kill count value: for game score updating.
  uint64_t lastKillCount{0};

 public:
  /**
   * @brief Construct a new Stage One State object.
   * @param game Game controller.
   */
  explicit StageOneState(cave_mummies::core::Game& game);

  /**
   * @brief Destroy the Stage One State object.
   */
  ~StageOneState() override;

  /**
   * @brief Initializes game resources and stage.
   */
  void init() override;

  /**
   * @brief Updates the game entities' state
   * @return If the player dies, it will return GameStateID::QuitGame.
   * If the player pauses the game, GameStateID::PausedMenu.
   * Otherwise, this state ID.
   */
  cave_mummies::core::GameStateID update() override;

  /**
   * @brief Draws the game stage on the screen.
   */
  void draw() override;

 private:
  /**
   * @brief Continues the current game time.
   */
  void continueGameTime();

  /**
   * @brief Checks if the player shot a bullet, and checks if it impacted
   * with an enemy to kill it.
   */
  void checkProjectileShot();

  /**
   * @brief Reloads player ammunition after the reload time has passed.
   */
  void reloadPlayerAmmunition();

  /**
   * @brief Updates all projectiles shot by the player.
   */
  void updateProjectilesShot();

  /**
   * @brief Updates the enemy and projectile collections by checking
   * collisions between them. Every killed enemy grants the player an extra
   * jump.
   */
  void updateKilledEnemies();

  /**
   * @brief Updates the game score using the current player's statistics.
   */
  void updateGameScore();

  /**
   * @brief Destroys all projectiles that went over the screen borders.
   */
  void destroyStrandedProjectiles();

  /**
   * @brief Checks if the player is dead.
   * @return If the player is dead, GameStateID::GameOver, otherwise
   * GameStateID::StageOne.
   */
  cave_mummies::core::GameStateID checkDeadPlayer();

  /**
   * @brief Pauses the current game time.
   */
  void pauseGameTime();

  /**
   * @brief Draws floor tiles on the screen.
   */
  void drawFloor();

  /**
   * @brief Draws score label on the screen.
   */
  void drawScore();

  /**
   * @brief Draws the duration clock on the screen.
   */
  void drawClock();

  /**
   * @brief Draws ammunition label on the screen.
   */
  void drawAmmunitionLabel();

  /**
   * @brief Generates game enemies, depending on the elapsed time and current
   * enemy count on the screen.
   */
  void generateEnemies();

  /**
   * @brief Spawns enemies on the screen.
   */
  void spawnEnemies();

  /**
   * @brief Calculates how many enemies to spawn depending on the minutes
   * elapsed in the current game stage.
   * @param minutesElapsed Minutes elapsed in game stage.
   * @return Enemy count to spawn.
   */
  uint32_t calculateSpawnEnemyCount(uint32_t minutesElapsed);

  /**
   * @brief Calculates the enemy difficulty classification depending on the
   * minutes elapsed in the current game stage.
   * @param minutesElapsed Minutes elapsed in game stage.
   * @return Enemy difficulty classification.
   */
  cave_mummies::entities::EnemyDifficulty calculateEnemyDifficulty(
    uint32_t minutesElapsed);

  /**
   * @brief Randomizes spawn points for spawning enemies and adds them to the
   * enemy collection.
   * @param enemyCount Enemy count to spawn.
   * @param enemyDifficulty Enemy difficulty classification.
   */
  void randomizeEnemySpawn(uint32_t enemyCount
    , cave_mummies::entities::EnemyDifficulty enemyDifficulty);
};

}  // namespace cave_mummies::states

#endif  // CAVE_MUMMIES_STATES_STAGE_ONE_STATE_HPP
