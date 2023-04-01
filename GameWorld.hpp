#pragma once

using namespace std;

class GameWorld{
public:
   int& height;
   int& width;
   int& org_size;
   int grid_size = 66;
   int& number_of_food;
   int& number_of_antibiotic;
   bool adding_antibiotics = false;
   std::vector<unique_ptr<Organism> > organisms;
   std::vector<std::tuple <int, int > > antibiotic_block_coords;

   Grid grid;
   GameWorld(int& height, int& width, int& org_size, int& number_of_food, int& number_of_antibiotic) : grid(height, width, grid_size), height(height), width(width), org_size(org_size), number_of_food(number_of_food), number_of_antibiotic(number_of_antibiotic) {
      this->height = height;
      this->width = width;
      this->org_size = org_size;
   }

    int sum_of_vector(vector<int> & v) {
        int sum = 0;
        for (int i = 0; i < v.size(); i++) {
            sum += v[i];
        }
        return sum;
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

         int color = rand() % 255;
         int id = i;
         
         vector<int> chances = { 0, 0, 0, 0 };
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
         organisms.push_back(make_unique<Organism>(x, y, size, speed, energy, color, id, chances, height, width, size*1.5, 0));
         //break;
      }

   }

   void spawn_food_in_lines(int amount_of_lines, int amount_of_food_in_line, int food_energy) {    
      for (int i = 1; i < amount_of_lines; i++) {
         for (int j = 0; j < amount_of_food_in_line; j++) {
            if (number_of_food < grid.amount_of_food) return;
            int x = (width / amount_of_lines) * i;
            int y = rand() % height;

            int size = 2;
            int energy = food_energy;
            int id = i;
            grid.addFood(x, y, size, energy, id, sf::Color::Yellow);


            x = rand() % width;
            y = (height / amount_of_lines) * i;

            size = 2;
            energy = 5;
            id = i;
            grid.addFood(x, y, size, energy, id, sf::Color::Yellow);

            }
      }
   }
      
   void spawn_random_food(int amount_of_food, int food_energy) {
        for (int i = 0; i < amount_of_food; i++) {
            if (number_of_food < grid.amount_of_food) return;
            int x = rand() % width;
            int y = rand() % height;

            int size = 2;
            int energy = food_energy;
            int color = rand() % 255;
            int id = i;
            grid.addFood(x, y, size, energy, id, sf::Color::Yellow);
        }
   }

   void spawn_food_in_rectangle(int amout_of_food, int food_energy) {
        for (int i = 0; i < amout_of_food; i++) {
            if (number_of_food < grid.amount_of_food) return;
               int x = rand() % (width / 2) + width / 4;
               int y = rand() % (height / 2) + height / 4;

               int size = 2;
               int energy = food_energy;
               int color = rand() % 255;
               int id = i;
               grid.addFood(x, y, size, energy, id, sf::Color::Yellow);
        }
   }

   void spawn_food_in_thick_line(int amount_of_lines, int amount_of_food, int food_energy) {
         for (int i = 0; i < amount_of_food; i++) {
            if (number_of_food < grid.amount_of_food) return;
               int x = rand() % (width / amount_of_lines) + width / 2 - width / (amount_of_lines * 2);
               int y = rand() % height;

               int size = 2;
               int energy = food_energy;
               int color = rand() % 255;
               int id = i;
               grid.addFood(x, y, size, energy, id, sf::Color::Yellow);
        }
   }

   void create_antibiotic_block(int antibiotic_energy, int click_x, int click_y, int amount_of_lines) {
      if (adding_antibiotics == false) return;
      int x = (click_x / (width / amount_of_lines)) * (width / amount_of_lines);
      int y = (click_y / (height / amount_of_lines)) * (height / amount_of_lines);
      
      antibiotic_block_coords.push_back(make_tuple(x, y));
      
   }

   void spawn_antibiotics(int amount_of_lines, int amount_of_antibiotics, int antibiotic_energy) {
      std::shuffle(antibiotic_block_coords.begin(), antibiotic_block_coords.end(), std::default_random_engine(0));

      for (int j = 0; j < antibiotic_block_coords.size(); j++) {
         for (int i = 0; i < amount_of_antibiotics; i++) {
            if (number_of_antibiotic < grid.amount_of_antibiotic) return;
            int sx = get<0>(antibiotic_block_coords[j]);
            int sy = get<1>(antibiotic_block_coords[j]);
            int x = rand() % (width / amount_of_lines) + sx;
            int y = rand() % (height / amount_of_lines) + sy;
            int size = 2;
            int energy = antibiotic_energy;
            int id = i;
            grid.addAntibiotic(x, y, size, energy, id, sf::Color::White);
         }
      }
   }

};