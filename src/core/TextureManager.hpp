// Copyright 2025 Jason Montenegro-Navarro

#ifndef CAVE_MUMMIES_CORE_TEXTURE_MANAGER_HPP
#define CAVE_MUMMIES_CORE_TEXTURE_MANAGER_HPP

#include <string>
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
  FloorTile,
  GameBackground,
  BlankDarkBackground
};

/**
 * @brief Texture manager which holds all loaded assets in the game.
 */
class TextureManager {
 private:
  /// @brief Loaded textures indexed by TextureID.
  std::map<TextureID, Texture2D> textures{{}};
  /// @brief Base path for texture assets.
  const char* basePath{nullptr};
  /// @brief Paths to enemy texture assets relative to this->basePath.
  static constexpr const char* const enemyAssetPaths[3]{
    "../assets/textures/entities/moderate_enemy_skin.png",
    "../assets/textures/entities/moderate_enemy_skin.png",
    "../assets/textures/entities/hard_enemy_skin.png"
  };
  /// @brief Path to the default player texture relative to this->basePath.
  static constexpr const char* const defaultPlayerAssetPath
    {"../assets/textures/entities/wil_player_skin.png"};
  /// @brief Path to the floor tile texture relative to this->basePath.
  static constexpr const char* const floorTileAssetPath
    {"../assets/textures/scene/floor_tile.png"};
  static constexpr const char* const gameBackground
    {"../assets/background/game_bg.png"};
  static constexpr const char* const blankDarkBackground
      {"../assets/background/blank_dark_bg.png"};

 public:
  /**
   * @brief Construct a new Texture Manager object.
   * @throw std::runtime_error if a texture image could not be loaded.
   */
  explicit TextureManager();

  /**
   * @brief Destroy the Texture Manager object. Does not invoke
   * unloadTextures(). Client must invoke unloadTextures() before destructor
   * to avoid memory leakage.
   */
  ~TextureManager() = default;

  /**
   * @brief Unloads all loaded textures.
   */
  void unloadTextures();

  /**
   * @brief Gets a texture by its identifier.
   * @param id Texture identifier.
   * @return Constant reference to the requested loaded texture.
   */
  const Texture2D& getTexture(TextureID id);

  /**
   * @brief Gets an enemy texture according to its difficulty level.
   * @param diff Enemy difficulty.
   * @return Constant reference to the corresponding loaded texture.
   */
  const Texture2D& getEnemyTexture(cave_mummies::entities::EnemyDifficulty
    diff);

 private:
  /**
   * @brief Loads texture and scales for game.
   * @param id Texture ID.
   * @param texturePath Image path for loading texture.
   * @throw std::runtime_error if the texture image could not be loaded.
   */
  void loadTextureAndScale(TextureID id, std::string_view texturePath);

  /**
   * @brief Loads all enemy textures.
   * @throw std::runtime_error if a texture image could not be loaded.
   */
  void loadEnemyTextures();

  /**
   * @brief Loads the player texture.
   * @throw std::runtime_error if the texture image could not be loaded.
   */
  void loadPlayerTexture();

  /**
   * @brief Loads textures for game stage elements.
   * @throw std::runtime_error if a texture image could not be loaded.
   */
  void loadGameStageTextures();
};

}  // namespace cave_mummies::core

#endif  // CAVE_MUMMIES_CORE_TEXTURE_MANAGER_HPP
