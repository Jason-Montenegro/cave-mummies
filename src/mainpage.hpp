// Copyright 2025 Jason Montenegro-Navarro

/**
 * @mainpage Cave Mummies
 *
 * @section game_lore Game Lore
 *
 * Cave Mummies is a **2D arcade/survival** game that creates a fun and
 * enjoyable experience during gameplay, through **unlimited** game time with an
 * infinite game mode that features the main character **Wil**. Wil is a
 * cat-looking creature that appeared one day on his owner's backyard as a baby.
 * Since then, his owner has taken care of him. Wil is stranded in a cave where
 * his owner went missing. He's in the search for him, but encounters himself
 * surrounded by hordes of **mummies** that are desperate to take him down.
 * Before Wil's owner went on searching for treasure in the caves, he left Wil a
 * glock so he could protect himself against any danger. Since it has been a
 * while since Wil has seen his owner, he starts his journey looking for him
 * taking the weapon he was given.
 *
 * Wil does not know when the hordes of mummies will stop, but he knows he has
 * to survive to see his owner again. Wil discovers they only perform **melee
 * attacks**, therefore he must take advantage of his ranged weapon.
 *
 * @section game_specification Game Specification
 *
 * Cave Mummies is a single-player desktop video game which is built on  *C++*
 * and *NASM* (x86_64 Assembly). It utilizes the Raylib library as its graphics
 * and keyboard input library. The game features code implementations in
 * assembly, directed towards Linux systems using *NASM* compiler. The game is
 * made fully with *C++* in its MacOS release.
 *
 * The core mechanic of the game is survival with score progression. The player
 * is intended to survive as long as possible. The player will accumulate a
 * higher score based on elapsed time and the number of mummies defeated. The
 * recorded highest game score will be the one while the program is running.
 * Game scores are not saved or stored when the program is closed.
 *
 * @subsection key_features Key Features
 * - Arena gameplay  
 * - Enemy waves with multiple difficulty levels (speed and resistance)  
 * - Player's weapon has limited loaded ammunition  
 * - Elapsed time clock for game sessions  
 * - Scoring system with high-score tracking  
 * - Minimalistic menu interface  
 *
 * @section how_to_play How to Play
 *
 * @image html doc-assets/gameplay_preview_one.png "Gameplay preview" width=500px
 *
 * At first, the player must navigate through the presented main menu. The
 * player can navigate the menu utilizing `W` / `ARROW_UP` keys for going
 * **upward**, and `S` / `ARROW_DOWN` keys for going **downward**. Or using the
 * mouse scroll wheel upwards and downwards. The player can select an option by
 * pressing the `ENTER` key or using the `MOUSE_LEFT_CLICK` key anywhere on the
 * screen.
 *
 * These navigation instructions apply to all menus presented in the game.  
 * Following these navigation instructions, the player should select the
 * **Start** option, which is the first in the menu. Once the player selects
 * that option, the game will initiate. The game provides the following key
 * control interface for the player to use:
 *
 * - **Movement**  
 * - **Left**: `A` / `ARROW_LEFT`  
 * - **Right**: `D` / `ARROW_RIGHT`  
 * - **Run**: `LEFT_SHIFT`  
 * - **Jump**: `SPACE_BAR` / `W` / `ARROW_UP`  
 * - **Reload**: `R` / `MOUSE_LEFT_CLICK`  
 * - **Shoot**: `MOUSE_LEFT_CLICK`  
 * - **Pause**: `ESC`  
 * - **Music**: `M`  
 *
 * The player must aim and shoot at incoming enemies that will try to follow
 * them. Surely shooting with a weapon which has unlimited bullets as ammunition
 * is **satisfying**, but there is a limit to how many bullets may be loaded
 * into the weapon. The weapon should only yield twelve bullets at a time. After
 * the remaining loaded bullets are used, the player must wait until the weapon
 * is reloaded. Reloading will take two seconds and can only occur once the
 * magazine is empty.
 *
 * This game features compatibility with the Arduino platform enabling movement
 * with the joystick accessory. To enable this option, you must have a Linux
 * based machine and should connect an Arduino device with a joystick accesory
 * to your machine. Movement is just as in many other titles, rolling the
 * joystick horizontally to the sides moves the player in that direction.
 * Rolling the joystick upward makes the player jump. Running can be done by
 * pressing the joystick button down as a toggle for running.
 *
 * @section how_to_win How to Win
 *
 * To win the game is actually a matter of the player's want. The game by itself
 * does not have a finish line. Rather, the game continues indefinitely until
 * the player ultimately fails to avoid the incoming waves of enemies, and dies.
 *
 * To increase the current game score, only two factors can contribute to it:  
 * time elapsed and enemies killed. Elapsed time, as its label implies, refers
 * to the time elapsed since the start of the gameplay. Each second elapsed
 * accounts for one extra point to the current game score. A greater enemy kill
 * count should also grant a better score. For each enemy killed, 10 points are
 * added to the game score. The player starts out with only two jumps available 
 * from the moment they are standing on the floor tile. Killing enemies
 * increases the amount of jumps the player can perform. This jump count can be
 * accumulated, therefore, the player can accumulate as many jumps as enemies
 * killed.

 * The player's goal is to survive as long as possible without being reached by
 * an enemy. The game score may indicate a degree of "winning", in the sense
 * that a higher score may indicate gamer prowess. In both the paused menu, and
 * game over screen, an option to go back to the main menu is available. This
 * option records current game score if its the highest achieved while the game
 * is running.
 */
