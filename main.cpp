#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

int sum_of_vector(vector<int> & v) {
   int sum = 0;
   for (int i = 0; i < v.size(); i++) {
      sum += v[i];
   }
   return sum;
}

class Organism{
public:
   int x;
   int y;

   int size;
   int speed;

   int energy;
   int color;
   int id;

   sf::CircleShape shape;

   vector<int> chances = { 0, 0, 0, 0 };
   Organism(int x, int y, int size, int speed, int energy, int color, int id, int chance_to_move_in_x_plus_direction, int chance_to_move_in_x_minus_direction, int chance_to_move_in_y_plus_direction, int chance_to_move_in_y_minus_direction){
      this->x = x;
      this->y = y;
      this->size = size;
      this->speed = speed;
      this->energy = energy;
      this->color = color;
      this->id = id;

      chances[0] = chance_to_move_in_x_plus_direction;
      chances[1] = chance_to_move_in_x_minus_direction;
      chances[2] = chance_to_move_in_y_plus_direction;
      chances[3] = chance_to_move_in_y_minus_direction;

      sf::CircleShape shape(100.f);
      shape.setFillColor(sf::Color::Green);
      shape.setPosition(x, y);

   }

   void move() {
      int random_number = rand() % 100;
      for (int i = 0; i < 4; i++) {
         if (random_number < chances[i]) {
            if (i == 0) {
               x += speed;
               shape.move(speed, 0);
            }
            else if (i == 1) {
               x -= speed;
               shape.move(-speed, 0);
            }
            else if (i == 2) {
               y += speed;
               shape.move(0, speed);
            }
            else if (i == 3) {
               y -= speed;
               shape.move(0, -speed);
            }
            break;
         }
         else {
            random_number -= chances[i];
         }
      }
   }

    
};

class GameWorld{
public:
   std::vector<Organism> organisms;
   
   void spawn_organisms(int amount) {
      for (int i = 0; i < amount; i++) {
         int x = rand() % 1800;
         int y = rand() % 1800;
         int size = rand() % 100;
         int speed = rand() % 10;
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


         
         
         Organism organism(x, y, size, speed, energy, color, id, chances[0], chances[1], chances[2], chances[3]);
         organisms.push_back(organism);
      }
   }

};

class GraphicalInterface{
public:
   int game_speed = 300; // in milliseconds
   GameWorld gw = GameWorld();
   sf::RenderWindow window;

   void start_game() {
      gw.spawn_organisms(10);
   }

   void game_tick() {
      for (int i = 0; i < gw.organisms.size(); i++) {
         gw.organisms[i].move();
      }
   }




   void InitializeWindow() {

      int width = 1800;
      int height = 1800;
      sf::RenderWindow window(sf::VideoMode(width, height), "Evolution game!");

      sf::Clock timer;

      sf::CircleShape shape(5.f);
      shape.setFillColor(sf::Color::Green);
      shape.setPosition(100,100);

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
            shape.move(7, 0);
         }
         window.clear();
         window.draw(shape);
         for(auto &organism : gw.organisms) {
            window.draw(organism.shape);
            //cout << organism.x << " " << organism.y << endl;
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