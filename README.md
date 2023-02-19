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

12/31/22 - Various bug fixes and error corrections of V1.3

12/30/22 - Started main function of bug tracker

12/29/22 - Added initial portion of bug tracker

2/18/23 - Added start of character implementation 
#Been awhile, sorry! Spent the last 60 days working on my Python projects as I was actively interviewing utilizing Python. But back at it now.

2/19/23 - Added initial combat, movement and map modules

**Character Battle**

This program is a simple simulation of a character battle game. It includes a Character class with basic attributes and methods, as well as an Enemy class that inherits from the Character class and includes additional attributes and methods.

**Requirements**

TensorFlow
C++ compiler

**Compiling and Running the Program**

To compile the program, run the following command:
g++ -std=c++11 character_battle.cpp -o character_battle




**Character Class**

The Character class represents a character in the game and has the following attributes:

x and y: the x and y coordinates of the character on the game map
image: a string representing the image file for the character
health: the current health points of the character
attackPower: the attack power of the character
defense: the defense of the character
speed: the speed of the character
level: the current level of the character
inventory: a vector of strings representing the items in the character's inventory
type: a string representing the type of the character (e.g. "enemy")
name: a string representing the name of the character
The Character class has the following methods:

move(int newX, int newY): moves the character to the new x and y coordinates
attack(Character& target): attacks the target character
defend(int damage): reduces the character's health by the specified amount of damage
useItem(std::string itemName): uses the specified item from the character's inventory
levelUp(): increases the character's level by 1
Enemy Class
The Enemy class represents an enemy character in the game and inherits from the Character class. It has the additional attributes:

experiencePoints: the number of experience points that the enemy gives when defeated
loot: a vector of strings representing the items that the enemy drops when defeated
The Enemy class has the following additional methods:

getExperiencePoints(): returns the experience points of the enemy
getLoot(): returns the loot of the enemy

**TensorFlow Model**  

The program also includes a simple TensorFlow model that predicts whether a character will win a battle based on various attributes. The model has two fully connected layers with 32 hidden units and a sigmoid activation function. It is trained using the Adam optimizer and the mean squared error loss function. The model is trained on a small dataset of past battles and then evaluated on the same dataset. The output of the model is a prediction of the probability of the character winning the battle.  
