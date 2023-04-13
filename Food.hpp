#pragma once

class Food{
public:
   int x, y;
   int size, energy, id;
   int time = 0;
   sf::CircleShape shape;
   
   Food(int x, int y, int size, int energy, const sf::Color& color) {
      this->x = x;
      this->y = y;
      this->size = size;
      this->energy = energy;
      shape = sf::CircleShape(size);
      shape.setFillColor(color);
      shape.setPosition(x, y);
   }
};