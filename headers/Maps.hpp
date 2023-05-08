#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include "GameWorld.hpp"
#include "Stats.hpp"
#include "Vars.hpp"
#include "Organism.hpp"
#include "Grid.hpp"

class Map {
public:
    GameWorld& gw;
    Grid& grid; 

    Map(GameWorld& gw);

    virtual void initialize() = 0;

    virtual void update() = 0;

    virtual ~Map() = default;

    std::vector<int> createVector(int N);
};


class Map1Lines : public Map {
public:
    Map1Lines(GameWorld& gw);

    void initialize() override;

    void update() override;

    void spawn_food_in_lines(int amount_of_lines, int amount_of_food_in_line);
};


class Map2Rectangle : public Map {
public:
    Map2Rectangle(GameWorld& gw);

    void initialize() override;

    void update() override;

    void spawn_food_in_rectangle(int amount_of_food);
};


class Map3ThickLine : public Map {
public:
    Map3ThickLine(GameWorld& gw);

    void initialize() override;

    void update() override;

    void spawn_food_in_thick_line(int amount_of_lines, int amount_of_food);
};


class Map4Cross : public Map {
public:
    Map4Cross(GameWorld& gw);

    void initialize() override;

    void update() override;

    void spawn_food_in_cross(int amount_of_lines, int amount_of_food);
};