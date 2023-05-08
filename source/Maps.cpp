#include "Maps.hpp"

Map::Map(GameWorld& gw) : gw(gw), grid(gw.grid) {
}

std::vector<int> Map::createVector(int N) {
    std::vector<int> vec;
    for(int i=1; i<=N; i++) {
        vec.push_back(i);
    }
    return vec;
}


Map1Lines::Map1Lines(GameWorld& gw) : Map(gw) {
}

void Map1Lines::initialize() {
    spawn_food_in_lines(NUMBER_OF_LINES, MAP1_STARTING_FOOD);
    gw.spawn_random_food(MAP1_RAND_STARTING_FOOD);
    //std::cout << gw.grid.amount_of_food << std::endl;
}

void Map1Lines::update() {
    // Update the map
    spawn_food_in_lines(NUMBER_OF_LINES, SPAWN_RATE);
    gw.spawn_random_food(RANDOM_SPAWN_RATE);
}

void Map1Lines::spawn_food_in_lines(int amount_of_lines, int amount_of_food_in_line) { 
    std::vector<int> vec1 = createVector(amount_of_lines);
    std::random_shuffle(vec1.begin(), vec1.end());

    for (int i : vec1) {
        for (int j = 0; j < amount_of_food_in_line; j++) {
            if (NUMBER_OF_FOOD <= grid.amount_of_food) return;
            int x = (WINDOW_WIDTH_GAME / amount_of_lines) * i;
            int y = rand() % WINDOW_HEIGHT_GAME;

            grid.addFood(x, y, FOOD_SIZE, FOOD_ENERGY, sf::Color::Yellow);

            x = rand() % WINDOW_WIDTH_GAME;
            y = (WINDOW_HEIGHT_GAME / amount_of_lines) * i;

            grid.addFood(x, y, FOOD_SIZE, FOOD_ENERGY, sf::Color::Yellow);
        }
    }
}


Map2Rectangle::Map2Rectangle(GameWorld& gw) : Map(gw) {
}

void Map2Rectangle::initialize() {
    spawn_food_in_rectangle(MAP2_STARTING_FOOD);
    gw.spawn_random_food(MAP2_RAND_STARTING_FOOD);
}

void Map2Rectangle::update() {
    // Update the map
    spawn_food_in_rectangle(SPAWN_RATE * MAP2_SPAWN_RATE_MULTIPLIER);
gw.spawn_random_food(RANDOM_SPAWN_RATE);
}

void Map2Rectangle::spawn_food_in_rectangle(int amount_of_food) {
    for (int i = 0; i < amount_of_food; i++) {
        if (NUMBER_OF_FOOD <= grid.amount_of_food) return;
        int x = rand() % (WINDOW_WIDTH_GAME / 2) + WINDOW_WIDTH_GAME / 4;
        int y = rand() % (WINDOW_WIDTH_GAME / 2) + WINDOW_WIDTH_GAME / 4;
         grid.addFood(x, y, FOOD_SIZE, FOOD_ENERGY, sf::Color::Yellow);
    }
}

Map3ThickLine::Map3ThickLine(GameWorld& gw) : Map(gw) {
}

void Map3ThickLine::initialize() {
    spawn_food_in_thick_line(NUMBER_OF_LINES, MAP3_STARTING_FOOD);
    gw.spawn_random_food(MAP3_RAND_STARTING_FOOD);
}

void Map3ThickLine::update() {
    spawn_food_in_thick_line(NUMBER_OF_LINES, SPAWN_RATE*MAP3_SPAWN_RATE_MULTIPLIER);
    gw.spawn_random_food(RANDOM_SPAWN_RATE);
}

void Map3ThickLine::spawn_food_in_thick_line(int amount_of_lines, int amount_of_food) {
    for (int i = 0; i < amount_of_food; i++) {
        if (NUMBER_OF_FOOD <= grid.amount_of_food) return;
        int x = rand() % (WINDOW_WIDTH_GAME / amount_of_lines) + WINDOW_WIDTH_GAME / 2 - WINDOW_WIDTH_GAME / (amount_of_lines * 2);
        int y = rand() % WINDOW_HEIGHT_GAME;   

        grid.addFood(x, y, FOOD_SIZE, FOOD_ENERGY, sf::Color::Yellow);
    }
}

Map4Cross::Map4Cross(GameWorld& gw) : Map(gw) {
}

void Map4Cross::initialize() {
    spawn_food_in_cross(NUMBER_OF_LINES, MAP4_STARTING_FOOD);
    gw.spawn_random_food(MAP4_RAND_STARTING_FOOD);
}

void Map4Cross::update() {
    spawn_food_in_cross(NUMBER_OF_LINES, SPAWN_RATE*MAP4_SPAWN_RATE_MULTIPLIER);
    gw.spawn_random_food(RANDOM_SPAWN_RATE);
}

void Map4Cross::spawn_food_in_cross(int amount_of_lines, int amount_of_food) {
    for (int i = 0; i < amount_of_food; i++) {
        if (NUMBER_OF_FOOD <= grid.amount_of_food) return;
        int x = rand() % (WINDOW_WIDTH_GAME / amount_of_lines) + WINDOW_WIDTH_GAME / 2 - WINDOW_WIDTH_GAME / (amount_of_lines * 2);
        int y = rand() % WINDOW_HEIGHT_GAME;   

        grid.addFood(y, x, FOOD_SIZE, FOOD_ENERGY, sf::Color::Yellow);
        grid.addFood(x, y, FOOD_SIZE, FOOD_ENERGY, sf::Color::Yellow);
    }
}