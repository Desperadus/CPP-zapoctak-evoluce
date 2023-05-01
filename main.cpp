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
#include "GameWorld.hpp"
#include "Game.hpp"
#include "Gui.hpp"


extern int NUMBER_OF_ORGANISMS;
extern int ORGANISM_SIZE;
extern int ORGANISM_ENERGY;
extern int GAME_SPEED; // in milliseconds
extern int FOOD_ENERGY;
extern int NUMBER_OF_LINES;
extern int REPRODUCTION_ENERGY;
extern int MAP;
extern const int WINDOW_WIDTH_GAME;
extern const int WINDOW_HEIGHT_GAME;
extern const int WINDOW_WIDTH_STATS;
extern const int WINDOW_HEIGHT_STATS;
extern int NUMBER_OF_FOOD;
extern int NUMBER_OF_ANTIBIOTIC;
extern int MAP1_STARTING_FOOD;
extern int MAP1_RAND_STARTING_FOOD;
extern int MAP2_STARTING_FOOD;
extern int MAP2_RAND_STARTING_FOOD;
extern int MAP3_STARTING_FOOD;
extern int MAP3_RAND_STARTING_FOOD;
extern int MAP4_STARTING_FOOD;
extern int MAP4_RAND_STARTING_FOOD;
extern int SPAWN_RATE;
extern int RANDOM_SPAWN_RATE;
extern int FOOD_SIZE;
extern int ANTIBIOTIC_SIZE;
extern int ANTIBIOTIC_ENERGY;
extern int ANTIBIOTIC_SPAWN_RATE;
extern int ANTIBIOTIC_RANDOM_SPAWN_RATE;

int main()
{
   GameWorld gw(WINDOW_HEIGHT_GAME, WINDOW_WIDTH_GAME, ORGANISM_SIZE, NUMBER_OF_FOOD, NUMBER_OF_ANTIBIOTIC);
   Game game(gw);
   GUI gui(gw, game);

   //Main loop - runs while the game window is open
   while (game.window.isOpen())
   {  
      gui.HandleEvents();
      gui.RenderScene();
      gui.window.display();

      game.HandleEvents(game.window, game.timer);
      game.window.clear();
      game.RenderScene(game.window);
      game.window.display();

      if (game.stats_win_is_open == true) { //If the stats window is open, render it
         game.stats->window.clear();
         game.stats->HandleEvents();
         game.stats->RenderScene();
         game.stats->window.display();
      }
   }

   return 0;
}