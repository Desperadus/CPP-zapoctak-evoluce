#include "Food.hpp"

Food::Food(int x, int y, int size, int energy, const sf::Color& color) {
      this->x = x;
      this->y = y;
      this->size = size;
      this->energy = energy;
      shape = sf::CircleShape(size);
      shape.setFillColor(color);
      shape.setPosition(x, y);
   }