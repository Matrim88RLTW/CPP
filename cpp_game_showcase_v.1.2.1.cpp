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

  Character(int x, int y, std::string image, int health, int attackPower, int defense, int speed, int level, std::vector<std::string> inventory, std::string type, std::string name)
      : x(x), y(y), image(image), health(health), attackPower(attackPower), defense(defense), speed(speed), level(level), inventory(inventory), type(type), name(name) {}

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

  Enemy(int x, int y, std::string image, int health, int attackPower, int defense, int speed, int level, std::vector<std::string> inventory, int experiencePoints, std::vector<std::string> loot)
      : Character(x, y, image, health, attackPower, defense, speed, level, inventory, "enemy", "goblin"), experiencePoints(experiencePoints), loot(loot) {}

  int getExperiencePoints() { return experiencePoints; }
  std::vector<std::string> getLoot() { return loot; }
};

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
std::vector<std::pair<string, Tensor>> inputs = {
  {{"input", Tensor(DT_FLOAT, {4, 10})},
  {{"label", Tensor(DT_FLOAT, {4, 1})}
};
auto inputTensor = inputs[0].second.matrix<float>();
auto labelTensor = inputs[1].second.matrix<float>();
for (int i = 0; i < 4; ++i) {
  for (int j = 0; j < 10; ++j) {
    inputTensor(i, j) = inputData[i][j];
  }
  labelTensor(i, 0) = outputData[i][0];
}
output = session.Run(inputs, {"loss"}, {});
std::cout << output[0].scalar<float>() << std::endl;

// use model to predict outcomes for new battles
std::vector<std::vector<float>> newInputData = {
  {80, 12, 4, 2, 3, 60, 8, 3, 2, 2, 1},
  {50, 7, 3, 1, 2, 50, 7, 3, 1, 1, 0},
  {100, 15, 5, 3, 4, 80, 10, 4, 3, 3, 1},
  {90, 13, 4, 2, 5, 50, 7, 3, 1, 1, 0},
};

inputs[0] = {{"input", Tensor(DT_FLOAT, {4, 10})}};
inputTensor = inputs[0].second.matrix<float>();
for (int i = 0; i < 4; ++i) {
  for (int j = 0; j < 10; ++j) {
    inputTensor(i, j) = newInputData[i][j];
  }
}
output = session.Run(inputs, {"fc3"}, {});
for (int i = 0; i < 4; ++i) {
  std::cout << output[0].matrix<float>()(i, 0) << std::endl;
}

return 0;