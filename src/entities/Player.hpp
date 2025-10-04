// Copyright 2025 Jason Montenegro-Navarro

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <cstdlib>

#include "Entity.hpp"
#include "Projectile.hpp"

/**
 * @brief Player entity
 */
class Player : public Entity {
 private:
  /// @brief Default player values
  static constexpr uint32_t defaultAmmunitionQuantity{12};
  static constexpr const char *const defaultProjectileAssetPath
    {"assets/textures/projectiles/projectile-sprite.png"};
  static constexpr const char *const defaultPlayerAssetPath
    {"assets/textures/entities/cat.jpeg"};
  /// Alive player flag
  bool isAlive{true};
  /// Type of projectile it uses
  Projectile projectile;
  /// Enemies kill count
  uint64_t killCount{0};
  /// Quantity of projectiles available
  uint64_t ammunitionQuantity{Player::defaultAmmunitionQuantity};
  /// Current reached score
  uint64_t currentScore{0};

 public:
  /**
   * @brief Constructor
   * @param playerAssetPath Texture for player object
   * @param projecileAssetPath Texture for projectile object
   */
  explicit Player(const char *const playerAssetPath =
      Player::defaultPlayerAssetPath
    , const char *const projectileAssetPath =
      Player::defaultProjectileAssetPath)
    : Entity(playerAssetPath), projectile(projectileAssetPath) { }

  /**
   * @brief Updates this player state.
   */
  void update() override;

  /**
   * @brief Checks if this player is alive.
   * @return true if alive, false otherwise
   */
  inline bool isPlayerAlive() const { return this->isAlive; }

  /**
   * @brief Gets the projectile used by the player.
   * @return Reference to the projectile object
   */
  inline Projectile& getProjectile() { return this->projectile; }

  /**
   * @brief Gets the projectile used by the player (const version).
   * @return Const reference to the projectile object
   */
  inline const Projectile& getProjectile() const { return this->projectile; }

  /**
   * @brief Gets the number of enemies killed by the player.
   * @return Kill count
   */
  inline uint64_t getKillCount() const { return this->killCount; }

  /**
   * @brief Gets the current amount of ammunition.
   * @return Ammunition quantity
   */
  inline uint64_t getAmmunitionQuantity() const {
    return this->ammunitionQuantity;
  }

  /**
   * @brief Gets the current score of the player.
   * @return Current score
   */
  inline uint64_t getCurrentScore() const { return this->currentScore; }

  /**
   * @brief Sets whether the player is alive.
   * @param alive true if alive, false otherwise
   */
  inline void setIsAlive(bool alive) { this->isAlive = alive; }

  /**
   * @brief Sets the projectile used by the player.
   * @param p Projectile object to assign
   */
  inline void setProjectile(const Projectile &p) { this->projectile = p; }

  /**
   * @brief Sets the number of enemies killed.
   * @param count New kill count
   * @remark If count is < 0, it is converted to -count.
   */
  inline void setKillCount(int32_t count) {
    this->killCount = (count < 0) ? -count : count;
  }

  /**
   * @brief Sets the current amount of ammunition.
   * @param qty Ammunition quantity
   * @remark If qty is < 0, it is converted to -qty.
   */
  inline void setAmmunitionQuantity(int32_t qty) {
    this->ammunitionQuantity = (qty < 0) ? -qty : qty;
  }

  /**
   * @brief Sets the current score of the player.
   * @param score New score
   */
  inline void setCurrentScore(uint64_t score) { this->currentScore = score; }
};

#endif  // PLAYER_HPP
