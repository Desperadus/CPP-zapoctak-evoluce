#pragma once

class Game{
public:

   int height = WINDOW_HEIGHT_GAME;
   int width = WINDOW_WIDTH_GAME;
   int& amount = NUMBER_OF_ORGANISMS;
   int& org_size = ORGANISM_SIZE;
   int& org_energy = ORGANISM_ENERGY;
   int& game_speed = GAME_SPEED; // in milliseconds
   int& food_energy = FOOD_ENERGY;
   int& amount_of_lines = NUMBER_OF_LINES;
   int& reproduction_energy = REPRODUCTION_ENERGY;

   bool paused = false;
   bool stats_win_is_open = false;

   int highest_generation = 0;
   size_t tick_counter = 0;
   
   GameWorld& gw;
   std::unique_ptr<Statistics> stats;
   sf::RenderWindow window;
   sf::Clock timer;

   
   Game(GameWorld& gw) : gw(gw), window(sf::VideoMode(WINDOW_WIDTH_GAME, WINDOW_HEIGHT_GAME), "Evolution") {
      start_game();
      //window.setFramerateLimit(60);
   }

   void start_game() const{
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
      if (MAP == 3) {
         gw.spawn_organisms(amount, org_energy);
         gw.spawn_food_in_thick_line(NUMBER_OF_LINES , NUMBER_OF_FOOD / 2, food_energy);
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

   void update_stats(const Organism& org) const {
      if (!stats_win_is_open) return;
      stats->texts[1].text.setString("Number of organisms alive: " + std::to_string(gw.organisms.size()));
      stats->texts[2].text.setString("Number of food: " + std::to_string(gw.grid.amount_of_food));
      stats->bac_stats[0].text.setString(std::to_string(org.size));
      stats->bac_stats[1].text.setString(std::to_string(org.speed));
      stats->bac_stats[2].text.setString(std::to_string(org.chances[0]));
      stats->bac_stats[3].text.setString(std::to_string(org.chances[1]));
      stats->bac_stats[4].text.setString(std::to_string(org.chances[2]));
      stats->bac_stats[5].text.setString(std::to_string(org.chances[3]));
   
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
         if (MAP == 3) {
            gw.spawn_food_in_thick_line(NUMBER_OF_LINES, SPAWN_RATE*10, food_energy);
            gw.spawn_random_food(RANDOM_SPAWN_RATE, food_energy);
         }
         natural_selection();

         if (gw.antibiotic_block_coords.size() > 0) {
            gw.spawn_antibiotics(NUMBER_OF_LINES, ANTIBIOTIC_SPAWN_RATE, ANTIBIOTIC_ENERGY);
         }
      }
   }

   void clear_game() const {
      gw.antibiotic_block_coords.clear();
      gw.organisms.clear();
      gw.grid.grid.clear();
      gw.grid.grid.resize(gw.grid.height/gw.grid.grid_size, std::vector<std::vector<std::shared_ptr<Food>>>(gw.grid.width/gw.grid.grid_size));
      //gw.grid = Grid(width, height, gw.grid_size);
      gw.grid.amount_of_food = 0;
      gw.grid.amount_of_antibiotic = 0;
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
      if (paused) return;

      sf::Event event;
      while (window.pollEvent(event))
      {
         if (event.type == sf::Event::Closed) window.close();
         else if (event.type == sf::Event::MouseButtonPressed) //creates antibiotic block
         {
            gw.create_antibiotic_block(ANTIBIOTIC_ENERGY,event.mouseButton.x, event.mouseButton.y, amount_of_lines);
         }
      }
      
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
      stats = std::make_unique<Statistics>(font);
   }

};
