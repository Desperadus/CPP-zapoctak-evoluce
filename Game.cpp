#include "Game.hpp"

Game::Game(GameWorld& gw) : gw(gw), window(sf::VideoMode(WINDOW_WIDTH_GAME, WINDOW_HEIGHT_GAME), "Evolution") {
      start_game();
      //window.setFramerateLimit(60);
}

void Game::start_game() {
// Initialize maps
    maps.push_back(std::make_unique<Map1Lines>(gw));
    maps.push_back(std::make_unique<Map2Rectangle>(gw));
    maps.push_back(std::make_unique<Map3ThickLine>(gw));
    maps.push_back(std::make_unique<Map4Cross>(gw));
    // Spawn organisms
    gw.spawn_organisms(amount, org_energy);

    // Initialize the map
    test_if_map_exists();
    maps[MAP-1]->initialize();
}

void Game::natural_selection() {
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
            gw.organisms[i]->shape.setFillColor(sf::Color::Blue);
            updated = true;
        }
    }
}

void Game::update_stats(const Organism& org) const {
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

void Game::test_if_map_exists() {
    if (MAP-1 >= maps.size()) {
        std::cout << "Map does not exist, switching to MAP 1" << std::endl;
        MAP = 1;
        return;
    }
}

void Game::game_tick() {
    if (paused) return;
    tick_counter++;
    for (int i = 0; i < gw.organisms.size(); i++) {
        gw.organisms[i]->move();
        gw.organisms[i]->try_to_eat(gw.grid);
        gw.organisms[i]->try_mitosis(gw.organisms, reproduction_energy);
    }
    if (tick_counter % 10 == 0) {
        test_if_map_exists();
        maps[MAP-1]->update();
        natural_selection();
    if (gw.antibiotic_block_coords.size() > 0) {
            gw.spawn_antibiotics(NUMBER_OF_LINES, ANTIBIOTIC_SPAWN_RATE, ANTIBIOTIC_ENERGY);
        }
    }
}


void Game::clear_game() const {
    gw.antibiotic_block_coords.clear();
    gw.organisms.clear();
    gw.grid.grid.clear();
    gw.grid.grid.resize(gw.grid.height/gw.grid.grid_size, std::vector<std::vector<std::shared_ptr<Food>>>(gw.grid.width/gw.grid.grid_size));
    gw.grid.amount_of_food = 0;
    gw.grid.amount_of_antibiotic = 0;
}

void Game::pause_game() {
    if (paused) {
        paused = false;
    }
    else {
        paused = true;
    }
}

void Game::RenderScene(sf::RenderWindow& window) {
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

void Game::HandleEvents(sf::RenderWindow& window, sf::Clock& timer) {
    if (paused) return;

    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) window.close();
        else if (event.type == sf::Event::MouseButtonPressed) //creates antibiotic block
        {
            gw.create_antibiotic_block(ANTIBIOTIC_ENERGY,event.mouseButton.x, event.mouseButton.y, amount_of_lines);
        }
        else if (event.Resized) {
            // sf::Vector2u size = window.getSize();
            // std::cout << "Resized, might not fit screen correctly. Size x-" << size.x <<" y-" << size.y << std::endl;
            // WINDOW_WIDTH_GAME = size.x;
            // WINDOW_HEIGHT_GAME = size.y;
            // gw.grid.new_gird();
            // maps[MAP-1]->initialize();
        }
    }

    if (timer.getElapsedTime().asMilliseconds() >= game_speed)
    {
        game_tick();
        timer.restart();

    }
}

void Game::InitializeWindow() {
    start_game();
    window.create(sf::VideoMode(WINDOW_WIDTH_GAME, WINDOW_HEIGHT_GAME), "Evolution game!");
}


void Game::draw_stats(const sf::Font& font) {
    stats_win_is_open = true;
    stats = std::make_unique<Statistics>(font);
}