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


#include "Constants.hpp"
#include "Food.hpp"
#include "Grid.hpp"
#include "Organism.hpp"
#include "GameWorld.hpp"
#include "Stats.hpp"
#include "Game.hpp"
#include "Gui.hpp"
#include "Maps.hpp"


//Linux compile with:
// g++ -c main.cpp && g++ main.o -o game -lsfml-graphics -lsfml-window -lsfml-system && ./game

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