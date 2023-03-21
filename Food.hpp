class Food{
public:
   int x, y;
   int size, energy, color, id;
   sf::CircleShape shape;
   Food(int x, int y, int size, int energy, int color, int id) {
      this->x = x;
      this->y = y;
      this->size = size;
      this->energy = energy;
      this->color = color;
      this->id = id;
      create_shape();
   }

   void create_shape() {
      shape = sf::CircleShape(size);
      shape.setFillColor(sf::Color::Yellow);
      shape.setPosition(x, y);
   }
};