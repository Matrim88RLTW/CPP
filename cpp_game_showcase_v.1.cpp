#include <iostream>
#include <string>
#include <vector>

#include "tensorflow/cc/ops/standard_ops.h"
#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/core/public/session.h"
#include "tensorflow/core/util/command_line_flags.h"

using namespace tensorflow;

class Character {
public:
  int x;
  int y;
  std::string image;
  int health;
  int attackPower;
  int defense;
  int speed;
  int level;
  std::vector<std::string> inventory;
  std::string type;
  std::string name;

  Character(int x, int y, std::string image, int health, int attackPower, int defense, int speed, int level, std::vector<std::string> inventory, std::string type, std::string name) :
    x(x), y(y), image(image), health(health), attackPower(attackPower), defense(defense), speed(speed), level(level), inventory(inventory), type(type), name(name) {}
  void move(int newX, int newY);
  void attack(Character& target);
  void defend(int damage);
  void useItem(std::string itemName);
  void levelUp();
};

class Enemy : public Character {
public:
  int experiencePoints;
  std::vector<std::string> loot;

#ifndef ENEMY_H
#define ENEMY_H

#include <vector>

class Enemy : public Character {
public:
  Enemy(int x, int y, std::string image, int health, int attackPower, int defense, int speed, int level, std::vector<std::string> inventory, int experiencePoints, std::vector<std::string> loot) :
      Character(x, y, image, health, attackPower, defense, speed, level, inventory, "enemy", "goblin"), experiencePoints(experiencePoints), loot(loot) {}
  int getExperiencePoints();
  std::vector<std::string> getLoot();
};

#endif

int main(int argc, char* argv[]) {
  // create and train model for predicting battle outcomes
  Scope root = Scope::NewRootScope();
  auto input = ops::Placeholder(root.WithOpName("input"), DT_FLOAT, ops::Placeholder::Shape({None, 10}));
  auto fc1 = ops::MatMul(root.WithOpName("fc1"), input, ops::Const(root.WithOpName("weights1"), {{32}, {32}, {32}, {32}, {32}, {32}, {32}, {32}, {32}, {32}}));
  auto fc2 = ops::MatMul(root.WithOpName("fc2"), fc1, ops::Const(root.WithOpName("weights2"), {{16}, {16}, {16}, {16}}));
  auto fc3 = ops::MatMul(root.WithOpName("fc3"), fc2, ops::Const(root.WithOpName("weights3"), {{1}, {1}}));
  auto loss = ops::MeanSquaredError(root.WithOpName("loss"), fc3, ops::Placeholder(root.WithOpName("label"), DT_FLOAT, ops::Placeholder::Shape({None, 1})));
  std::vector<Tensor> output;
  ClientSession session(root);

// read in dataset of past battles
std::vector<std::vector<float>> inputData = {
  {100, 15, 5, 3, 1, 50, 7, 3, 1, 1, 1},
  {30, 5, 2, 2, 1, 50, 7, 3, 1, 1, 0},
  {100, 15, 5, 3, 5, 70, 10, 4, 2, 3, 1},
  {70, 10, 4, 2, 3, 50, 7, 3, 1, 1, 0},
};
std::vector<std::vector<float>> outputData = {{1}, {0}, {1}, {0}};

// compile and fit model
std::vector<Tensor> output;
ClientSession session(root);
std::vector<std::pair<string, Tensor>> inputs = {{"input", tensorflow::Tensor(DT_FLOAT, {4, 10})}, {"label", tensorflow::Tensor(DT_FLOAT, {4, 1})}};
tensorflow::Tensor inputTensor(DT_FLOAT, {4, 10});
for (int i = 0; i < 4; ++i) {
  for (int j = 0; j < 10; ++j) {
    inputTensor.matrix<float>()(i, j) = inputData[i][j];
  }
}
inputs[0].second = inputTensor;
tensorflow::Tensor outputTensor(DT_FLOAT, {4, 1});
for (int i = 0; i < 4; ++i) {
  outputTensor.matrix<float>()(i, 0) = outputData[i][0];
}
inputs[1].second = outputTensor;
session.Run(inputs, {"loss"}, {}, &output);

// use model to predict outcome of battle
Tensor battleInputTensor(DT_FLOAT, {1, 10});
battleInputTensor.matrix<float>()(0, 0) = 50;
battleInputTensor.matrix<float>()(0, 1) = 7;
battleInputTensor.matrix<float>()(0, 2) = 3;
battleInputTensor.matrix<float>()(0, 3) = 1;
battleInputTensor.matrix<float>()(0, 4) = 1;
battleInputTensor.matrix<float>()(0, 5) = 1;
battleInputTensor.matrix<float>()(0, 6) = 1;
battleInputTensor.matrix<float>()(0, 7) = 100;
battleInputTensor.matrix<float>()(0, 8) = 15;
battleInputTensor.matrix<float>()(0, 9) = 5;
std::vector<Tensor> battleOutput = session.Run({{"input", battleInputTensor}}, {"fc3"}, {});
float prediction = battleOutput[0].matrix<float>()(0, 0);
std::cout << "Prediction for this battle: " << prediction << std::endl;

// use unsupervised learning to generate new enemies
auto input = ops::Placeholder(root.WithOpName("input"), DT_FLOAT, ops::Placeholder::Shape({4, 7}));
auto fc1 = ops::MatMul(root.WithOpName("fc1"), input, ops::Const(root, {{8}, {8}, {8}, {8}, {8}, {8}, {8}}));
auto fc2 = ops::MatMul(root.WithOpName("fc2"), fc1, ops::Const(root, {{4}, {4}, {4}, {4}}));
auto fc3 = ops::MatMul(root.WithOpName("fc3"), fc2, ops::Const(root, {{2}, {2}}));
std::vector<Tensor> output;
ClientSession session(root);

// read in dataset of enemy characteristics
std::vector<std::vector<float>> inputData = {
  {50, 7, 3, 1, 1, 15, 15},
  {70, 10, 4, 2, 3, 30, 30},
  {100, 15, 5, 3, 5, 50, 50},
  {30, 5, 2, 2, 1, 10, 10},
};
Tensor inputTensor(DT_FLOAT, {4, 7});
for (int i = 0; i < 4; ++i) {
  for (int j = 0; j < 7; ++j) {
    inputTensor.matrix<float>()(i, j) = inputData[i][j];
  }
}

// cluster enemy types
std::vector<Tensor> clusteringOutput = session.Run({{"input", inputTensor}}, {"fc3"}, {});

// create new enemy based on generated data
Tensor inputTensor(DT_FLOAT, {1, 7});
inputTensor.matrix<float>()(0, 0) = 50;
inputTensor.matrix<float>()(0, 1) = 7;
inputTensor.matrix<float>()(0, 2) = 3;
inputTensor.matrix<float>()(0, 3) = 1;
inputTensor.matrix<float>()(0, 4) = 1;
inputTensor.matrix<float>()(0, 5) = 15;
inputTensor.matrix<float>()(0, 6) = 15;
std::vector<Tensor> newEnemyOutput = session.Run({{"input", inputTensor}}, {"fc3"}, {});

// create new enemy based on generated data
Enemy newEnemy;
newEnemy.x = newEnemyOutput[0].matrix<float>()(0, 0);
newEnemy.y = newEnemyOutput[0].matrix<float>()(0, 1);
newEnemy.image = "new_enemy.png";
newEnemy.health = 50;
newEnemy.attackPower = 7;
newEnemy.defense = 3;
newEnemy.speed = 1;
newEnemy.level = 1;
newEnemy.loot = {"gold", "mystery item"};

std::cout << "New enemy: " << newEnemy.x << " " << newEnemy.y << std::endl;

return 0;