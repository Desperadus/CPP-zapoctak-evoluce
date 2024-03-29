#include "Organism.hpp"
#include <cmath>


Organism::Organism(int x, int y, int size, int speed, int energy, std::vector<int> chances, const int height, const int width, int max_size, int mutation_rate, int chance_of_mutation ,int generation) :
    height(height), width(width) {
    this->x = x;
    this->y = y;
    this->size = size;
    this->speed = speed;
    this->energy = energy;

    this->chances = chances;

    this->max_size = max_size;
    this->max_speed = max_size;
    this->generation = generation;
    this->mutation_rate = mutation_rate;
    this->chance_of_mutation = chance_of_mutation;

    create_shape();
}

void Organism::create_shape() {
    shape = sf::CircleShape(size);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(x - size, y - size);
}

int Organism::sum_of_vector(const std::vector<int> & v) const {
    int sum = 0;
    for (int i = 0; i < v.size(); i++) {
        sum += v[i];
    }
    return sum;
}

bool Organism::distance(int x1, int y1, int x2, int y2, int distance) const {
    if (sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)) <= distance) {
        return true;
    }
    return false;
}

bool Organism::distance2(int x1, int y1, int x2, int y2, int distance) const {
    if (abs(x1 - x2) <= distance && abs(y1 - y2) <= distance) {
        return true;
    }
    return false;
}

void Organism::move() {
    energy -= 1;
    int random_number = rand() % 100;
    for (int i = 0; i < 4; i++) {
        if (random_number < chances[i]) {
            if (i == 0) {

                if (x < width)
                {
                    x += speed;
                    shape.move(speed, 0);
                }
                else {
                    x = 1;
                    shape.setPosition(1 - size, y - size);
                }
            }
                        else if (i == 1) {

                if (x > 0)
                {
                    x -= speed;
                    shape.move(-speed, 0);
                }
                else {
                    x = width - 1;
                    shape.setPosition(width - 1 - size, y - size);
                }
            }
            else if (i == 2) {

                if (y < height)
                {
                    y += speed;
                    shape.move(0, speed);
                }
                else {
                    y = 1;
                    shape.setPosition(x - size, 1 - size);
                }
            }
            else if (i == 3) {

                if (y > 0)
                {
                    y -= speed;
                    shape.move(0, -speed);
                }
                else {
                    y = height - 1;
                    shape.setPosition(x - size, height - 1 - size);
                }
            }
            break;
        }
        else {
            random_number -= chances[i];
        }
    }
}


void Organism::try_to_eat(Grid & grid) {
    int x = this->x / grid.grid_size;
    int y = this->y / grid.grid_size;
    if (x >= 0 && x < width / grid.grid_size && y >= 0 && y < height / grid.grid_size) {
        for (int i = 0; i < grid.grid[y][x].size(); i++) {
            if (distance2(this->x, this->y, grid.grid[y][x][i]->x, grid.grid[y][x][i]->y, this->size)) {
                int food_energy = grid.grid[y][x][i]->energy;
                this->energy += food_energy;
                grid.grid[y][x].erase(grid.grid[y][x].begin() + i);
                if (food_energy > 0) grid.amount_of_food--;
                if (food_energy < 0) grid.amount_of_antibiotic--;
            }
        }
    }
}


void Organism::try_mitosis(std::vector<std::unique_ptr<Organism> > & organisms, int needed_energy) {
    if (energy > needed_energy) {
        int x = this->x;
        int y = this->y;
        int size = this->size;
        int speed = this->speed;
        int new_energy = this->energy / 2;
        std::vector<int> chances = this->chances;
        organisms.push_back(std::make_unique<Organism>(x, y, size, speed, new_energy, chances, height, width, max_size, chance_of_mutation ,generation + 1));
        generation += 1;

        mutate();
        organisms[organisms.size() - 1]->mutate();
        energy = energy / 2;
    }
}


void Organism::mutate(bool mutate_for_sure) {
      
      int random_number = rand() % 100;
      if (mutate_for_sure) {
         random_number = 101;
      }
      if (random_number < 100 - chance_of_mutation) {
         return;
      }
      
      random_number = rand() % 4;
      
      if (chances[random_number] - mutation_rate >= 0) {
         //cout << "mutate " << chances[i] <<endl;
         chances[random_number] -= mutation_rate;
         int rng = rand() % 4;
         while(rng == random_number) {
            rng = rand() % 4;
         }
         chances[rng] += mutation_rate;
      }
      else {
         int rng = rand() % 4;
         while(rng == random_number) {
            rng = rand() % 4;
         }
         chances[rng] += chances[random_number];
         chances[random_number] = 0;
      }


      if (random_number == 0 && speed > 1) {
         //cout << "mutate speed" << endl;
         int rand2 = rand() % 2;
         if (rand2 == 0) {
            speed -= 1;
            if (speed < 1) {
               speed = 1;
            }
         }
         if (rand2 == 1 && speed < max_speed) {
            speed+=1;
            //cout << speed << " " << max_speed << endl;
            if (speed > size && size < max_size) {
               size +=1;
               shape = sf::CircleShape(size);
            }
         }
      }
   }