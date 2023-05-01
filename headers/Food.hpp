#pragma once
#include <SFML/Graphics.hpp>

class Food{
public:
   int x, y;
   int size, energy, id;
   int time = 0;
   sf::CircleShape shape;
   
   Food(int x, int y, int size, int energy, const sf::Color& color);
};