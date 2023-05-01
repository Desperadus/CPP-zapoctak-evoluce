#pragma once

#include <vector>
#include <memory>
#include "Grid.hpp"
#include "Organism.hpp"
#include "Vars.hpp"
#include <tuple>
#include <algorithm>
#include <random>
#include <iostream>


class GameWorld{
public:
   const int height;
   const int width;
   int& org_size;
   int grid_size = AMOUNT_OF_GRID_CELLS;
   int& number_of_food;
   int& number_of_antibiotic;
   bool adding_antibiotics = false;
   std::vector<std::unique_ptr<Organism> > organisms;
   std::vector<std::tuple <int, int > > antibiotic_block_coords;

   Grid grid;
   
   GameWorld(const int height, const int width, int& org_size, int& number_of_food, int& number_of_antibiotic);

   template <typename T>
   int sum_of_vector(const T & v) const;

   void spawn_organisms(int amount, int energy);
   
   void spawn_random_food(int amount_of_food);

   void create_antibiotic_block(int antibiotic_energy, int click_x, int click_y, int amount_of_lines);

   void spawn_antibiotics(int amount_of_lines, int amount_of_antibiotics, int antibiotic_energy);
};
