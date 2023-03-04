#include <SFML/Graphics.hpp>
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
using namespace std;

//TODO : add posibility of set seed, another maps, gui for settings, make evolution better and faster, Fix keystrokes for speed/slowing the game, add antibiotic
//Linux compile with g++ -c main.cpp && g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system && ./sfml-app


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

class Food{
public:
   int x;
   int y;
   int size;
   int energy;
   int color;
   int id;
   sf::CircleShape shape;
   Food(int x, int y, int size, int energy, int color, int id) {
      this->x = x;
      this->y = y;
      this->size = size;
      this->energy = energy;
      this->color = color;
      this->id = id;
      create_shape();
   }

   void create_shape() {
      shape = sf::CircleShape(size);
      shape.setFillColor(sf::Color::Yellow);
      shape.setPosition(x, y);
   }
};



class Grid {
public:
    int width, height, grid_size;
    std::vector<std::vector<std::vector<shared_ptr<Food> > > > grid;
    size_t amount_of_food = 0;

    Grid(int width, int height, int grid_size) : 
        width(width), height(height), grid_size(grid_size) {
        // Initialize the grid with empty vectors
        grid.resize(height/grid_size, std::vector<std::vector<shared_ptr<Food>>>(width/grid_size));
    }

    void addFood(int x, int y, int size, int energy, int color, int id) {
      int xgrid = x / grid_size;
      int ygrid = y / grid_size;
      //std::cout << x << " " << y << std::endl;
      if (xgrid >= 0 && xgrid < width/grid_size && ygrid >= 0 && ygrid < height/grid_size) {
         grid[ygrid][xgrid].push_back(make_shared<Food>(x, y, size, energy, color, id));
         amount_of_food++;
      }
      else {
         std::cout << x << " " << y << std::endl;
      }
    }
};

class Organism{
public:
   int height;
   int width;

   int x;
   int y;

   int size;
   int speed;

   int energy;
   int color;
   int id;

   int max_size;
   int max_speed;
   int mutation_rate = 3;

   sf::CircleShape shape;

   vector<int> chances;
   Organism(int x, int y, int size, int speed, int energy, int color, int id, vector<int> chances, int height, int width) {
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
      this->max_speed = 10;
      create_shape();
   }

   void create_shape() {
      shape = sf::CircleShape(size);
      shape.setFillColor(sf::Color::Green);
      shape.setPosition(x-size, y-size);
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
         organisms.push_back(make_unique<Organism>(x, y, size, speed, new_energy, color, id, chances, height, width));
         
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
      if (random_number == 0) {
         if (chances[0] > mutation_rate) {
            chances[0] -= mutation_rate;
            chances[rand() % 4] += mutation_rate;
         }
      }
      else if (random_number == 1) {
         if (chances[1] > 0) {
            chances[1] -= 1;
            chances[rand() % 4] += mutation_rate;
         }
      }
      else if (random_number == 2) {
         if (chances[2] > 0) {
            chances[2] -= mutation_rate;
            chances[rand() % 4] += mutation_rate;
         }
      }
      else if (random_number == 3) {
         if (chances[3] > 0) {
            chances[3] -= mutation_rate;
            chances[rand() % 4] += mutation_rate;
         }
      }
      if (random_number == 0 && speed > 1) {
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


class GameWorld{
public:
   int height;
   int width;
   int org_size;
   int grid_size = 50;
   std::vector<unique_ptr<Organism> > organisms;
   Grid grid;
   GameWorld(int height, int width, int org_size) : grid(height, width, grid_size) {
      this->height = height;
      this->width = width;
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
      
         organisms.push_back(make_unique<Organism>(x, y, size, speed, energy, color, id, chances, height, width));
      }

   }

   void spawn_food_in_lines(int amount_of_lines, int amount_of_food_in_line, int food_energy) {
      if (grid.amount_of_food == 0) {
         grid = Grid(height, width, grid_size);
      }
      for (int i = 1; i < amount_of_lines; i++) {
         for (int j = 0; j < amount_of_food_in_line; j++) {
            int x = (width / amount_of_lines) * i;
            int y = rand() % height;

            int size = 2;
            int energy = food_energy;
            int color = rand() % 255;
            int id = i;
            grid.addFood(x, y, size, energy, color, id);


            x = rand() % width;
            y = (height / amount_of_lines) * i;

            size = 2;
            energy = 5;
            color = rand() % 255;
            id = i;
            grid.addFood(x, y, size, energy, color, id);

         }
      }
   }
      
   void spawn_random_food(int amount_of_food, int food_energy) {
      if (grid.amount_of_food == 0) {
         grid = Grid(height, width, grid_size);
      }
      for (int i = 0; i < amount_of_food; i++) {
         int x = rand() % width;
         int y = rand() % height;

         int size = 2;
         int energy = food_energy;
         int color = rand() % 255;
         int id = i;
         grid.addFood(x, y, size, energy, color, id);
      }
   }

   void respawn_food_in_lines(int amount_of_lines, int amount_of_food_in_line, int food_energy, int rate) {
      if (grid.amount_of_food > 5000) {
         return;
      }

      for (int i = 1; i < amount_of_lines; i++) {
         for (int j = 0; j < rate; j++) {
            int x = (width / amount_of_lines) * i;
            int y = rand() % height;

            int size = 2;
            int energy = food_energy;
            int color = rand() % 255;
            int id = i;
            grid.addFood(x, y, size, energy, color, id);


            x = rand() % width;
            y = (height / amount_of_lines) * i;

            size = 2;
            energy = 5;
            color = rand() % 255;
            id = i;
            grid.addFood(x, y, size, energy, color, id);

         }
      }
   }

   void respawn_food_at_random(int rate, int food_energy) {
      if (grid.amount_of_food > 5000) {
         return;
      }

      for (int i = 0; i < rate; i++) {
         int x = rand() % width;
         int y = rand() % height;

         int size = 2;
         int energy = food_energy;
         int color = rand() % 255;
         int id = i;
         grid.addFood(x, y, size, energy, color, id);
      }
   }

};

class GraphicalInterface{
public:

   int height = 1000;
   int width = 1000;
   int amount = 50;
   int org_size = 8;
   int org_energy = 200;
   int game_speed = 10; // in milliseconds
   int food_energy = 5;
   int amount_of_lines = 7;
   int reproduction_energy = 500;
   size_t tick_counter = 0;

   
   GameWorld gw = GameWorld(height, width, org_size);
   sf::RenderWindow window;
   

   void start_game() {
      gw.spawn_organisms(amount, org_energy);
      gw.spawn_food_in_lines(amount_of_lines, 100, food_energy);
      gw.spawn_random_food(500, food_energy);
   }

   void natural_selection() {
      for (int i = 0; i < gw.organisms.size(); i++) {
         if (gw.organisms[i]->energy <= 0) {
            gw.organisms.erase(gw.organisms.begin() + i);
         }
      }
   }

   void game_tick() {
      tick_counter++;
      for (int i = 0; i < gw.organisms.size(); i++) {
         gw.organisms[i]->move();
         gw.organisms[i]->try_to_eat(gw.grid);
         gw.organisms[i]->try_mitosis(gw.organisms, reproduction_energy);
      }
      if (tick_counter % 10 == 0) {
         gw.respawn_food_in_lines(amount_of_lines, 100, food_energy, 7);
         gw.respawn_food_at_random(9, food_energy);
         natural_selection();
      }
   }


   void InitializeWindow() {

      sf::RenderWindow window(sf::VideoMode(width, height), "Evolution game!");

      sf::Clock timer;

      start_game();

      while (window.isOpen())
      {
         sf::Event event;
         while (window.pollEvent(event))
         {
            if (event.type == sf::Event::Closed)
               window.close();
         }

         if (timer.getElapsedTime().asMilliseconds() >= game_speed)
         {
            game_tick();
            timer.restart();
            
         }

         if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
         {
            cout << "Game speed: " << game_speed << endl;
            game_speed -= 3;
            if(game_speed < 1)
               game_speed = 1;
         }
         if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O))
         {
            game_speed += 3;
         }

         window.clear();
         
         for (int i = 0; i < gw.organisms.size(); i++) {
         window.draw(gw.organisms[i]->shape);
         }
         for (int i = 0; i < gw.grid.grid.size(); i++) {
            for (int j = 0; j < gw.grid.grid[i].size(); j++) {
               for (int k = 0; k < gw.grid.grid[i][j].size(); k++) {
                  window.draw(gw.grid.grid[i][j][k]->shape);
               }
            }
         }
         window.display();
      }
   }
};

int main()
{
    GraphicalInterface gui;
    gui.InitializeWindow();
    return 0;
}
