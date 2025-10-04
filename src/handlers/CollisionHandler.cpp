// Copyright 2025 (author)

#include <vector>

#include "CollisionHandler.hpp"

bool CollisionHandler::checkCollision(const Entity &a, const Entity &b) const {
  (void)a;  // Remove once method is implemented
  (void)b;  // Remove once method is implemented
  // TODO(any): implement
  return false;
}

CollidingEntityPair CollisionHandler::checkCollisions(const std::vector<Entity>
  &entities) const {
  (void)entities;  // Remove once method is implemented
  // TODO(any): implement
  return CollidingEntityPair();
}

void CollisionHandler::handleCollision(Entity &a, Entity &b) {
  (void)a;  // Remove once method is implemented
  (void)b;  // Remove once method is implemented
  // TODO(any): implement
}
