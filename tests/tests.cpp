#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <gtest/gtest.h>
#include <iostream>
#include <memory>
#include <random>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>

#include "../headers/Food.hpp"
#include "../headers/Game.hpp"
#include "../headers/GameWorld.hpp"
#include "../headers/Grid.hpp"
#include "../headers/Gui.hpp"
#include "../headers/Maps.hpp"
#include "../headers/Organism.hpp"
#include "../headers/Stats.hpp"
#include "../headers/Vars.hpp"

// sudo dnf install gtest-devel
// sudo dnf install gtest
// run:
// g++ -I/usr/include -I./headers -I/usr/local/include -L/usr/lib64 -L/usr/local/lib ../source/Grid.o ../source/Organism.o ../source/Game.o ../source/Vars.o ../source/Gui.o ../source/Stats.o ../source/Food.o ../source/GameWorld.o ../source/Maps.o tests.cpp -o tests -lgtest -lgtest_main -pthread -lsfml-graphics -lsfml-window -lsfml-system -lstdc++ &&


// #################### LAST RUN RESULTS ####################

// [==========] Running 14 tests from 3 test suites.
// [----------] Global test environment set-up.
// [----------] 1 test from Game
// [ RUN      ] Game.test_if_map_exists
// [       OK ] Game.test_if_map_exists (82 ms)
// [----------] 1 test from Game (82 ms total)

// [----------] 5 tests from GameWorld
// [ RUN      ] GameWorld.test_if_map1_initilazies
// [       OK ] GameWorld.test_if_map1_initilazies (79 ms)
// [ RUN      ] GameWorld.test_if_map2_initilazies
// [       OK ] GameWorld.test_if_map2_initilazies (65 ms)
// [ RUN      ] GameWorld.test_if_map3_initilazies
// [       OK ] GameWorld.test_if_map3_initilazies (68 ms)
// [ RUN      ] GameWorld.test_if_map4_initilazies
// [       OK ] GameWorld.test_if_map4_initilazies (61 ms)
// [ RUN      ] GameWorld.natural_selection_org_doesnt_die
// [       OK ] GameWorld.natural_selection_org_doesnt_die (60 ms)
// [----------] 5 tests from GameWorld (334 ms total)

// [----------] 8 tests from Organism
// [ RUN      ] Organism.test_eating_food_at_same_location
// [       OK ] Organism.test_eating_food_at_same_location (58 ms)
// [ RUN      ] Organism.test_eating_food_is_at_reach1
// [       OK ] Organism.test_eating_food_is_at_reach1 (56 ms)
// [ RUN      ] Organism.test_eating_food_is_at_reach_max_distance
// [       OK ] Organism.test_eating_food_is_at_reach_max_distance (53 ms)
// [ RUN      ] Organism.test_eating_food_is_over_max_possible_distance
// [       OK ] Organism.test_eating_food_is_over_max_possible_distance (53 ms)
// [ RUN      ] Organism.do_mitosis
// [       OK ] Organism.do_mitosis (56 ms)
// [ RUN      ] Organism.try_mitosis_not_enough_energy
// [       OK ] Organism.try_mitosis_not_enough_energy (54 ms)
// [ RUN      ] Organism.mutate
// [       OK ] Organism.mutate (58 ms)
// [ RUN      ] Organism.mutate_with_value_lower_than_mutation_value
// [       OK ] Organism.mutate_with_value_lower_than_mutation_value (54 ms)
// [----------] 8 tests from Organism (445 ms total)

// [----------] Global test environment tear-down
// [==========] 14 tests from 3 test suites ran. (862 ms total)

// #################### VALGRIND ####################
// I have tested the program with valgrind:
// run: valgrind --leak-check=full --log-file="logfile.out" -v ./game

// you can look inside "logfile.out" for the results of the valgrind test.
// It detects memory leaks, but they dont seem to be in my code, but in the SFML
// library. I have looked on the internet and i am not alone seeing them - but
// also people claim it is not really a problem.

// #################### TESTS ####################

std::string print_vector(const std::vector<int> &v) {
  std::string s = "";
  for (int i = 0; i < v.size(); i++) {
    s += std::to_string(v[i]) + " ";
  }
  return s;
}

TEST(Game, test_if_map_exists) {
  GameWorld gw(WINDOW_HEIGHT_GAME, WINDOW_WIDTH_GAME, ORGANISM_SIZE,
               NUMBER_OF_FOOD, NUMBER_OF_ANTIBIOTIC);
  Game game(gw);
  // game.test_if_map_exists();
  ASSERT_EQ(game.maps.size(), 4); // maps have been loaded
}

TEST(GameWorld, test_if_map1_initilazies) {
  GameWorld gw(WINDOW_HEIGHT_GAME, WINDOW_WIDTH_GAME, ORGANISM_SIZE,
               NUMBER_OF_FOOD, NUMBER_OF_ANTIBIOTIC);
  Game game(gw);
  game.maps[MAP - 1]->initialize();
  ASSERT_GT(gw.organisms.size(), 0); // organism spawn
  ASSERT_EQ(gw.organisms.size(),
            NUMBER_OF_ORGANISMS);       // organism spawn correct amount
  ASSERT_GT(gw.grid.amount_of_food, 0); // food spawns
}

TEST(GameWorld, test_if_map2_initilazies) {
  GameWorld gw(WINDOW_HEIGHT_GAME, WINDOW_WIDTH_GAME, ORGANISM_SIZE,
               NUMBER_OF_FOOD, NUMBER_OF_ANTIBIOTIC);
  Game game(gw);
  gw.grid.new_gird();

  game.maps[1]->initialize();
  ASSERT_GT(gw.organisms.size(), 0); // organism spawn
  ASSERT_EQ(gw.organisms.size(),
            NUMBER_OF_ORGANISMS);       // organism spawn correct amount
  ASSERT_GT(gw.grid.amount_of_food, 0); // food spawns
}

TEST(GameWorld, test_if_map3_initilazies) {
  GameWorld gw(WINDOW_HEIGHT_GAME, WINDOW_WIDTH_GAME, ORGANISM_SIZE,
               NUMBER_OF_FOOD, NUMBER_OF_ANTIBIOTIC);
  Game game(gw);
  gw.grid.new_gird();

  game.maps[2]->initialize();
  ASSERT_GT(gw.organisms.size(), 0); // organism spawn
  ASSERT_EQ(gw.organisms.size(),
            NUMBER_OF_ORGANISMS);       // organism spawn correct amount
  ASSERT_GT(gw.grid.amount_of_food, 0); // food spawns
}

TEST(GameWorld, test_if_map4_initilazies) {
  GameWorld gw(WINDOW_HEIGHT_GAME, WINDOW_WIDTH_GAME, ORGANISM_SIZE,
               NUMBER_OF_FOOD, NUMBER_OF_ANTIBIOTIC);
  Game game(gw);
  gw.grid.new_gird();

  game.maps[3]->initialize();
  ASSERT_GT(gw.organisms.size(), 0); // organism spawn
  ASSERT_EQ(gw.organisms.size(),
            NUMBER_OF_ORGANISMS);       // organism spawn correct amount
  ASSERT_GT(gw.grid.amount_of_food, 0); // food spawns
}

TEST(GameWorld, natural_selection_org_doesnt_die) {
  GameWorld gw(WINDOW_HEIGHT_GAME, WINDOW_WIDTH_GAME, ORGANISM_SIZE,
               NUMBER_OF_FOOD, NUMBER_OF_ANTIBIOTIC);
  Game game(gw);

  int x = WINDOW_WIDTH_GAME / 2;
  int y = WINDOW_HEIGHT_GAME / 2;
  int size = 3;
  int speed = 1;
  int energy = 100;
  std::vector<int> chances = {25, 25, 25, 25};
  int height = WINDOW_HEIGHT_GAME;
  int width = WINDOW_WIDTH_GAME;

  gw.organisms.push_back(std::make_unique<Organism>(
      x, y, size, speed, energy, chances, height, width,
      size * MAX_SIZE_MULTIPLIER, MUTATION_RATE, CHANCE_OF_MUTATION, 0));
}

TEST(Organism, test_eating_food_at_same_location) {
  GameWorld gw(WINDOW_HEIGHT_GAME, WINDOW_WIDTH_GAME, ORGANISM_SIZE,
               NUMBER_OF_FOOD, NUMBER_OF_ANTIBIOTIC);
  Game game(gw);

  gw.organisms.clear();
  gw.grid.new_gird();

  int starting_amount_od_food = gw.grid.amount_of_food;
  ASSERT_EQ(gw.grid.amount_of_food, 0);
  gw.grid.addFood(WINDOW_WIDTH_GAME / 2, WINDOW_HEIGHT_GAME / 2, 3, 3,
                  sf::Color::Yellow);
  ASSERT_EQ(gw.grid.amount_of_food, 1);

  int x = WINDOW_WIDTH_GAME / 2;
  int y = WINDOW_HEIGHT_GAME / 2;
  int size = 3;
  int speed = 1;
  int energy = 100;
  std::vector<int> chances = {25, 25, 25, 25};
  int height = WINDOW_HEIGHT_GAME;
  int width = WINDOW_WIDTH_GAME;

  gw.organisms.push_back(std::make_unique<Organism>(
      x, y, size, speed, energy, chances, height, width,
      size * MAX_SIZE_MULTIPLIER, MUTATION_RATE, CHANCE_OF_MUTATION, 0));

  gw.organisms[0]->try_to_eat(gw.grid);

  ASSERT_EQ(gw.organisms[0]->energy, 103); // has eaten food and gained energy
  ASSERT_EQ(gw.grid.amount_of_food, 0);
}

TEST(Organism, test_eating_food_is_at_reach1) {
  GameWorld gw(WINDOW_HEIGHT_GAME, WINDOW_WIDTH_GAME, ORGANISM_SIZE,
               NUMBER_OF_FOOD, NUMBER_OF_ANTIBIOTIC);
  Game game(gw);

  gw.organisms.clear();
  gw.grid.new_gird();

  int starting_amount_od_food = gw.grid.amount_of_food;
  ASSERT_EQ(gw.grid.amount_of_food, 0);
  gw.grid.addFood(WINDOW_WIDTH_GAME / 2, WINDOW_HEIGHT_GAME / 2, 3, 3,
                  sf::Color::Yellow);
  ASSERT_EQ(gw.grid.amount_of_food, 1);

  int x = WINDOW_WIDTH_GAME / 2 + 5;
  int y = WINDOW_HEIGHT_GAME / 2 + 7;
  int size = 10;
  int speed = 1;
  int energy = 100;
  std::vector<int> chances = {25, 25, 25, 25};
  int height = WINDOW_HEIGHT_GAME;
  int width = WINDOW_WIDTH_GAME;

  gw.organisms.push_back(std::make_unique<Organism>(
      x, y, size, speed, energy, chances, height, width,
      size * MAX_SIZE_MULTIPLIER, MUTATION_RATE, CHANCE_OF_MUTATION, 0));

  gw.organisms[0]->try_to_eat(gw.grid);

  ASSERT_EQ(gw.organisms[0]->energy, 103); // has eaten food and gained energy
  ASSERT_EQ(gw.grid.amount_of_food, 0);
}

TEST(Organism, test_eating_food_is_at_reach_max_distance) {
  GameWorld gw(WINDOW_HEIGHT_GAME, WINDOW_WIDTH_GAME, ORGANISM_SIZE,
               NUMBER_OF_FOOD, NUMBER_OF_ANTIBIOTIC);
  Game game(gw);

  gw.organisms.clear();
  gw.grid.new_gird();

  int starting_amount_od_food = gw.grid.amount_of_food;
  ASSERT_EQ(gw.grid.amount_of_food, 0);
  gw.grid.addFood(WINDOW_WIDTH_GAME / 2, WINDOW_HEIGHT_GAME / 2, 3, 3,
                  sf::Color::Yellow);
  ASSERT_EQ(gw.grid.amount_of_food, 1);

  int x = WINDOW_WIDTH_GAME / 2 + 10;
  int y = WINDOW_HEIGHT_GAME / 2 - 3;
  int size = 10;
  int speed = 1;
  int energy = 100;
  std::vector<int> chances = {25, 25, 25, 25};
  int height = WINDOW_HEIGHT_GAME;
  int width = WINDOW_WIDTH_GAME;

  gw.organisms.push_back(std::make_unique<Organism>(
      x, y, size, speed, energy, chances, height, width,
      size * MAX_SIZE_MULTIPLIER, MUTATION_RATE, CHANCE_OF_MUTATION, 0));

  gw.organisms[0]->try_to_eat(gw.grid);

  ASSERT_EQ(gw.organisms[0]->energy, 103); // has eaten food and gained energy
  ASSERT_EQ(gw.grid.amount_of_food, 0);
}

TEST(Organism, test_eating_food_is_over_max_possible_distance) {
  GameWorld gw(WINDOW_HEIGHT_GAME, WINDOW_WIDTH_GAME, ORGANISM_SIZE,
               NUMBER_OF_FOOD, NUMBER_OF_ANTIBIOTIC);
  Game game(gw);

  gw.organisms.clear();
  gw.grid.new_gird();

  int starting_amount_od_food = gw.grid.amount_of_food;
  ASSERT_EQ(gw.grid.amount_of_food, 0);
  gw.grid.addFood(WINDOW_WIDTH_GAME / 2, WINDOW_HEIGHT_GAME / 2, 3, 3,
                  sf::Color::Yellow);
  ASSERT_EQ(gw.grid.amount_of_food, 1);

  int x = WINDOW_WIDTH_GAME / 2 + 11;
  int y = WINDOW_HEIGHT_GAME / 2 - 3;
  int size = 10;
  int speed = 1;
  int energy = 100;
  std::vector<int> chances = {25, 25, 25, 25};
  int height = WINDOW_HEIGHT_GAME;
  int width = WINDOW_WIDTH_GAME;

  gw.organisms.push_back(std::make_unique<Organism>(
      x, y, size, speed, energy, chances, height, width,
      size * MAX_SIZE_MULTIPLIER, MUTATION_RATE, CHANCE_OF_MUTATION, 0));

  gw.spawn_organisms(1, 0);
  gw.organisms[0]->try_to_eat(gw.grid);

  ASSERT_EQ(gw.organisms[0]->energy,
            100); // has not eaten food and gained energy
  ASSERT_EQ(gw.grid.amount_of_food, 1);
}

TEST(Organism, do_mitosis) {
  GameWorld gw(WINDOW_HEIGHT_GAME, WINDOW_WIDTH_GAME, ORGANISM_SIZE,
               NUMBER_OF_FOOD, NUMBER_OF_ANTIBIOTIC);
  Game game(gw);

  gw.organisms.clear();
  gw.grid.new_gird();

  int x = WINDOW_WIDTH_GAME / 2;
  int y = WINDOW_HEIGHT_GAME / 2;
  int size = 10;
  int speed = 1;
  int energy = 287;
  std::vector<int> chances = {25, 25, 25, 25};
  int height = WINDOW_HEIGHT_GAME;
  int width = WINDOW_WIDTH_GAME;

  REPRODUCTION_ENERGY = 200;

  gw.organisms.push_back(std::make_unique<Organism>(
      x, y, size, speed, energy, chances, height, width,
      size * MAX_SIZE_MULTIPLIER, MUTATION_RATE, CHANCE_OF_MUTATION, 0));

  gw.organisms[0]->try_to_eat(gw.grid);
  gw.organisms[0]->try_mitosis(gw.organisms, REPRODUCTION_ENERGY);

  ASSERT_EQ(gw.organisms.size(), 2);
  ASSERT_EQ(gw.organisms[0]->energy, energy / 2); // daughter cell
  ASSERT_EQ(gw.organisms[1]->energy, energy / 2); // daughter cell
}

TEST(Organism, try_mitosis_not_enough_energy) {
  GameWorld gw(WINDOW_HEIGHT_GAME, WINDOW_WIDTH_GAME, ORGANISM_SIZE,
               NUMBER_OF_FOOD, NUMBER_OF_ANTIBIOTIC);
  Game game(gw);

  gw.organisms.clear();
  gw.grid.new_gird();

  int x = WINDOW_WIDTH_GAME / 2;
  int y = WINDOW_HEIGHT_GAME / 2;
  int size = 10;
  int speed = 1;
  int energy = 187;
  std::vector<int> chances = {25, 25, 25, 25};
  int height = WINDOW_HEIGHT_GAME;
  int width = WINDOW_WIDTH_GAME;

  REPRODUCTION_ENERGY = 200;

  gw.organisms.push_back(std::make_unique<Organism>(
      x, y, size, speed, energy, chances, height, width,
      size * MAX_SIZE_MULTIPLIER, MUTATION_RATE, CHANCE_OF_MUTATION, 0));

  gw.organisms[0]->try_to_eat(gw.grid);
  gw.organisms[0]->try_mitosis(gw.organisms, REPRODUCTION_ENERGY);

  ASSERT_EQ(gw.organisms.size(), 1);
  ASSERT_EQ(gw.organisms[0]->energy, energy); // same cell
}

TEST(Organism, mutate) {
  GameWorld gw(WINDOW_HEIGHT_GAME, WINDOW_WIDTH_GAME, ORGANISM_SIZE,
               NUMBER_OF_FOOD, NUMBER_OF_ANTIBIOTIC);
  Game game(gw);

  gw.organisms.clear();
  gw.grid.new_gird();

  int x = WINDOW_WIDTH_GAME / 2;
  int y = WINDOW_HEIGHT_GAME / 2;
  int size = 10;
  int speed = 1;
  int energy = 287;
  std::vector<int> chances = {25, 25, 25, 25};
  int height = WINDOW_HEIGHT_GAME;
  int width = WINDOW_WIDTH_GAME;

  gw.organisms.push_back(std::make_unique<Organism>(
      x, y, size, speed, energy, chances, height, width,
      size * MAX_SIZE_MULTIPLIER, MUTATION_RATE, CHANCE_OF_MUTATION, 0));
  gw.organisms[0]->mutate(true);

  std::vector<int> chances_after = gw.organisms[0]->chances;

  ASSERT_NE(chances, chances_after);
  ASSERT_EQ(gw.sum_of_vector(chances_after), 100);
}

TEST(Organism, mutate_with_value_lower_than_mutation_value) {
  GameWorld gw(WINDOW_HEIGHT_GAME, WINDOW_WIDTH_GAME, ORGANISM_SIZE,
               NUMBER_OF_FOOD, NUMBER_OF_ANTIBIOTIC);
  Game game(gw);

  gw.organisms.clear();
  gw.grid.new_gird();

  int x = WINDOW_WIDTH_GAME / 2;
  int y = WINDOW_HEIGHT_GAME / 2;
  int size = 10;
  int speed = 1;
  int energy = 287;
  std::vector<int> chances = {2, 2, 2, 94};
  int height = WINDOW_HEIGHT_GAME;
  int width = WINDOW_WIDTH_GAME;

  MUTATION_RATE = 5;

  gw.organisms.push_back(std::make_unique<Organism>(
      x, y, size, speed, energy, chances, height, width,
      size * MAX_SIZE_MULTIPLIER, MUTATION_RATE, CHANCE_OF_MUTATION, 0));
  gw.organisms[0]->mutate(true);

  std::vector<int> chances_after = gw.organisms[0]->chances;

  ASSERT_NE(chances, chances_after) << print_vector(chances) << " "
                                    << print_vector(chances_after) << std::endl;
  ASSERT_EQ(gw.sum_of_vector(chances_after), 100)
      << print_vector(chances) << " " << print_vector(chances_after)
      << std::endl;
  ;
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
