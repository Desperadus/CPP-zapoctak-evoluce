#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Food.hpp"

class Grid {
public:
    const int width, height;
    int grid_size;
    std::vector<std::vector<std::vector<std::shared_ptr<Food> > > > grid;
    size_t amount_of_food = 0;
    size_t amount_of_antibiotic = 0;

    Grid(const int width, const int height, int grid_size);

    void new_gird();
    void addFood(int x, int y, int size, int energy, const sf::Color color);
    void addAntibiotic(int x, int y, int size, int energy, const sf::Color color);
};