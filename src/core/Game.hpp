// Copyright 2025 Jason Montenegro-Navarro

#ifndef CAVE_MUMMIES_CORE_GAME_HPP
#define CAVE_MUMMIES_CORE_GAME_HPP

#include <memory>
#include "raylib.h"
#include "Application.hpp"

namespace cave_mummies::handlers {
  class GameStateHandler;
  class InputHandler;
  class CollisionHandler;
  enum class InputSourceType;
}

namespace cave_mummies::core {

class TextureManager;

/**
 * @brief Game controller which controls the game loop.
 */
class Game : public cave_mummies::core::Application {
 private:
  /// @brief Default window title.
  static constexpr const char* const defaultWindowTitle{"Cave Mummies"};
  /// @brief Path to the background soundtrack.
  const char* soundtrackPath{"../assets/audio/music/game_soundtrack.mp3"};
  /// @brief Background soundtrack instance.
  Music backgroundSoundtrack{};
  /// @brief Indicates if the music is currently paused.
  bool isMusicPaused{false};
  /// @brief Manages game states and state transitions.
  std::unique_ptr<cave_mummies::handlers::GameStateHandler> gameStateHandler{
    nullptr};
  /// @brief Handles player input.
  std::unique_ptr<cave_mummies::handlers::InputHandler> inputHandler{
    nullptr};
  /// @brief Handles collision detection.
  std::unique_ptr<cave_mummies::handlers::CollisionHandler> collisionHandler{
    nullptr};
  /// @brief Manages texture loading and storage.
  std::unique_ptr<cave_mummies::core::TextureManager> textureManager{nullptr};
  /// @brief Indicates whether the game was successfully loaded.
  bool loadedGame{false};
  /// @brief Highest recorded game score.
  uint64_t currentHighestGameScore{0};
  /// @brief Current player score.
  uint64_t currentGameScore{0};

 public:
  /**
   * @brief Construct a new Game object.
   * @throw std::runtime_error if a game texture image could not be loaded.
   * @throw std::bad_alloc if a handler could not be initialized.
   */
  explicit Game();

  /**
   * @brief Destroy the Game object and releases resources.
   */
  ~Game() override;

  /**
   * @brief Starts and maintains the main game loop.
   * @throw std::bad_alloc if there was an initialization error.
   * @return EXIT_SUCCESS if successful, otherwise EXIT_FAILURE.
   */
  int run() override;

  /**
   * @brief Gets the GameStateHandler reference.
   * @return Reference to the GameStateHandler.
   */
  cave_mummies::handlers::GameStateHandler& getGameStateHandler();

  /**
   * @brief Gets the InputHandler reference.
   * @return Reference to the InputHandler.
   */
  cave_mummies::handlers::InputHandler& getInputHandler();

  /**
   * @brief Gets the CollisionHandler reference.
   * @return Reference to the CollisionHandler.
   */
  cave_mummies::handlers::CollisionHandler& getCollisionHandler();

  /**
   * @brief Gets the TextureManager reference.
   * @return Reference to the TextureManager.
   */
  cave_mummies::core::TextureManager& getTextureManager();

  /**
   * @brief Gets the default stage floor height.
   * @return Floor height value.
   */
  float getGameStageFloorHeight() const;

  /**
   * @brief Sets the current game score.
   * @param score New score value (negative values are converted to positive).
   */
  void setCurrentGameScore(int64_t score);

  /**
   * @brief Sets the highest recorded game score.
   * @param score New score value (negative values are converted to positive).
   */
  void setHighestGameScore(int64_t score);

  /**
   * @brief Gets the current game score.
   * @return Current score value.
   */
  uint64_t getCurrentGameScore() const;

  /**
   * @brief Gets the highest recorded game score.
   * @return Highest score value.
   */
  uint64_t getHighestGameScore() const;

 private:
  /**
   * @brief Initializes all game resources.
   * @throw std::bad_alloc if there was an initialization error.
   */
  void init() override;

  /**
   * @brief Updates game logic and state.
   * @return true if successful, otherwise false to close the program.
   */
  bool update() override;

  /**
   * @brief Updates the soundtrack playback status.
   */
  void updateSoundtrackStatus();

  /**
   * @brief Draws all game objects on screen.
   */
  void draw() override;
};

}  // namespace cave_mummies::core

#endif  // CAVE_MUMMIES_CORE_GAME_HPP
