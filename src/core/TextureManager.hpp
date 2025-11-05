// Copyright 2025 Jason Montenegro-Navarro

#ifndef CAVE_MUMMIES_CORE_TEXTURE_MANAGER_HPP
#define CAVE_MUMMIES_CORE_TEXTURE_MANAGER_HPP

#include <map>
#include "raylib.h"

namespace cave_mummies::entities {
  enum class EnemyDifficulty;
};

namespace cave_mummies::core {

/**
 * @brief Texture identifiers for game texture objects.
 */
enum class TextureID {
  PlayerSprite,
  EnemyEasySprite, 
  EnemyModerateSprite, 
  EnemyHardSprite,
  FloorTile
};

/**
 * @brief Texture manager which holds all loaded assets in the game.
 */
class TextureManager {
  // Public API
 public:
  /**
   * @brief Construct a new Texture Manager object.
   */
  TextureManager();

  /**
   * @brief Destroy the Texture Manager object.
   */
  ~TextureManager();

  /**
   * @brief Gets a texture by its identifier.
   * @param id Texture identifier.
   * @return Constant reference to the requested texture.
   */
  const Texture2D& getTexture(TextureID id);

  /**
   * @brief Gets an enemy texture according to its difficulty level.
   * @param diff Enemy difficulty.
   * @return Constant reference to the corresponding texture.
   */
  const Texture2D& getEnemyTexture(cave_mummies::entities::EnemyDifficulty
    diff);

  // Private data
 private:
  /// @brief Map of loaded textures indexed by TextureID.
  std::map<TextureID, Texture2D> textures;
  /// @brief Base path for texture assets.
  const char* basePath{nullptr};
  /// @brief Paths to enemy texture assets.
  static constexpr const char* const enemyAssetPaths[3]{
    "../assets/textures/entities/moderate_enemy_skin.png",
    "../assets/textures/entities/moderate_enemy_skin.png",
    "../assets/textures/entities/hard_enemy_skin.png"
  };
  /// @brief Path to the default player texture.
  static constexpr const char* const defaultPlayerAssetPath
    {"../assets/textures/entities/wil_player_skin.png"};
  /// @brief Path to the floor tile texture.
  static constexpr const char* const floorTileAssetPath
    {"../assets/textures/scene/floor_tile.png"};

  /**
   * @brief Loads all enemy textures.
   */
  void loadEnemyTextures();

  /**
   * @brief Loads the player texture.
   */
  void loadPlayerTexture();

  /**
   * @brief Loads textures for game stage elements.
   */
  void loadGameStageTextures();
};

}  // namespace cave_mummies::core

#endif  // CAVE_MUMMIES_CORE_TEXTURE_MANAGER_HPP
