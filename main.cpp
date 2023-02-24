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


bool distance(int x1, int y1, int x2, int y2, int distance) {
   if (abs(x1 - x2) < distance && abs(y1 - y2) < distance) {
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
               
               if (x > 0 && x < width && y > 0 && y < height) 
               {
                  x += speed;
                  shape.move(speed, 0);
               }
               else {
                  x=1;
                  shape.setPosition(1, y);
               }
            }
            else if (i == 1) {
               
               if (x > 0 && x < width && y > 0 && y < height)
               {
                  x -= speed;
                  shape.move(-speed, 0);
               }
               else {
                  x=width-1;
                  shape.setPosition(width-1, y);
               }
            }
            else if (i == 2) {
               
               if (x > 0 && x < width && y > 0 && y < height)
               {
                  y += speed;
                  shape.move(0, speed);
               }
               else {
                  y=1;
                  shape.setPosition(x, 1);
               }
            }
            else if (i == 3) {
               
               if (x > 0 && x < width && y > 0 && y < height)
               {
                  y -= speed;
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
   void try_to_eat(Grid & grid) {
      int x = this->x / grid.grid_size;
      int y = this->y / grid.grid_size;
      if (x >= 0 && x < width / grid.grid_size && y >= 0 && y < height / grid.grid_size) {
         for (int i = 0; i < grid.grid[y][x].size(); i++) {
            if (distance(this->x, this->y, grid.grid[y][x][i].x, grid.grid[y][x][i].y, size*2)) {
               this->energy += grid.grid[y][x][i].energy;
               grid.grid[y][x].erase(grid.grid[y][x].begin() + i);
               break;
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
   int grid_size = 23;
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
         int speed = rand() % org_size;
         if (speed < 1) {
            speed = 1;
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
   int game_speed = 10; // in milliseconds
   size_t tick_counter = 0;

   
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
         gw.organisms[i].try_to_eat(gw.grid);
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