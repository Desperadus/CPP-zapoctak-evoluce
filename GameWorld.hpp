#pragma once

template <typename T>
int sum_of_vector(const T & v) {
   int sum = 0;
   for (int i = 0; i < v.size(); i++) {
      sum += v[i];
   }
   return sum;
}

class GameWorld{
public:
   int& height;
   int& width;
   int& org_size;
   int grid_size = AMOUNT_OF_GRID_CELLS;
   int& number_of_food;
   int& number_of_antibiotic;
   bool adding_antibiotics = false;
   std::vector<std::unique_ptr<Organism> > organisms;
   std::vector<std::tuple <int, int > > antibiotic_block_coords;

   Grid grid;
   
   GameWorld(int& height, int& width, int& org_size, int& number_of_food, int& number_of_antibiotic) : grid(height, width, grid_size), height(height), width(width), org_size(org_size), number_of_food(number_of_food), number_of_antibiotic(number_of_antibiotic) {
      this->org_size = org_size;
   }

   
   void spawn_organisms(int amount, int energy) {
      srand((unsigned) time(NULL));
      for (int i = 0; i < amount; i++) {
         int x = rand() % width;
         int y = rand() % height;
         int size = org_size;
         int speed = rand() % org_size;
         if (speed < 1) {
            speed = 1;
         }

         
         std::vector<int> chances = { 0, 0, 0, 0 };
         for (int i = 0; i < 4; i++) {
            chances[i] = rand() % 100;
         }
         int sum = sum_of_vector(chances);
         for (int i = 0; i < 4; i++) {
            chances[i] = chances[i] * 100 / sum;
         }
         int sum2 = sum_of_vector(chances);
         if (sum2 != 100) {
            chances[0] += 100 - sum2;
         }
         
         //chances = {100,0,0,0};
         //y = 143;
         organisms.push_back(std::make_unique<Organism>(x, y, size, speed, energy, chances, height, width, size*MAX_SIZE_MULTIPLIER, 0));

         //break;
      }

   }

      
   
   void spawn_random_food(int amount_of_food) {
        for (int i = 0; i < amount_of_food; i++) {
            if (number_of_food <= grid.amount_of_food) return;
            int x = rand() % width;
            int y = rand() % height;

            grid.addFood(x, y, FOOD_SIZE, RAND_FOOD_ENERGY, sf::Color::Yellow);
        }
   }

   
   void create_antibiotic_block(int antibiotic_energy, int click_x, int click_y, int amount_of_lines) {
      if (adding_antibiotics == false) return;
      int x = (click_x / (width / amount_of_lines)) * (width / amount_of_lines);
      int y = (click_y / (height / amount_of_lines)) * (height / amount_of_lines);
      
      antibiotic_block_coords.push_back(std::make_tuple(x, y));
   }

   
   void spawn_antibiotics(int amount_of_lines, int amount_of_antibiotics, int antibiotic_energy) {
      std::shuffle(antibiotic_block_coords.begin(), antibiotic_block_coords.end(), std::default_random_engine(0));

      for (int j = 0; j < antibiotic_block_coords.size(); j++) {
         for (int i = 0; i < amount_of_antibiotics; i++) {
            if (number_of_antibiotic < grid.amount_of_antibiotic) return;
            int sx = std::get<0>(antibiotic_block_coords[j]);
            int sy = std::get<1>(antibiotic_block_coords[j]);
            int x = rand() % (width / amount_of_lines) + sx;
            int y = rand() % (height / amount_of_lines) + sy;
            grid.addAntibiotic(x, y, ANTIBIOTIC_SIZE, antibiotic_energy*(-1), sf::Color::White);
         }
      }
   }

};