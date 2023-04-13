#include <gtest/gtest.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <memory>
#include <cmath>


#include "Vars.hpp"
#include "Food.hpp"
#include "Grid.hpp"
#include "Organism.hpp"
#include "GameWorld.hpp"
#include "Stats.hpp"
#include "Game.hpp"
#include "Gui.hpp"
#include "Maps.hpp"

//sudo dnf install gtest-devel
//sudo dnf install gtest
//run: gcc -I/usr/include -I/usr/local/include -L/usr/lib64 -L/usr/local/lib tests.cpp -o tests -lgtest -lgtest_main -pthread -lsfml-graphics -lsfml-window -lsfml-system -lstdc++ && ./tests


std::string print_vector(const std::vector<int>& v) {
    std::string s = "";
    for (int i = 0; i < v.size(); i++) {
        s += std::to_string(v[i]) + " ";
    }
    return s;
}

TEST(Game, test_if_map_exists) {
    GameWorld gw(WINDOW_HEIGHT_GAME, WINDOW_WIDTH_GAME, ORGANISM_SIZE, NUMBER_OF_FOOD, NUMBER_OF_ANTIBIOTIC);
    Game game(gw);
    GUI gui(gw, game);
    //game.test_if_map_exists();
    ASSERT_EQ(game.maps.size(), 4); //maps have been loaded
}

TEST(GameWorld, test_if_map1_initilazies) {
    GameWorld gw(WINDOW_HEIGHT_GAME, WINDOW_WIDTH_GAME, ORGANISM_SIZE, NUMBER_OF_FOOD, NUMBER_OF_ANTIBIOTIC);
    Game game(gw);
    GUI gui(gw, game);
    game.maps[MAP-1]->initialize();
    ASSERT_GT(gw.organisms.size(), 0); //organism spawn
    ASSERT_EQ(gw.organisms.size(), NUMBER_OF_ORGANISMS); //organism spawn correct amount
    ASSERT_GT(gw.grid.amount_of_food, 0); //food spawns
}

TEST(GameWorld, test_if_map2_initilazies) {
    GameWorld gw(WINDOW_HEIGHT_GAME, WINDOW_WIDTH_GAME, ORGANISM_SIZE, NUMBER_OF_FOOD, NUMBER_OF_ANTIBIOTIC);
    Game game(gw);
    GUI gui(gw, game);
    gw.grid.new_gird();


    game.maps[1]->initialize();
    ASSERT_GT(gw.organisms.size(), 0); //organism spawn
    ASSERT_EQ(gw.organisms.size(), NUMBER_OF_ORGANISMS); //organism spawn correct amount
    ASSERT_GT(gw.grid.amount_of_food, 0); //food spawns
}

TEST(GameWorld, test_if_map3_initilazies) {
    GameWorld gw(WINDOW_HEIGHT_GAME, WINDOW_WIDTH_GAME, ORGANISM_SIZE, NUMBER_OF_FOOD, NUMBER_OF_ANTIBIOTIC);
    Game game(gw);
    GUI gui(gw, game);
    gw.grid.new_gird();

    game.maps[2]->initialize();
    ASSERT_GT(gw.organisms.size(), 0); //organism spawn
    ASSERT_EQ(gw.organisms.size(), NUMBER_OF_ORGANISMS); //organism spawn correct amount
    ASSERT_GT(gw.grid.amount_of_food, 0); //food spawns

}

TEST(GameWorld, test_if_map4_initilazies) {
    GameWorld gw(WINDOW_HEIGHT_GAME, WINDOW_WIDTH_GAME, ORGANISM_SIZE, NUMBER_OF_FOOD, NUMBER_OF_ANTIBIOTIC);
    Game game(gw);
    GUI gui(gw, game);
    gw.grid.new_gird();

    game.maps[3]->initialize();
    ASSERT_GT(gw.organisms.size(), 0); //organism spawn
    ASSERT_EQ(gw.organisms.size(), NUMBER_OF_ORGANISMS); //organism spawn correct amount
    ASSERT_GT(gw.grid.amount_of_food, 0); //food spawns

}

TEST(GameWorld, natural_selection_org_doesnt_die) {
    GameWorld gw(WINDOW_HEIGHT_GAME, WINDOW_WIDTH_GAME, ORGANISM_SIZE, NUMBER_OF_FOOD, NUMBER_OF_ANTIBIOTIC);
    Game game(gw);
    GUI gui(gw, game);
    
    int x = WINDOW_WIDTH_GAME/2;
    int y = WINDOW_HEIGHT_GAME/2;
    int size = 3;
    int speed = 1;
    int energy = 100;
    std::vector<int> chances = {25, 25, 25, 25};
    int height = WINDOW_HEIGHT_GAME;
    int width = WINDOW_WIDTH_GAME;


    gw.organisms.push_back(std::make_unique<Organism>(x, y, size, speed, energy, chances, height, width, size*MAX_SIZE_MULTIPLIER, 0));



}

TEST(Organism, test_eating_food_at_same_location) {
    GameWorld gw(WINDOW_HEIGHT_GAME, WINDOW_WIDTH_GAME, ORGANISM_SIZE, NUMBER_OF_FOOD, NUMBER_OF_ANTIBIOTIC);
    Game game(gw);
    GUI gui(gw, game);
   
    gw.organisms.clear();
    gw.grid.new_gird();
   
    int starting_amount_od_food = gw.grid.amount_of_food;
    ASSERT_EQ(gw.grid.amount_of_food, 0);
    gw.grid.addFood(WINDOW_WIDTH_GAME/2, WINDOW_HEIGHT_GAME/2, 3, 3, sf::Color::Yellow);
    ASSERT_EQ(gw.grid.amount_of_food, 1);

    int x = WINDOW_WIDTH_GAME/2;
    int y = WINDOW_HEIGHT_GAME/2;
    int size = 3;
    int speed = 1;
    int energy = 100;
    std::vector<int> chances = {25, 25, 25, 25};
    int height = WINDOW_HEIGHT_GAME;
    int width = WINDOW_WIDTH_GAME;


    gw.organisms.push_back(std::make_unique<Organism>(x, y, size, speed, energy, chances, height, width, size*MAX_SIZE_MULTIPLIER, 0));

    gw.organisms[0]->try_to_eat(gw.grid);

    ASSERT_EQ(gw.organisms[0]->energy, 103); //has eaten food and gained energy
    ASSERT_EQ(gw.grid.amount_of_food, 0);

}

TEST(Organism, test_eating_food_is_at_reach1) {
    GameWorld gw(WINDOW_HEIGHT_GAME, WINDOW_WIDTH_GAME, ORGANISM_SIZE, NUMBER_OF_FOOD, NUMBER_OF_ANTIBIOTIC);
    Game game(gw);
    GUI gui(gw, game);
   
    gw.organisms.clear();
    gw.grid.new_gird();
   
    int starting_amount_od_food = gw.grid.amount_of_food;
    ASSERT_EQ(gw.grid.amount_of_food, 0);
    gw.grid.addFood(WINDOW_WIDTH_GAME/2, WINDOW_HEIGHT_GAME/2, 3, 3, sf::Color::Yellow);
    ASSERT_EQ(gw.grid.amount_of_food, 1);

    int x = WINDOW_WIDTH_GAME/2 + 5;
    int y = WINDOW_HEIGHT_GAME/2 + 7;
    int size = 10;
    int speed = 1;
    int energy = 100;
    std::vector<int> chances = {25, 25, 25, 25};
    int height = WINDOW_HEIGHT_GAME;
    int width = WINDOW_WIDTH_GAME;


    gw.organisms.push_back(std::make_unique<Organism>(x, y, size, speed, energy, chances, height, width, size*MAX_SIZE_MULTIPLIER, 0));

    gw.organisms[0]->try_to_eat(gw.grid);

    ASSERT_EQ(gw.organisms[0]->energy, 103); //has eaten food and gained energy
    ASSERT_EQ(gw.grid.amount_of_food, 0);

}

TEST(Organism, test_eating_food_is_at_reach_max_distance) {
    GameWorld gw(WINDOW_HEIGHT_GAME, WINDOW_WIDTH_GAME, ORGANISM_SIZE, NUMBER_OF_FOOD, NUMBER_OF_ANTIBIOTIC);
    Game game(gw);
    GUI gui(gw, game);
   
    gw.organisms.clear();
    gw.grid.new_gird();
   
    int starting_amount_od_food = gw.grid.amount_of_food;
    ASSERT_EQ(gw.grid.amount_of_food, 0);
    gw.grid.addFood(WINDOW_WIDTH_GAME/2, WINDOW_HEIGHT_GAME/2, 3, 3, sf::Color::Yellow);
    ASSERT_EQ(gw.grid.amount_of_food, 1);

    int x = WINDOW_WIDTH_GAME/2 + 10;
    int y = WINDOW_HEIGHT_GAME/2 - 3;
    int size = 10;
    int speed = 1;
    int energy = 100;
    std::vector<int> chances = {25, 25, 25, 25};
    int height = WINDOW_HEIGHT_GAME;
    int width = WINDOW_WIDTH_GAME;


    gw.organisms.push_back(std::make_unique<Organism>(x, y, size, speed, energy, chances, height, width, size*MAX_SIZE_MULTIPLIER, 0));
    
    gw.organisms[0]->try_to_eat(gw.grid);

    ASSERT_EQ(gw.organisms[0]->energy, 103); //has eaten food and gained energy
    ASSERT_EQ(gw.grid.amount_of_food, 0);

}

TEST(Organism, test_eating_food_is_over_max_possible_distance) {
    GameWorld gw(WINDOW_HEIGHT_GAME, WINDOW_WIDTH_GAME, ORGANISM_SIZE, NUMBER_OF_FOOD, NUMBER_OF_ANTIBIOTIC);
    Game game(gw);
    GUI gui(gw, game);
   
    gw.organisms.clear();
    gw.grid.new_gird();
   
    int starting_amount_od_food = gw.grid.amount_of_food;
    ASSERT_EQ(gw.grid.amount_of_food, 0);
    gw.grid.addFood(WINDOW_WIDTH_GAME/2, WINDOW_HEIGHT_GAME/2, 3, 3, sf::Color::Yellow);
    ASSERT_EQ(gw.grid.amount_of_food, 1);

    int x = WINDOW_WIDTH_GAME/2 + 11;
    int y = WINDOW_HEIGHT_GAME/2 - 3;
    int size = 10;
    int speed = 1;
    int energy = 100;
    std::vector<int> chances = {25, 25, 25, 25};
    int height = WINDOW_HEIGHT_GAME;
    int width = WINDOW_WIDTH_GAME;


    gw.organisms.push_back(std::make_unique<Organism>(x, y, size, speed, energy, chances, height, width, size*MAX_SIZE_MULTIPLIER, 0));

    gw.spawn_organisms(1,0);
    gw.organisms[0]->try_to_eat(gw.grid);

    ASSERT_EQ(gw.organisms[0]->energy, 100); //has not eaten food and gained energy
    ASSERT_EQ(gw.grid.amount_of_food, 1);

}

TEST(Organism, do_mitosis) {
    GameWorld gw(WINDOW_HEIGHT_GAME, WINDOW_WIDTH_GAME, ORGANISM_SIZE, NUMBER_OF_FOOD, NUMBER_OF_ANTIBIOTIC);
    Game game(gw);
    GUI gui(gw, game);
   
    gw.organisms.clear();
    gw.grid.new_gird();

    int x = WINDOW_WIDTH_GAME/2;
    int y = WINDOW_HEIGHT_GAME/2;
    int size = 10;
    int speed = 1;
    int energy = 287;
    std::vector<int> chances = {25, 25, 25, 25};
    int height = WINDOW_HEIGHT_GAME;
    int width = WINDOW_WIDTH_GAME;

    REPRODUCTION_ENERGY = 200;


    gw.organisms.push_back(std::make_unique<Organism>(x, y, size, speed, energy, chances, height, width, size*MAX_SIZE_MULTIPLIER, 0));

    gw.organisms[0]->try_to_eat(gw.grid);
    gw.organisms[0]->try_mitosis(gw.organisms, REPRODUCTION_ENERGY);

    ASSERT_EQ(gw.organisms.size(), 2);
    ASSERT_EQ(gw.organisms[0]->energy, energy / 2); //daughter cell
    ASSERT_EQ(gw.organisms[1]->energy, energy / 2); //daughter cell

}

TEST(Organism, try_mitosis_not_enough_energy) {
    GameWorld gw(WINDOW_HEIGHT_GAME, WINDOW_WIDTH_GAME, ORGANISM_SIZE, NUMBER_OF_FOOD, NUMBER_OF_ANTIBIOTIC);
    Game game(gw);
    GUI gui(gw, game);
   
    gw.organisms.clear();
    gw.grid.new_gird();

    int x = WINDOW_WIDTH_GAME/2;
    int y = WINDOW_HEIGHT_GAME/2;
    int size = 10;
    int speed = 1;
    int energy = 187;
    std::vector<int> chances = {25, 25, 25, 25};
    int height = WINDOW_HEIGHT_GAME;
    int width = WINDOW_WIDTH_GAME;

    REPRODUCTION_ENERGY = 200;


    gw.organisms.push_back(std::make_unique<Organism>(x, y, size, speed, energy, chances, height, width, size*MAX_SIZE_MULTIPLIER, 0));

    gw.organisms[0]->try_to_eat(gw.grid);
    gw.organisms[0]->try_mitosis(gw.organisms, REPRODUCTION_ENERGY);

    ASSERT_EQ(gw.organisms.size(), 1);
    ASSERT_EQ(gw.organisms[0]->energy, energy); //same cell

}

TEST(Organism, mutate) {
    GameWorld gw(WINDOW_HEIGHT_GAME, WINDOW_WIDTH_GAME, ORGANISM_SIZE, NUMBER_OF_FOOD, NUMBER_OF_ANTIBIOTIC);
    Game game(gw);
    GUI gui(gw, game);
   
    gw.organisms.clear();
    gw.grid.new_gird();

    int x = WINDOW_WIDTH_GAME/2;
    int y = WINDOW_HEIGHT_GAME/2;
    int size = 10;
    int speed = 1;
    int energy = 287;
    std::vector<int> chances = {25, 25, 25, 25};
    int height = WINDOW_HEIGHT_GAME;
    int width = WINDOW_WIDTH_GAME;

    gw.organisms.push_back(std::make_unique<Organism>(x, y, size, speed, energy, chances, height, width, size*MAX_SIZE_MULTIPLIER, 0));
    gw.organisms[0]->mutate(true);

    std::vector<int> chances_after = gw.organisms[0]->chances;

    ASSERT_NE(chances, chances_after);
    ASSERT_EQ(sum_of_vector(chances_after),100);

}

TEST(Organism, mutate_with_value_lower_than_mutation_value) {
    GameWorld gw(WINDOW_HEIGHT_GAME, WINDOW_WIDTH_GAME, ORGANISM_SIZE, NUMBER_OF_FOOD, NUMBER_OF_ANTIBIOTIC);
    Game game(gw);
    GUI gui(gw, game);
   
    gw.organisms.clear();
    gw.grid.new_gird();

    int x = WINDOW_WIDTH_GAME/2;
    int y = WINDOW_HEIGHT_GAME/2;
    int size = 10;
    int speed = 1;
    int energy = 287;
    std::vector<int> chances = {2, 2, 2, 94};
    int height = WINDOW_HEIGHT_GAME;
    int width = WINDOW_WIDTH_GAME;

    MUTATION_RATE = 5;

    gw.organisms.push_back(std::make_unique<Organism>(x, y, size, speed, energy, chances, height, width, size*MAX_SIZE_MULTIPLIER, 0));
    gw.organisms[0]->mutate(true);

    std::vector<int> chances_after = gw.organisms[0]->chances;

    ASSERT_NE(chances, chances_after) << print_vector(chances) <<" " <<print_vector(chances_after) << std::endl;
    ASSERT_EQ(sum_of_vector(chances_after),100) << print_vector(chances) <<" " <<print_vector(chances_after) << std::endl;;

}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}