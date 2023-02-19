#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "character.h"

using namespace std;

class Combat {
public:
    Combat(Character& player, Character& enemy) : player(player), enemy(enemy) {}

    void fight() {
        // Print the starting status to the console
        cout << "A " << enemy.name << " approaches!" << endl;
        print_status();

        while (player.is_alive() && enemy.is_alive()) {
            // Determine who goes first based on speed
            Character& first = (player.speed >= enemy.speed) ? player : enemy;
            Character& second = (first == player) ? enemy : player;

            // First character attacks second character
            first.attack_target(second);

            // If second character is still alive, they attack first character
            if (second.is_alive()) {
                second.attack_target(first);
            }

            // Print the updated status to the console
            print_status();
        }

        // Print the result of the battle to the console
        if (player.is_alive()) {
            cout << "You win!" << endl;
        } else {
            cout << "You lose." << endl;
        }
    }

private:
    Character& player;
    Character& enemy;

    void print_status() {
        cout << player.name << ": " << player.health << " / " << player.max_health << endl;
        cout << enemy.name << ": " << enemy.health << " / " << enemy.max_health << endl;
        cout << endl;
    }
};

int main() {
    // Create a player character and an enemy character
    Character player("Hero", 100, 10, 5, 8);
    Character enemy("Goblin", 50, 6, 2, 4);

    // Create a new combat instance and fight
    Combat combat(player, enemy);
    combat.fight();

    return 0;
}
