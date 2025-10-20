// Copyright 2025 Jason Montenegro-Navarro

/**
 * @namespace cave_mummies
 * @brief Root namespace for the "Cave Mummies" game engine.
 *
 * Contains all modules and subcomponents of the game, including
 * core logic, entities, states, handlers, and utilities.
 */

/**
 * @namespace cave_mummies::core
 * @brief Core game logic and main application loop.
 *
 * Contains classes that define the application, game loop,
 * abstract states, and overall engine control.
 *
 * Key classes:
 * - Application
 * - Game
 * - GameState
 */

/**
 * @namespace cave_mummies::entities
 * @brief Game entities such as players, enemies, and NPCs.
 *
 * Contains classes representing playable and non-playable objects,
 * including their data and behavior.
 *
 * Key classes:
 * - Entity
 * - Player
 * - Enemy
 * - Projectile
 */

/**
 * @namespace cave_mummies::handlers
 * @brief Modules handling auxiliary game systems.
 *
 * Contains classes responsible for input handling, collisions,
 * object spawning, and state management.
 *
 * Key classes:
 * - CollisionHandler
 * - InputHandler
 * - GameStateHandler
 * - InputSource (KeyboardSource, JoystickSource)
 */

/**
 * @namespace cave_mummies::states
 * @brief Concrete game states inheriting from GameState.
 *
 * Contains the different application states such as menus,
 * gameplay screen, and pause screen, each implementing its own logic.
 *
 * Key classes:
 * - MainMenuState
 * - AboutMenuState
 * - ScoreboardState
 * - StageOneState
 * - PausedMenuGameState
 * - GameOverState
 */

/**
 * @namespace cave_mummies::utils
 * @brief Helper functions and classes for the game engine.
 *
 * Contains general utilities, logging, and math functions.
 *
 * Key classes:
 * - Log
 * - Math functions (optional: namespace cave_mummies::utils::math)
 */

 /**
  * @namespace cave_mummies::states::menu
  * @brief Helper functions and aggregate structures for building menu states
  * 
  * Contains menu option enum attributes such as MenuOptionFlag and
  * MenuOptionTag.
  * 
  * Key class:
  * - MenuOption
  */