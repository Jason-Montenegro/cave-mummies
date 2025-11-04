// Copyright 2025 Jason Montenegro-Navarro

#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <map>
#include "raylib.h"

namespace cave_mummies::entities {
  enum class EnemyDifficulty;
};

namespace cave_mummies::core {

enum class TextureID {
  PlayerSprite,
  EnemyEasySprite, 
  EnemyModerateSprite, 
  EnemyHardSprite,
  FloorTile
};

/**
 * @brief 
 * 
 */
class TextureManager {
 private:
  /// @brief Entity texture
  std::map<TextureID, Texture2D> textures;
  /// @brief Base path for textures
  const char* basePath{nullptr};
  /// @brief Default enemy values
  static constexpr const char* const enemyAssetPaths[3]{
    "../assets/textures/entities/moderate_enemy_skin.png",
    "../assets/textures/entities/moderate_enemy_skin.png",
    "../assets/textures/entities/hard_enemy_skin.png"
  };
  /// @brief Player texture
  static constexpr const char* const defaultPlayerAssetPath
    {"../assets/textures/entities/wil_player_skin.png"};
  /// @brief Floor tile texture
  static constexpr const char* const floorTileAssetPath
    {"../assets/textures/scene/floor_tile.png"};

 public:
  /**
   * @brief Constructor
   */
  TextureManager();

  /**
   * @brief Destructor
   */
  ~TextureManager();

  /**
   * @brief Getter of game object texture
   * 
   * @param id Texture identifier
   * @return Corresponding texture
   */
  const Texture2D& getTexture(TextureID id);

  /**
   * @brief Getter of enemy object texture
   * 
   * @param diff Enemy difficulty
   * @return Enemy object texture
   */
  const Texture2D& getEnemyTexture(cave_mummies::entities::EnemyDifficulty
    diff);

 private:
  /**
   * @brief Loads all enemy object textures
   */
  void loadEnemyTextures();

  /**
   * @brief Loads the player object texture
   * 
   */
  void loadPlayerTexture();

  /**
   * @brief Loads all game stage object textures
   */
  void loadGameStageTextures();

  /**
   * @brief Getter for default game stage floor height
   */
  float getGameStageFloorHeight() const;
};

}  // namespace cave_mummies::core

#endif  // TEXTURE_MANAGER_HPP