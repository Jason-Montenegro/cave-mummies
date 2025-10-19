// Copyright 2025 Jason Montenegro-Navarro

#include <vector>

#include "CollisionHandler.hpp"

namespace cave_mummies::handlers {

bool CollisionHandler::checkCollision(const cave_mummies::entities::Entity& a
  , const cave_mummies::entities::Entity& b) const {
  (void)a;  // Remove once method is implemented
  (void)b;  // Remove once method is implemented
  // TODO(any): implement
  return false;
}

CollidingEntityPair CollisionHandler::checkCollisions(
  const std::vector<cave_mummies::entities::Entity>& entities) const {
  (void)entities;  // Remove once method is implemented
  // TODO(any): implement
  return CollidingEntityPair();
}

void CollisionHandler::handleCollision(cave_mummies::entities::Entity& a
  , cave_mummies::entities::Entity& b) {
  (void)a;  // Remove once method is implemented
  (void)b;  // Remove once method is implemented
  // TODO(any): implement
}

}  // cave_mummies::handlers
