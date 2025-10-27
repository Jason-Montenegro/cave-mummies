// Copyright 2025 Jason Montenegro-Navarro

/**
 * @mainpage Cave Mummies
 * 
 * @section Game-Lore Game Lore
 * Cave Mummies is a **2D arcade / survival** game that creates a fun and
 * enjoyable experience during gameplay, through **unlimited** gameplay with an
 * infinite game mode that features the main character **Wil**.
 * Wil is an anthropomorphic creature that appeared one day on his owner's
 * backyard as a baby. Since then, his owner has taken care of him.
 * Wil is stranded in a cave where his owner went missing. He's in the search 
 * for him, but encounters himself surrounded by hordes of **mummies** that are
 * desperate to take him down.
 * Before Wil's owner went on searching for treasure in the caves, he left Wil a
 * gun so he could protect himself against any creature. Since it has been a
 * while since Wil has seen his owner, he starts his journey looking for him
 * taking the gun he was given.
 * 
 * Wil does not know when the hordes of mummies will stop, but he knows he has
 * to survive to see his owner again. Wil discovers they only perform
 * melee attacks, therefore he must take advantage of his ranged weapon.
 * 
 * @section Game-Specification Game Specification
 * Cave Mummies is a single-player desktop video game which is built on C++ and
 * NASM (x86_64 Assembly). It utilizes Raylib as its base graphics library, and
 * relies on it for all graphic and input actions in the game. The game features
 * NASM in its Linux-based release. Therefore, performance may increase in 
 * Linux-based machines.
 * 
 * The core mechanic of the game is time-based survival with score progression.
 * The player is intended to survive as long as possible. Based on elapsed time
 * and the number of mummies defeated by the player, they will be rewarded with
 * a greater score. Scores have a specific scope: they are only the highest on
 * the current game application opened. Therefore, if the player wished to save
 * their progress, they should take a picture of the highest score recorded.
 * 
 * @subsection Key-Features Key Features
 * - Static arena gameplay
 * - Enemy waves with multiple difficulty levels (speed and resistance)
 * - Player's weapon with limited ammunition
 * - Elapsed time clock for game sessions
 * - Scoring system with high-score tracking
 * - Menu interface, with about page and highest score label
 * 
 * @section How-to-Play How to Play
 * 
 * The game provides the following control interface for the player to use:
 * - Movement: A / W / D or LEFT / UP / RIGHT arrow keys
 * - Run: Left Shift key
 * - Jump: Space key
 * - Reload: R key or mouse LEFT click
 * - Shoot: Mouse LEFT click
 * - Pause: Esc key
 * - Music: M key
 */