# Zefir_Game
This is a text-based adventure game in C. Players interact with characters, gather clues, solve mysteries, and complete tasks. The game progresses based on player choices, leading to multiple endings. It features dynamic interactions and covers basic programming concepts like conditions, loops, and functions.

# muzaffer-batmaz
CENG209_HW
# Zefir Adventure Game

## Overview

The Zefir Adventure Game is a text-based dungeon exploration game written in C. Players navigate through different rooms, solve puzzles, fight monsters, and manage their inventory to progress. The goal is to overcome all challenges and emerge victorious.

## How the Game Works

### Objectives
- Explore the dungeon and interact with the environment.
- Solve puzzles to progress and unlock new areas.
- Fight monsters and manage resources effectively.
- Collect items to enhance stats and abilities.
- Survive traps and challenges to win the game.

### Key Features

1. *Rooms and Challenges*
   - The game consists of multiple rooms, each presenting unique challenges:
     - *Room 5 (Trap Room)*:
       - Solve logic puzzles and symbol sequences.
       - Survive traps to collect powerful items like "Helmet of Wisdom" and "Shield of Valor".
     - *Room 6 (Creature Card Room)*:
       - Face off against creatures by selecting cards.
       - Solve a riddle to earn the "Diamond Sword".
     - *Room 3 (Treasure Room)*:
       - Collect valuable items from a chest while managing health and inventory.
     - *Room 2 (Battle Room)*:
       - Fight against a selected or random creature to advance.

2. *Core Mechanics*
   - *Commands and Interactions*:
     - *look*: Describes the current room and lists items or monsters present.
     - *pickup <item>*: Collects an item from the room.
     - *drop <item>*: Removes an item from your inventory.
     - *inventory*: Displays current inventory.
   - *Combat*:
     - *attack*: Engages in a battle with the room's monster.
     - *Game Progression*:
       - *save*: Saves the current game state.
       - *load*: Loads a saved game state.

3. *Key Functions in the Code*
   - *Room Management*:
     - initialize_room(Room* room, const char* description, Item items[], int item_count): Initializes a room with a description, items, and their count.
     - look(Room* room): Displays the room's description and available items.
     - cleanup_room(Room* room): Frees allocated memory for room descriptions.
   - *Inventory Management*:
     - pickup(Room* room, Player* player, const char* item_name): Allows the player to pick up an item, adding it to their inventory and boosting their stats.
     - remove_item(Player* player, const char* item_name): Removes an item from the player's inventory.
   - *Game Saving and Loading*:
     - save_game(Player* player, int* completed_traps): Saves the player's progress to a file.
     - load_game(Player* player, int* completed_traps): Loads a saved game state from a file.
   - *Trap Challenges*:
     - room5_traps(Player* player, Room* room, int* completed_traps): Contains three traps:
       - Logic question: "If a farmer has 17 sheep and all but 9 run away, how many are left?"
       - Guess the correct box (A, B, or C).
       - Match a sequence of symbols.
   - *Creature Challenges*:
     - room6_creature_cards(Player* player, Room* room, Creature** selected_creature, int* completed_traps): Selects a card to determine the creature faced.
       - Includes a riddle: "I'm not alive, but I can grow. I don't have lungs, but I need air. What am I?"
   - *Battle Mechanics*:
     - battle(Player* player, Creature* creature): Executes the turn-based battle system.
     - room2_battle(Player* player, Room* room, Creature* selected_creature): Manages battles in Room 2 with selected or random creatures.
   - *Treasure Room*:
     - room3_chest(Player* player, Room* room, Item room3_items[]): Presents the player with items from a chest. Requires health management to take items.

## How to Play

###Setup
-Clone or download the project repository.
-For Linux and macOS:.
Open a terminal and navigate to the directory containing the game2.1.c file:.
```bash
 cd /path/to/your/project/directory
```
 -Compile the code using GCC:
   gcc -o zefir_game game2.1.c
-For Windows:
-Make sure a GCC compiler (such as MinGW) is installed on your system.
-Open the command prompt (cmd) or terminal and navigate to the directory containing game2.1.c:
```bash
cd C:\path\to\your\project\directory
```
-Compile the code using GCC:
```bash
gcc -o zefir_game.exe game2.1.c
```
-This will generate an executable file named zefir_game.exe in the same directory.
-For Linux and macOS:
-After compiling the code, run the game with the following command:
```bash
./zefir_game
```
-For Windows:
-Run the zefir_game.exe file by double-clicking it or by typing the following command in -the terminal:
```bash
zefir_game.exe
```
