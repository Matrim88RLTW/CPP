# CPP
**C++ showcase game**

If you are here, you are either lost, or somehow have been lured here by myself. Either way, welcome!! Please take a look at my ongoing project for furthering my own abilities and education in C++ particularly. 

This is a project at building a top down tactical RPG. I am pushing myself by working heavily and primarily in the tensorflow lib, I have taken a liking to cluster algorithims and their use in unsupervised learning for enemy generation. While supervised learning seems particularly suited for the battle prediction and difficulty scaling. Need to read further into these areas for upcoming updates. 

Current build status: V1.3 : Working my way through initial modules for the build.

Version 1: Butcher build

Version 1.2: Overhaul from initial butcher build

Version 1.2.1: Rework of Character class

Version 1.2.2: Rework of first portion of Enemy class

Version 1.3: Rework of main()

12/29/22 - Added initial portion of bug tracker

12/31/22 - Various bug fixes and error corrections of V1.3

12/30/22 - Started main function of bug tracker

2/18/23 - Added start of character implementation 
#Been awhile, sorry! Spent the last 60 days working on my Python projects as I was actively interviewing utilizing Python. But back at it now.

2/19/23 - Added initial combat, movement and map modules

**Top-Down Tactical RPG Game**

**Overview**

This is a simple top-down tactical RPG game written in C++ using the TensorFlow library. The game features a player-controlled character navigating a grid-based map, fighting enemies and collecting loot along the way. The game is won when the player reaches a certain level, and lost if the player is defeated in combat with an enemy.

**Requirements**

The game requires a C++ compiler and the TensorFlow library to be installed. The game has been tested on Linux and Windows operating systems.

**Installation**

To install the game, follow these steps:

Clone the repository to your local machine
Install the TensorFlow library by following the instructions on the TensorFlow website
Compile the game by running the command g++ -std=c++11 -I /path/to/tensorflow/include -L /path/to/tensorflow/lib -ltensorflow game.cpp engine.cpp map.cpp combat.cpp -o game in the game directory

**Usage** <-- No runnable in current build

To start the game, run the compiled executable game in the game directory. Use the w, a, s, and d keys to move the player character up, left, down, and right, respectively. Fight enemies by moving onto their tile, and collect loot by defeating them. The game is won when the player reaches level 10, and lost if the player is defeated in combat.
