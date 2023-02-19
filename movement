#include <iostream>
#include <vector>

using namespace std;

const int MAP_WIDTH = 10;
const int MAP_HEIGHT = 10;

class Map {
public:
    Map() {
        // Initialize the map with empty spaces
        for (int y = 0; y < MAP_HEIGHT; y++) {
            vector<char> row;
            for (int x = 0; x < MAP_WIDTH; x++) {
                row.push_back(' ');
            }
            map.push_back(row);
        }
    }

    void print() {
        // Print the map to the console
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                cout << map[y][x];
            }
            cout << endl;
        }
    }

    void set(int x, int y, char c) {
        // Set a character at a specific position on the map
        if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
            map[y][x] = c;
        }
    }

    char get(int x, int y) {
        // Get the character at a specific position on the map
        if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
            return map[y][x];
        } else {
            return ' ';
        }
    }

    void move(int x, int y, int dx, int dy) {
        // Move a character on the map
        if (get(x, y) != ' ' && get(x + dx, y + dy) == ' ') {
            set(x + dx, y + dy, get(x, y));
            set(x, y, ' ');
        }
    }

private:
    vector<vector<char>> map;
};

int main() {
    Map map;
    map.set(0, 0, 'A');
    map.print();

    while (true) {
        // Wait for user input
        char input;
        cin >> input;

        // Move the character based on the user input
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
        map.move(0, 0, dx, dy);

        // Print the updated map
        map.print();
    }

    return 0;
}
