// Copyright 2025 Jason Montenegro-Navarro

#include <string>
#include <vector>
#include "TextureManager.hpp"
#include "Enemy.hpp"

namespace cave_mummies::core {

TextureManager::TextureManager() {
  this->basePath = GetApplicationDirectory();
  this->loadPlayerTexture();
  this->loadEnemyTextures();
  this->loadGameStageTextures();
}

TextureManager::~TextureManager() {
  for (auto texture : this->textures) {
    if (texture.second.id != 0) {
      UnloadTexture(texture.second);
    }
  }
}

float TextureManager::getGameStageFloorHeight() const {
  return (GetScreenHeight() / 2) + GetScreenHeight() * 0.3f;
}

void TextureManager::loadPlayerTexture() {
  if (this->textures[TextureID::PlayerSprite].id != 0) {
    UnloadTexture(this->textures[TextureID::PlayerSprite]);
  }
  std::string filename{TextureManager::defaultPlayerAssetPath};
  Image img{LoadImage((this->basePath + filename).c_str())};
  if (!img.data) {
    throw std::runtime_error("Failed to load player texture: "
      + std::string(filename));
  }
  const int32_t newWidth{static_cast<int32_t>(img.width * 0.1f)};
  const int32_t newHeight{static_cast<int32_t>(img.height * 0.1f)};
  ImageResize(&img, newWidth, newHeight);
  this->textures[TextureID::PlayerSprite] = LoadTextureFromImage(img);
  UnloadImage(img);
}

void TextureManager::loadEnemyTextures() {
  std::vector<TextureID> enemyTextures = {TextureID::EnemyEasySprite
    , TextureID::EnemyModerateSprite, TextureID::EnemyHardSprite};
  size_t enemyTextureIndex{0};

  for (TextureID enemyID : enemyTextures) {
    if (this->textures[enemyID].id != 0) {
      UnloadTexture(this->textures[enemyID]);
    }
    std::string filename{TextureManager::enemyAssetPaths[enemyTextureIndex++]};
    Image img{LoadImage((basePath + filename).c_str())};
    if (!img.data) {
      throw std::runtime_error("Failed to load enemy texture: "
        + std::string(filename));
    }
    const int32_t newWidth{static_cast<int32_t>(img.width * 0.1f)};
    const int32_t newHeight{static_cast<int32_t>(img.height * 0.1f)};
    ImageResize(&img, newWidth, newHeight);
    this->textures[enemyID] = LoadTextureFromImage(img);
    UnloadImage(img);
  }
}

void TextureManager::loadGameStageTextures() {
  this->textures[TextureID::FloorTile] = LoadTexture((
    std::string(this->basePath) + this->floorTileAssetPath).c_str());
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
    return this->textures[TextureID::EnemyEasySprite];
  }
}

}  // namespace cave_mummies::core
