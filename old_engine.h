#include "engine.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

Engine::Engine() : player_(0, 0, '@') {}

void Engine::initialize() {
    generateMap();
    generateEnemies();
}

void Engine::movePlayer(int dx, int dy) {
    player_.x += dx;
    player_.y += dy;
}

bool Engine::checkValidMove(int x, int y) {
    if (x < 0 || y < 0 || x >= mapWidth_ || y >= mapHeight_) {
        return false;
    }
    if (gameMap_[y][x] != '.') {
        return false;
    }
    return true;
}

Character& Engine::getPlayer() {
    return player_;
}

Enemy Engine::getEnemy() {
    int index = rand() % numEnemies_;
    return enemies_[index];
}

void Engine::generateMap() {
    std::ifstream mapFile("map.txt");
    if (mapFile.fail()) {
        std::cerr << "Failed to open map file" << std::endl;
        exit(1);
    }

    std::string line;
    while (std::getline(mapFile, line)) {
        std::vector<char> mapRow;
        for (char c : line) {
            mapRow.push_back(c);
        }
        gameMap_.push_back(mapRow);
    }
    mapWidth_ = gameMap_[0].size();
    mapHeight_ = gameMap_.size();
}

void Engine::generateEnemies() {
    numEnemies_ = 10;
    for (int i = 0; i < numEnemies_; i++) {
        int x = rand() % mapWidth_;
        int y = rand() % mapHeight_;
        enemies_.push_back(Enemy(x, y, 'E'));
    }
}
