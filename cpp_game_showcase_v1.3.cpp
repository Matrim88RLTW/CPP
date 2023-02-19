#include <iostream>
#include <string>
#include <vector>

#include "tensorflow/cc/ops/standard_ops.h"
#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/core/public/session.h"
#include "tensorflow/core/util/command_line_flags.h"

#include "engine.h"
#include "map.h"
#include "combat.h"

using namespace tensorflow;
using namespace tensorflow::ops;
using namespace std;

int main() {
    // Initialize the game engine
    Engine engine;
    engine.initialize();

    // Initialize the game map
    Map map;
    map.set(engine.getPlayer().x, engine.getPlayer().y, engine.getPlayer().image);
    map.print();

    // Cache the player object to avoid repeated calls to engine.getPlayer()
    Character& player = engine.getPlayer();

    while (true) {
        // Wait for user input
        char input;
        cin >> input;

        // Move the character on the map based on user input
        int dx = 0, dy = 0;
        if (input == 'w') {
            dy = -1;
        } else if (input == 'a') {
            dx = -1;
        } else if (input == 's') {
            dy = 1;
        } else if (input == 'd') {
            dx = 1;
        }
        int new_x = player.x + dx;
        int new_y = player.y + dy;

        if (engine.checkValidMove(new_x, new_y)) {
            map.set(player.x, player.y, ' ');
            engine.movePlayer(dx, dy);
            map.set(player.x, player.y, player.image);
        }

        // Check for combat with enemy
        if (map.get(player.x, player.y) == 'E') {
            Enemy enemy = engine.getEnemy();
            bool playerWins = Combat::fight(player, enemy);
            if (playerWins) {
                // Player wins, remove enemy from map and give loot
                map.set(player.x, player.y, ' ');
                player.levelUp();
                for (string item : enemy.getLoot()) {
                    player.addItemToInventory(item);
                }
            } else {
                // Player loses, end game
                cout << "You have been defeated by the enemy. Game over." << endl;
                return 0;
            }
        }

        // Check if player has won the game
        if (player.getLevel() >= 10) {
            cout << "Congratulations! You have won the game." << endl;
            return 0;
        }
    }

    // Print the updated map
    map.print();

    return 0;
}
