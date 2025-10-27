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
 * @brief Game entities such as players, enemies, and projectiles.
 *
 * Contains classes representing playable and non-playable objects,
 * including their data and behavior.
 *
 * Key classes:
 * - Enemy
 * - Entity
 * - GameTextures
 * - Player
 * - Projectile
 */

/**
 * @namespace cave_mummies::handlers
 * @brief Modules handling auxiliary game systems.
 *
 * Contains classes responsible for input handling, collisions,
 * and state management.
 *
 * Key classes:
 * - CollisionHandler
 * - GameStateHandler
 * - InputHandler
 * - InputSource
 * - JoystickSource
 * - KeyboardSource
 */

/**
 * @namespace cave_mummies::states
 * @brief Concrete game states inheriting from GameState.
 *
 * Contains the different application states such as menus,
 * gameplay screen, and pause screen, each implementing its own logic.
 *
 * Key classes:
 * - AboutMenuState
 * - GameOverState
 * - MainMenuState
 * - PausedMenuGameState
 * - StageOneState
 */

 /**
 * @namespace cave_mummies::states::menu
 * @brief Utility classes, enummerations and functions.
 *
 * Contains a variety of classes, enummerations and functions for building
 * menu interfaces for game states.
 *
 * Key classes:
 * - MenuBuilder
 * - MenuElement 
 * - MenuElementFlag
 * - MenuElementTag
 * - TextBox
 */

/**
 * @namespace cave_mummies::utils
 * @brief Helper functions and classes for the game engine.
 *
 * Contains general utilities such as logging.
 *
 * Key classes:
 * - Log
 */
