// Copyright 2025 Jason Montenegro-Navarro

#include "GameTextures.hpp"
#include "Enemy.hpp"

namespace cave_mummies::entities {

const char* GameTextures::getEnemyTextureFilename(EnemyDifficulty type) {
  switch (type) {
  case EnemyDifficulty::Easy: return GameTextures::enemyAssetPaths[0];
  case EnemyDifficulty::Moderate: return GameTextures::enemyAssetPaths[1];
  case EnemyDifficulty::Hard: return GameTextures::enemyAssetPaths[2];
  default: return "";
  }
}

const char* GameTextures::getPlayerTextureFilename() {
  return GameTextures::defaultPlayerAssetPath;
}

}  // namespace cave_mummies::entities
