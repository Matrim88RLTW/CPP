#include <iostream>
#include <vector>
#include <string>

// Define the dimensions of the map
const int MAP_WIDTH = 10;
const int MAP_HEIGHT = 10;

// Define the tile types
const char TILE_GRASS = '.';
const char TILE_WALL = '#';
const char TILE_WATER = '~';

class Map {
public:
    // Initialize the map with a default tile type
    Map() : tiles(MAP_WIDTH, std::vector<char>(MAP_HEIGHT, TILE_GRASS)) {}

    // Set a tile at a specific location
    void set(int x, int y, char tile) {
        tiles[x][y] = tile;
    }

    // Get the tile at a specific location
    char get(int x, int y) const {
        return tiles[x][y];
    }

    // Print the map to the console
    void print() const {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                std::cout << get(x, y) << " ";
            }
            std::cout << std::endl;
        }
    }

private:
    std::vector<std::vector<char>> tiles;
};

int main() {
    // Initialize the game map
    Map map;

    // Set some tiles to create a simple map
    map.set(1, 1, TILE_WALL);
    map.set(1, 2, TILE_WALL);
    map.set(1, 3, TILE_WALL);
    map.set(2, 3, TILE_WALL);
    map.set(3, 3, TILE_WALL);
    map.set(4, 3, TILE_WALL);
    map.set(5, 3, TILE_WALL);
    map.set(5, 4, TILE_WALL);
    map.set(5, 5, TILE_WALL);
    map.set(5, 6, TILE_WALL);
    map.set(5, 7, TILE_WALL);
    map.set(5, 8, TILE_WALL);
    map.set(4, 8, TILE_WALL);
    map.set(3, 8, TILE_WALL);
    map.set(2, 8, TILE_WALL);
    map.set(1, 8, TILE_WALL);
    map.set(1, 7, TILE_WALL);
    map.set(1, 6, TILE_WALL);
    map.set(1, 5, TILE_WALL);
    map.set(1, 4, TILE_WALL);
    map.set(4, 4, TILE_WATER);

    // Print the map
    map.print();

    return 0;
}
