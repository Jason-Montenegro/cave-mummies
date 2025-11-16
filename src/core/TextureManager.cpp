// Copyright 2025 Jason Montenegro-Navarro

#include <stdexcept>
#include <string>
#include <vector>
#include "TextureManager.hpp"
#include "Enemy.hpp"

namespace cave_mummies::core {

TextureManager::TextureManager()
  : basePath(GetApplicationDirectory()) {
  if (!basePath) {
    basePath = "";
  } else {
    this->loadPlayerTexture();
    this->loadEnemyTextures();
    this->loadGameStageTextures();
  }
}

void TextureManager::unloadTextures() {
  for (auto& [id, texture] : this->textures) {
    if (texture.id != 0) {
      UnloadTexture(texture);
    }
  }
}

void TextureManager::loadPlayerTexture() {
  this->loadTextureAndScale(TextureID::PlayerSprite
    , TextureManager::defaultPlayerAssetPath);
}

void TextureManager::loadEnemyTextures() {
  std::vector<TextureID> enemyTextures{TextureID::EnemyEasySprite
    , TextureID::EnemyModerateSprite, TextureID::EnemyHardSprite};

  size_t enemyTextureIndex{0};
  for (TextureID enemyID : enemyTextures) {
    this->loadTextureAndScale(enemyID
      , TextureManager::enemyAssetPaths[enemyTextureIndex++]);
  }
}

void TextureManager::loadTextureAndScale(TextureID id
  , std::string_view texturePath) {
  std::string filename{this->basePath};
  filename += texturePath;
  Image img{LoadImage(filename.c_str())};
  if (!img.data) {
    throw std::runtime_error("Failed to load texture: " + filename);
  }
  const int32_t newWidth{static_cast<int32_t>(img.width * 0.1f)};
  const int32_t newHeight{static_cast<int32_t>(img.height * 0.1f)};
  ImageResize(&img, newWidth, newHeight);
  this->textures[id] = LoadTextureFromImage(img);
  UnloadImage(img);
}

void TextureManager::loadGameStageTextures() {
  this->textures[TextureID::GameBackground] = LoadTexture(
    (this->basePath + std::string(this->gameBackground)).c_str());
  this->textures[TextureID::BlankDarkBackground] = LoadTexture(
    (this->basePath + std::string(this->blankDarkBackground)).c_str());
  this->textures[TextureID::FloorTile] = LoadTexture(
    (this->basePath + std::string(this->floorTileAssetPath)).c_str());
}

const Texture2D& TextureManager::getTexture(TextureID id) {
  return this->textures[id];
}

const Texture2D& TextureManager::getEnemyTexture(
  cave_mummies::entities::EnemyDifficulty diff) {
  switch (diff) {
  case cave_mummies::entities::EnemyDifficulty::Easy:
    return this->textures[TextureID::EnemyEasySprite];
  case cave_mummies::entities::EnemyDifficulty::Moderate:
    return this->textures[TextureID::EnemyModerateSprite];
  case cave_mummies::entities::EnemyDifficulty::Hard:
    return this->textures[TextureID::EnemyHardSprite];
  default:
    // Easy difficulty enemy is arbitrarily the default
    return this->textures[TextureID::EnemyEasySprite];
  }
}

}  // namespace cave_mummies::core
