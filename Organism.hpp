#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Grid.hpp"


class Organism {
public:
    const int height, width;

    int x, y;

    int size, speed;

    int energy;

    int max_size, max_speed, mutation_rate;

    int generation;

    int chance_of_mutation;

    sf::CircleShape shape;

    std::vector<int> chances;

    Organism(int x, int y, int size, int speed, int energy, std::vector<int> chances, const int height, const int width, int max_size, int mutation_rate, int chance_of_mutation, int generation = 0);

    void create_shape();

    int sum_of_vector(const std::vector<int> & v) const;

    bool distance(int x1, int y1, int x2, int y2, int distance) const;

    bool distance2(int x1, int y1, int x2, int y2, int distance) const;

    void move();

    void try_to_eat(Grid & grid);

    void try_mitosis(std::vector<std::unique_ptr<Organism> > & organisms, int needed_energy);

    void mutate(bool mutate_for_sure = false);
};