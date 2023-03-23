#pragma once


using namespace std;

class Organism{
public:
   int height, width;

   int x, y;

   int size, speed;

   int energy, color, id;

   int max_size, max_speed, mutation_rate = 3;

   int generation;

   sf::CircleShape shape;

   vector<int> chances;
   Organism(int x, int y, int size, int speed, int energy, int color, int id, vector<int> chances, int height, int width, int generation = 0) {
      this->x = x;
      this->y = y;
      this->size = size;
      this->speed = speed;
      this->energy = energy;
      this->color = color;
      this->id = id;
      this->height = height;
      this->width = width;

      this->chances = chances;

      this->max_size = size*1.25;
      this->max_speed = max_size;
      this->generation = generation;

      create_shape();
   }

   void create_shape() {
      shape = sf::CircleShape(size);
      shape.setFillColor(sf::Color::Green);
      shape.setPosition(x-size, y-size);
   }

   int sum_of_vector(vector<int> & v) {
        int sum = 0;
        for (int i = 0; i < v.size(); i++) {
            sum += v[i];
        }
        return sum;
    }


    bool distance(int x1, int y1, int x2, int y2, int distance) {
        if (sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)) < distance) {
            return true;
        }
        return false;
    }


   void move() {
      //chances = { 100, 0, 0, 0 };
      energy -= 1;
      int random_number = rand() % 100;
      for (int i = 0; i < 4; i++) {
         if (random_number < chances[i]) {
            if (i == 0) {
               
               if (x < width) 
               {
                  x += speed;
                  shape.move(speed, 0);
               }
               else {
                  x=1;
                  shape.setPosition(1-size, y-size);
               }
            }
            else if (i == 1) {
               
               if (x > 0)
               {
                  x -= speed;
                  shape.move(-speed, 0);
               }
               else {
                  x=width-1;
                  shape.setPosition(width-1-size, y-size);
               }
            }
            else if (i == 2) {
               
               if (y < height)
               {
                  y += speed;
                  shape.move(0, speed);
               }
               else {
                  y=1;
                  shape.setPosition(x-size, 1-size);
               }
            }
            else if (i == 3) {
               
               if (y > 0)
               {
                  y -= speed;
                  shape.move(0, -speed);
               }
               else {
                  y=height-1;
                  shape.setPosition(x-size, height-1-size);
               }
            }
            break;
         }
         else {
            random_number -= chances[i];
         }
      }
   }
   void try_to_eat(Grid & grid) {
      int x = this->x / grid.grid_size;
      int y = this->y / grid.grid_size;
      if (x >= 0 && x < width / grid.grid_size && y >= 0 && y < height / grid.grid_size) {
         for (int i = 0; i < grid.grid[y][x].size(); i++) {
            if (distance(this->x, this->y, grid.grid[y][x][i]->x, grid.grid[y][x][i]->y, this->size)) {
               this->energy += grid.grid[y][x][i]->energy;
               grid.grid[y][x].erase(grid.grid[y][x].begin() + i);
               grid.amount_of_food--;
            }
         }
      }
   }

   void try_mitosis(vector<unique_ptr<Organism> > & organisms, int needed_energy) {
      if (energy > needed_energy) {
         energy -= needed_energy/2;
         int x = this->x;
         int y = this->y;
         int size = this->size;
         int speed = this->speed;
         int new_energy = this->energy/2;
         int color = this->color;
         int id = this->id;
         vector<int> chances = this->chances;
         organisms.push_back(make_unique<Organism>(x, y, size, speed, new_energy, color, id, chances, height, width, generation + 1));
         generation += 1;

         mutate();
         organisms[organisms.size() - 1]->mutate();
      }
   }

   void mutate() {
      int random_number = rand() % 100;
      if (random_number < 90) {
         return;
      }
      random_number = rand() % 4;
      
      for (int i = 0; i < 4; i++) {
         if (chances[i] - mutation_rate >= 0) {
            //cout << "mutate " << chances[i] <<endl;
            chances[i] -= mutation_rate;
            chances[rand() % 4] += mutation_rate;
         }
         else {
            chances[rand() % 4] += mutation_rate - chances[i];
            chances[i] = 0;
         }
      }

      if (random_number == 0 && speed > 1) {
         //cout << "mutate speed" << endl;
         int rand2 = rand() % 2;
         if (rand2 == 0) {
            speed -= 1;
            if (speed < 1) {
               speed = 1;
            }
         }
         if (rand2 == 1 && speed < max_speed) {
            speed+=1;
            if (speed > size && size < max_size) {
               size +=1;
               shape = sf::CircleShape(size);
            }
         }
      }
   }
      
      
};