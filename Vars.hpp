#ifndef VARS_HPP
#define VARS_HPP

extern const int WINDOW_WIDTH_GUI;
extern const int WINDOW_HEIGHT_GUI;

extern const int WINDOW_WIDTH_GAME;
extern const int WINDOW_HEIGHT_GAME;

//default ingame settings
extern int ORGANISM_SIZE;
extern int ORGANISM_SPEED;

extern int ORGANISM_MAX_SIZE;
extern int ORGANISM_MAX_SPEED;

extern int NUMBER_OF_ORGANISMS;
extern int NUMBER_OF_FOOD;
extern int NUMBER_OF_LINES;
extern int NUMBER_OF_ANTIBIOTIC;

extern int ORGANISM_ENERGY;
extern int REPRODUCTION_ENERGY;
extern int FOOD_ENERGY;
extern int RAND_FOOD_ENERGY;
extern int ANTIBIOTIC_ENERGY;
extern int ANTIBIOTIC_SIZE;
extern int FOOD_SIZE;

//default spawnrates
extern int SPAWN_RATE;
extern int RANDOM_SPAWN_RATE;
extern int ANTIBIOTIC_SPAWN_RATE;

extern int GAME_SPEED_MULTIPLIER;

//default map
extern int MAP;

extern int GAME_SPEED;

//grid for reducing computational complexity
extern const int AMOUNT_OF_GRID_CELLS;

//mutation settings
extern int CHANCE_OF_MUTATION;
extern int MUTATION_RATE;

extern float MAX_SIZE_MULTIPLIER;

//map settings - food spawing
extern int MAP1_STARTING_FOOD;
extern int MAP2_STARTING_FOOD;
extern int MAP3_STARTING_FOOD;
extern int MAP4_STARTING_FOOD;

extern int MAP1_RAND_STARTING_FOOD;
extern int MAP2_RAND_STARTING_FOOD;
extern int MAP3_RAND_STARTING_FOOD;
extern int MAP4_RAND_STARTING_FOOD;

extern int MAP2_SPAWN_RATE_MULTIPLIER;
extern int MAP3_SPAWN_RATE_MULTIPLIER;
extern int MAP4_SPAWN_RATE_MULTIPLIER;

void initializeVars();

#endif
