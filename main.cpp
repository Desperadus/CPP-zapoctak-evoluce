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
using namespace std;

//TODO : add posibility of set seed

int sum_of_vector(vector<int> & v) {
   int sum = 0;
   for (int i = 0; i < v.size(); i++) {
      sum += v[i];
   }
   return sum;
}

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

      create_shape();
   }

   void create_shape() {
      shape = sf::CircleShape(size);
      shape.setFillColor(sf::Color::Green);
      shape.setPosition(x, y);
   }

   void move() {
      //chances = { 100, 0, 0, 0 };
      int random_number = rand() % 100;
      for (int i = 0; i < 4; i++) {
         if (random_number < chances[i]) {
            if (i == 0) {
               x += speed;
               if (x > 0 && x < width && y > 0 && y < height) 
               {
                  shape.move(speed, 0);
               }
               else {
                  x=1;
                  shape.setPosition(1, y);
               }
            }
            else if (i == 1) {
               x -= speed;
               if (x > 0 && x < width && y > 0 && y < height)
               {
                  shape.move(-speed, 0);
               }
               else {
                  x=width-1;
                  shape.setPosition(width-1, y);
               }
            }
            else if (i == 2) {
               y += speed;
               if (x > 0 && x < width && y > 0 && y < height)
               {
                  shape.move(0, speed);
               }
               else {
                  y=1;
                  shape.setPosition(x, 1);
               }
            }
            else if (i == 3) {
               y -= speed;
               if (x > 0 && x < width && y > 0 && y < height)
               {
                  shape.move(0, -speed);
               }
               else {
                  y=height-1;
                  shape.setPosition(x, height-1);
               }
            }
            break;
         }
         else {
            random_number -= chances[i];
         }
      }
   }

    
};


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
    std::vector<std::vector<std::vector<Food>>> grid;

    Grid(int width, int height, int grid_size) : 
        width(width), height(height), grid_size(grid_size) {
        // Initialize the grid with empty vectors
        grid.resize(height/grid_size, std::vector<std::vector<Food>>(width/grid_size));
    }

    void addFood(const Food& food) {
        int x = food.x / grid_size;
        int y = food.y / grid_size;

        if (x >= 0 && x < width/grid_size && y >= 0 && y < height/grid_size) {
            grid[y][x].push_back(food);
        }
    }
};

class GameWorld{
public:
   int height;
   int width;
   int org_size;
   int grid_size = 10;
   std::vector<Organism> organisms;
   Grid grid;
   GameWorld(int height, int width, int org_size) : grid(height, width, grid_size) {
      this->height = height;
      this->width = width;
      this->org_size = org_size;
   }
   void spawn_organisms(int amount) {
      srand((unsigned) time(NULL));
      for (int i = 0; i < amount; i++) {
         int x = rand() % width;
         int y = rand() % height;
         int size = org_size;
         int speed = rand() % 20;
         if (speed < 5) {
            speed = 5;
         }

         int energy = 100;
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
      
         Organism organism(x, y, size, speed, energy, color, id, chances, height, width);
         organisms.push_back(organism);
      }

   }

   void spawn_food_in_lines(int amount_of_lines, int amount_of_food_in_line) {
      grid = Grid(width, height, grid_size);
      for (int i = 1; i < amount_of_lines; i++) {
         for (int j = 0; j < amount_of_food_in_line; j++) {
            int x = (width / amount_of_lines) * i;
            int y = rand() % height;

            int size = 2;
            int energy = 5;
            int color = rand() % 255;
            int id = i;
            grid.addFood(Food(x, y, size, energy, color, id));


            x = rand() % width;
            y = (height / amount_of_lines) * i;

            size = 2;
            energy = 5;
            color = rand() % 255;
            id = i;
            grid.addFood(Food(x, y, size, energy, color, id));

         }
      }
      
   }

};

class GraphicalInterface{
public:

   int height = 1800;
   int width = 1800;
   int amount = 50;
   int org_size = 10;
   size_t tick_counter = 0;

   int game_speed = 30; // in milliseconds
   GameWorld gw = GameWorld(height, width, org_size);
   sf::RenderWindow window;

   void start_game() {
      gw.spawn_organisms(amount);
      gw.spawn_food_in_lines(10, 100);
   }

   void game_tick() {
      tick_counter++;
      for (int i = 0; i < gw.organisms.size(); i++) {
         gw.organisms[i].move();
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
         window.clear();
         
         for (int i = 0; i < gw.organisms.size(); i++) {
         window.draw(gw.organisms[i].shape);
         }
         for (int i = 0; i < gw.grid.grid.size(); i++) {
            for (int j = 0; j < gw.grid.grid[i].size(); j++) {
               for (int k = 0; k < gw.grid.grid[i][j].size(); k++) {
                  window.draw(gw.grid.grid[i][j][k].shape);
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