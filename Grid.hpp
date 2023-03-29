#pragma once

using namespace std;

class Grid {
public:
    int width, height, grid_size;
    std::vector<std::vector<std::vector<shared_ptr<Food> > > > grid;
    size_t amount_of_food = 0;
    size_t amount_of_antibiotic = 0;

    Grid(int width, int height, int grid_size) :
        width(width), height(height), grid_size(grid_size) {
        // Initialize the grid with empty vectors
        grid.resize(height/grid_size);
        for (auto& row : grid) {
            row.resize(width/grid_size);
            for (auto& col : row) {
                col.resize(0);
            }
        }
    }

    void addFood(int x, int y, int size, int energy, int id, sf::Color color) {
      int xgrid = x / grid_size;
      int ygrid = y / grid_size;
      //std::cout << x << " " << y << std::endl;
      if (xgrid >= 0 && xgrid < width/grid_size && ygrid >= 0 && ygrid < height/grid_size) {
         grid[ygrid][xgrid].push_back(make_unique<Food>(x, y, size, energy, id, color));
         amount_of_food++;
      }
      else {
         //std::cout << x << " " << y << std::endl;
      }
    }

    void addAntibiotic(int x, int y, int size, int energy, int id, sf::Color color) {
      int xgrid = x / grid_size;
      int ygrid = y / grid_size;
      //std::cout << x << " " << y << std::endl;
      if (xgrid >= 0 && xgrid < width/grid_size && ygrid >= 0 && ygrid < height/grid_size) {
         grid[ygrid][xgrid].push_back(make_unique<Food>(x, y, size, energy, id, color));
         amount_of_antibiotic++;
      }
      else {
         //std::cout << x << " " << y << std::endl;
      }
    }
};
