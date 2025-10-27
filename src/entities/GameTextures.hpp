// Copyright 2025 Jason Montenegro-Navarro

#ifndef GAME_TEXTURES_HPP
#define GAME_TEXTURES_HPP

#include <string>

#include "raylib.h"

namespace cave_mummies::entities {
  enum class EnemyDifficulty;
}

namespace cave_mummies::entities {

/**
 * @brief Enemy texture loader
 * 
 * Used to load all enemy textures for performance
 */
class GameTextures {
 private:
  /// @brief Default enemy values
  static constexpr const char* const enemyAssetPaths[3]{
    "../assets/textures/entities/moderate_enemy_skin.png",
    "../assets/textures/entities/moderate_enemy_skin.png",
    "../assets/textures/entities/hard_enemy_skin.png"
  };
  /// @brief Player texture
  static constexpr const char* const defaultPlayerAssetPath
    {"../assets/textures/entities/wil_player_skin.png"};
 
 public:
  /**
   * @brief Constructor
   */
  GameTextures() = default;

  /**
   * @brief Destructor
   */
  ~GameTextures() = default;

  /**
   * @brief Getter of enemy texture file name
   * @param type Enemy classification type
   * @return Texture file name
   */
  static const char* getEnemyTextureFilename(EnemyDifficulty type);

  /**
   * @brief Getter of player texture file name
   * @return Texture file name
   */
  static const char* getPlayerTextureFilename();
};


}  //namespace cave_mummies::entities

#endif