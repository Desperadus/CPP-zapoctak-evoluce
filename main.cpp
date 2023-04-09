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

using namespace std;

//Linux compile with:
// g++ -c main.cpp && g++ main.o -o game -lsfml-graphics -lsfml-window -lsfml-system && ./game




int main()
{
   GameWorld gw(WINDOW_HEIGHT_GAME, WINDOW_WIDTH_GAME, ORGANISM_SIZE, NUMBER_OF_FOOD, NUMBER_OF_ANTIBIOTIC);
   Game game(gw);
   //game.InitializeWindow();
   GUI gui(gw, game);


   //cout << window2.isOpen() << endl;
   while (gui.window.isOpen() || game.window.isOpen())
   {  
      if (game.window.isOpen() == false)
         break;
      gui.HandleEvents();
      gui.RenderScene();
      gui.window.display();

      game.HandleEvents(game.window, game.timer);
      game.window.clear();
      game.RenderScene(game.window);
      game.window.display();

      if (game.stats_win_is_open == true) {
         game.stats->window.clear();
         game.stats->HandleEvents();
         game.stats->RenderScene();
         game.stats->window.display();
      }
   }

   return 0;
}