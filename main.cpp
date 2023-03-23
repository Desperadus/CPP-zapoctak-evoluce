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

#include "Food.hpp"
#include "Grid.hpp"
#include "Organism.hpp"
#include "GameWorld.hpp"



using namespace std;

//TODO : add posibility of set seed, another maps, gui for settings, make evolution better and faster, Fix keystrokes for speed/slowing the game, add antibiotic
//Linux compile with:
// g++ -c main.cpp && g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system && ./sfml-app

int WINDOW_WIDTH_GUI = 800;
int WINDOW_HEIGHT_GUI = 600;

int WINDOW_WIDTH_GAME = 1000;
int WINDOW_HEIGHT_GAME = 1000;

int ORGANISM_SIZE = 8;
int ORGANISM_SPEED = 1;

int ORGANISM_MAX_SIZE = 10;
int ORGANISM_MAX_SPEED = 10;

int NUMBER_OF_ORGANISMS = 50;
int NUMBER_OF_FOOD = 5500;
int NUMBER_OF_LINES = 7;

int ORGANISM_ENERGY = 200;
int REPRODUCTION_ENERGY = 300;
int FOOD_ENERGY = 5;

int SPAWN_RATE = 20;
int RANDOM_SPAWN_RATE = 7;

int MAP = 1;



class Text {
public:
    sf::Text text;
    sf::Font& font;
    Text(sf::Font& font, std::string txt, int x, int y, int font_size, sf::Color color) : font(font) {
      text.setFont(font);
      text.setCharacterSize(font_size);
      text.setFillColor(color);
      text.setPosition(x, y);
      text.setString(txt);
    }
    void draw(sf::RenderWindow& window) {
      window.draw(text);
    }
};

class Statistics {
public:
   sf::RenderWindow window;
   sf::Font& font;

   std::vector<Text> texts;
   std::vector<Text> bac_stats; 


   Statistics(sf::Font& font) : font(font) {
      window.create(sf::VideoMode(500, 250), "Statistics");
      
      texts.emplace_back(font, "Statistics:", 10, 10, 24, sf::Color::Green);
      texts.emplace_back(font, "Number of organisms alive: ", 10, 40, 14, sf::Color::White);
      texts.emplace_back(font, "Number of food: ", 10, 60, 14, sf::Color::White);
      texts.emplace_back(font, "Most successful bacteria stats: ", 10, 100, 14, sf::Color::Cyan);
      texts.emplace_back(font, "Size: ", 10, 120, 14, sf::Color::White);
      texts.emplace_back(font, "Speed: ", 10, 140, 14, sf::Color::White);
      texts.emplace_back(font, "Chance of moving in right direction: ", 10, 160, 14, sf::Color::White);
      texts.emplace_back(font, "Chance of moving in left direction: ", 10, 180, 14, sf::Color::White);
      texts.emplace_back(font, "Chance of moving in down direction: ", 10, 200, 14, sf::Color::White);
      texts.emplace_back(font, "Chance of moving in up direction: ", 10, 220, 14, sf::Color::White);

      bac_stats.emplace_back(font, "0", 80, 120, 14, sf::Color::White);
      bac_stats.emplace_back(font, "0", 80, 140, 14, sf::Color::White);
      bac_stats.emplace_back(font, "0", 320, 160, 14, sf::Color::White);
      bac_stats.emplace_back(font, "0", 320, 180, 14, sf::Color::White);
      bac_stats.emplace_back(font, "0", 320, 200, 14, sf::Color::White);
      bac_stats.emplace_back(font, "0", 320, 220, 14, sf::Color::White);



   }

   void HandleEvents() {
   sf::Event event;
   while (window.pollEvent(event))
   {
      if (event.type == sf::Event::Closed)
      {
         window.close();
      }

   }
   }

   void RenderScene() {
      for (auto && text : texts) {
         text.draw(window);
      }
      for (auto && bac_stat : bac_stats) {
         bac_stat.draw(window);
      }
   }




};


class Game{
public:

   int height = WINDOW_HEIGHT_GAME;
   int width = WINDOW_WIDTH_GAME;
   int& amount = NUMBER_OF_ORGANISMS;
   int& org_size = ORGANISM_SIZE;
   int& org_energy = ORGANISM_ENERGY;
   int game_speed = 32; // in milliseconds
   int& food_energy = FOOD_ENERGY;
   int& amount_of_lines = NUMBER_OF_LINES;
   int& reproduction_energy = REPRODUCTION_ENERGY;

   bool paused = false;
   bool stats_win_is_open = false;

   int highest_generation = 0;

   size_t tick_counter = 0;

   
   GameWorld& gw;
   unique_ptr<Statistics> stats;
   sf::RenderWindow window;
   sf::Clock timer;


   
   Game(GameWorld& gw) : gw(gw), window(sf::VideoMode(WINDOW_WIDTH_GAME, WINDOW_HEIGHT_GAME), "Evolution") {
      start_game();
      //window.setFramerateLimit(60);
   }



   void start_game() {
      if (MAP == 1) {
         gw.spawn_organisms(amount, org_energy);
         gw.spawn_food_in_lines(amount_of_lines, NUMBER_OF_FOOD / NUMBER_OF_LINES / 3, food_energy);
         gw.spawn_random_food(NUMBER_OF_FOOD / NUMBER_OF_LINES / 6, food_energy);
      }
      if (MAP == 2) {
         //SPAWN_RATE = 100;
         gw.spawn_organisms(amount, org_energy);
         gw.spawn_food_in_rectangle(NUMBER_OF_FOOD / 2, food_energy);
         gw.spawn_random_food(NUMBER_OF_FOOD / 3, food_energy);
      }
   }

   void natural_selection() {
      highest_generation = 0;
      bool updated = false;
      for (int i = 0; i < gw.organisms.size(); i++) {
         if (gw.organisms[i]->generation > highest_generation) {
            highest_generation = gw.organisms[i]->generation;
         }

         if (gw.organisms[i]->energy <= 0) {
            gw.organisms.erase(gw.organisms.begin() + i);
         }
      }

      for (int i = 0; i < gw.organisms.size(); i++) {
         gw.organisms[i]->shape.setFillColor(sf::Color::Green);
         if (gw.organisms[i]->generation == highest_generation) {
            gw.organisms[i]->shape.setFillColor(sf::Color::Red);
         }
         if (!updated) {
            update_stats(*gw.organisms[i]);
            updated = true;
         }

      }
   }

   void update_stats(Organism& org) {
      if (!stats_win_is_open) return;
      stats->texts[1].text.setString("Number of organisms alive: " + to_string(gw.organisms.size()));
      stats->texts[2].text.setString("Number of food: " + to_string(gw.grid.amount_of_food));
      stats->bac_stats[0].text.setString(to_string(org.size));
      stats->bac_stats[1].text.setString(to_string(org.speed));
      stats->bac_stats[2].text.setString(to_string(org.chances[0]));
      stats->bac_stats[3].text.setString(to_string(org.chances[1]));
      stats->bac_stats[4].text.setString(to_string(org.chances[2]));
      stats->bac_stats[5].text.setString(to_string(org.chances[3]));
   
   }

   void game_tick() {
      if (paused) return;
      tick_counter++;
      for (int i = 0; i < gw.organisms.size(); i++) {
         gw.organisms[i]->move();
         gw.organisms[i]->try_to_eat(gw.grid);
         gw.organisms[i]->try_mitosis(gw.organisms, reproduction_energy);
      }
      if (tick_counter % 10 == 0) {
         
         if (MAP == 1) {
            gw.spawn_food_in_lines(amount_of_lines, SPAWN_RATE, food_energy);
            gw.spawn_random_food(RANDOM_SPAWN_RATE, food_energy);
         }
         
         if (MAP == 2) {
            gw.spawn_food_in_rectangle(SPAWN_RATE*10, food_energy);
            gw.spawn_random_food(RANDOM_SPAWN_RATE, food_energy);
         }
         natural_selection();
      }
   }

   void clear_game() {
      gw.organisms.clear();
      gw.grid.grid.clear();
      gw.grid.grid.resize(gw.grid.height/gw.grid.grid_size, std::vector<std::vector<shared_ptr<Food>>>(gw.grid.width/gw.grid.grid_size));
      //gw.grid = Grid(width, height, gw.grid_size);
      gw.grid.amount_of_food = 0;
   }

   void pause_game() {
      if (paused) {
         paused = false;
      }
      else {
         paused = true;
      }
   }

   void RenderScene(sf::RenderWindow& window) {
      //draws organisms
      for (int i = 0; i < gw.organisms.size(); i++) {
         window.draw(gw.organisms[i]->shape);
      }
      //draws food
      for (int i = 0; i < gw.grid.grid.size(); i++) {
         for (int j = 0; j < gw.grid.grid[i].size(); j++) {
            for (int k = 0; k < gw.grid.grid[i][j].size(); k++) {
               window.draw(gw.grid.grid[i][j][k]->shape);
            }
         }
      }
   }

   void HandleEvents(sf::RenderWindow& window, sf::Clock& timer) {
      sf::Event event;
      while (window.pollEvent(event))
      {
         if (event.type == sf::Event::Closed)
            window.close();
      }
      if (paused) return;
      
      if (timer.getElapsedTime().asMilliseconds() >= game_speed)
      {
         game_tick();
         timer.restart();
         
      }
   }


   void InitializeWindow() {
      
      start_game();
      window.create(sf::VideoMode(width, height), "Evolution game!");

   }

   void draw_stats(sf::Font& font) {
      stats_win_is_open = true;
      stats = make_unique<Statistics>(font);
   }

};



class Button {
public:
   sf::RectangleShape shape;
   sf::Text text;
   sf::Font& font;
   sf::Color idleColor;
   sf::Color hoverColor;
   sf::Color activeColor;
   int id;

   GameWorld& gw;
   Game& game;
   //unique_ptr<Statistics> stats;

   Button(float x, float y, float width, float height,
      sf::Font& font, const std::string text, sf::Color Color, GameWorld& gw, Game& game, int id) : font(font), gw(gw), game(game)
   {
      this->shape.setPosition(sf::Vector2f(x, y));
      this->shape.setSize(sf::Vector2f(width, height));
      this->shape.setFillColor(Color);

      this->font = font;
      this->text.setFont(this->font);
      this->text.setString(text);
      this->text.setFillColor(sf::Color::Black);
      this->text.setCharacterSize(20);
      this->text.setPosition(
         this->shape.getPosition().x + this->shape.getGlobalBounds().width / 2.f - this->text.getGlobalBounds().width / 2.f,
         this->shape.getPosition().y + this->shape.getGlobalBounds().height / 2.f - this->text.getGlobalBounds().height / 2.f
      );
      this->id = id;

   }

   void draw(sf::RenderWindow& window) const
   {
      window.draw(shape);
      window.draw(text);
   }

   void handleEvent(sf::Event event, sf::RenderWindow& window)
   {
      if (event.type == sf::Event::MouseButtonPressed)
      {
         // Check if the mouse click is inside the text box
         sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
         sf::FloatRect bounds = shape.getGlobalBounds();
         if (bounds.contains(mousePosition))
         {
            //cout << id;
            if (id == 0) {
               game.clear_game();
               game.start_game();
               return;
            }
            if (id == 1) {
               game.pause_game();
            }
            if (id == 2) {
               gw.spawn_organisms(NUMBER_OF_ORGANISMS, ORGANISM_ENERGY);
            }
            if (id == 3) {
               game.game_speed /= 4;
            }
            if (id == 4) {
               game.game_speed *= 4;
               if (game.game_speed < 1)
                  game.game_speed = 1;
            }
            if (id == 5) {
               game.draw_stats(font);
            }
         }
      }
   }

};



class InputBox
{
public:
   string value;
   int& asociated_var;
   
   InputBox(const std::string& label, sf::Font& font, sf::Vector2f position, int offset, int& asociated_var) : asociated_var(asociated_var)
   {  
      // Create label
      m_label.setFont(font);
      m_label.setString(label);
      m_label.setCharacterSize(16);
      m_label.setFillColor(sf::Color::White);
      m_label.setPosition(position);

      // Create text box
      m_textBox.setSize(sf::Vector2f(120, 20));
      m_textBox.setOutlineThickness(2.f);
      m_textBox.setOutlineColor(sf::Color::Green);
      m_textBox.setPosition(position + sf::Vector2f(offset, 0));

      // Create text object
      m_text.setFont(font);
      m_text.setString(to_string(asociated_var));
      m_text.setCharacterSize(16);
      m_text.setFillColor(sf::Color::Black);
      m_text.setPosition(position + sf::Vector2f(offset + 3, 2));

   }

   void draw(sf::RenderWindow& window) const
   {
      window.draw(m_label);
      window.draw(m_textBox);
      window.draw(m_text);
   }

   void handleEvent(sf::Event event, sf::RenderWindow& window)
   {
      if (event.type == sf::Event::MouseButtonPressed)
      {
         // Check if the mouse click is inside the text box
         sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
         sf::FloatRect bounds = m_textBox.getGlobalBounds();
         if (bounds.contains(mousePosition))
         {
               isSelected = true;
         }
         else
         {
               isSelected = false;
         }
      }
      else if (event.type == sf::Event::TextEntered && isSelected)
      {   
         //cout << "event.text.unicode: " << event.text.unicode << endl; 
         if (event.text.unicode == 8) // Backspace
         {     
               m_textBox.setOutlineColor(sf::Color::Red);
               if(m_input.size() == 0) {
                  m_text.setString("");
               }  

               if (m_input.size() > 0)
               {
                  m_input.pop_back();
                  m_text.setString(m_input);
               }
         }
         else if (event.text.unicode < 128 && event.text.unicode != 13)
         {     
               m_textBox.setOutlineColor(sf::Color::Red);
               m_input += static_cast<char>(event.text.unicode);
               m_text.setString(m_input);
         }
         else if (event.text.unicode == 13) // Enter
         {     
               m_textBox.setOutlineColor(sf::Color::Green);
               isSelected = false;
               m_text.setString(m_input);
               try {
                  asociated_var = stoi(m_input);
               }
               catch (const std::exception& e) {
                  cout << "Invalid input" << endl;
               }
         }
         
      }
    }

private:
    std::string m_input;
    sf::Text m_label;
    sf::RectangleShape m_textBox;
    sf::Text m_text;
    bool isSelected = false;
};




class GUI {
public:
   sf::RenderWindow window;
   std::vector<InputBox> inputBoxes;
   std::vector<Button> buttons;
   sf::Font font;
   GameWorld& gw;
   Game& game;

   GUI(GameWorld& gw, Game& game) : gw(gw), game(game) {
      // Create window
      window.create(sf::VideoMode(WINDOW_WIDTH_GUI, WINDOW_HEIGHT_GUI), "SFML Input Boxes");

      // Load font
      
      if (!font.loadFromFile("ariblk.ttf"))
      {
         exit(EXIT_FAILURE);
      }

      // Create input boxes
      inputBoxes.emplace_back("Map: (1,2,3)", font, sf::Vector2f(10, 50), 170, MAP);
      inputBoxes.emplace_back("Number of lines:", font, sf::Vector2f(10, 100), 170, NUMBER_OF_LINES);
      inputBoxes.emplace_back("Organism size:", font, sf::Vector2f(10, 150), 170, ORGANISM_SIZE);
      inputBoxes.emplace_back("Reroduction E:", font, sf::Vector2f(10, 200), 170, REPRODUCTION_ENERGY);
      inputBoxes.emplace_back("Spawn rate:", font, sf::Vector2f(10, 250), 170, SPAWN_RATE);
      inputBoxes.emplace_back("Rand spawn rate:", font, sf::Vector2f(10, 300), 170, RANDOM_SPAWN_RATE);
      inputBoxes.emplace_back("Number of org:", font, sf::Vector2f(10, 350), 170, NUMBER_OF_ORGANISMS);
      inputBoxes.emplace_back("Food energy:", font, sf::Vector2f(10, 400), 170, FOOD_ENERGY);
      inputBoxes.emplace_back("Max num of food:", font, sf::Vector2f(10, 450), 170, NUMBER_OF_FOOD);

      // Create buttons
      buttons.emplace_back(550, 36, 100, 50, font, "Start", sf::Color::Green, gw, game, 0);
      buttons.emplace_back(550, 100, 170, 50, font, "Pause/Resume", sf::Color::Cyan, gw, game, 1);
      buttons.emplace_back(550, 164, 170, 50, font, "Add organisms", sf::Color::Green, gw, game, 2);
      buttons.emplace_back(550, 334, 170, 50, font, "Speed up", sf::Color::Green, gw, game, 3);
      buttons.emplace_back(550, 390, 170, 50, font, "Slow down", sf::Color::Red, gw, game, 4);
      buttons.emplace_back(550, 500, 170, 50, font, "Show stats", sf::Color::Cyan, gw, game, 5);



   }

   void HandleEvents() {
      // Handle events
         sf::Event event;
         while (window.pollEvent(event))
         {
               if (event.type == sf::Event::Closed)
               {
                  window.close();
               }
               else if (event.type == sf::Event::TextEntered || event.type == sf::Event::MouseButtonPressed)
               {   
                  for (auto & inputBox : inputBoxes)
                  {
                     inputBox.handleEvent(event, window);
                  }
                  for (auto & button : buttons)
                  {
                     button.handleEvent(event, window);
                  }
               }
         }
   }

   void RenderScene() {
      // Draw input boxes
      window.clear(sf::Color::Black);
      for (const auto & inputBox : inputBoxes)
      {
         inputBox.draw(window);
      }
      for (const auto & button : buttons)
      {
         button.draw(window);
      }
   }
};






int main()
{
   GameWorld gw(WINDOW_HEIGHT_GAME, WINDOW_WIDTH_GAME, ORGANISM_SIZE, NUMBER_OF_FOOD);
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