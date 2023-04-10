#pragma once

class Grid {
public:
    int& width, height;
    int grid_size;
    std::vector<std::vector<std::vector<std::shared_ptr<Food> > > > grid;
    size_t amount_of_food = 0;
    size_t amount_of_antibiotic = 0;

    Grid(int& width, int& height, int grid_size) :
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

    void new_gird() {
        amount_of_food = 0;
        amount_of_antibiotic = 0;
        grid.resize(height / grid_size);
        for (auto& row : grid) {
            row.resize(width / grid_size);
            for (auto& col : row) {
                col.resize(0);
            }
        }
    }

    
    void addFood(int x, int y, int size, int energy, const sf::Color color) {
      int xgrid = x / grid_size;
      int ygrid = y / grid_size;

      if (xgrid >= 0 && xgrid < width/grid_size && ygrid >= 0 && ygrid < height/grid_size) {
         grid[ygrid][xgrid].push_back(std::make_unique<Food>(x, y, size, energy, color));
         amount_of_food++;
      }
      else {
         //std::cout << x << " " << y << std::endl;
      }
    }

    
    void addAntibiotic(int x, int y, int size, int energy, const sf::Color color) {
      int xgrid = x / grid_size;
      int ygrid = y / grid_size;
      
      if (xgrid >= 0 && xgrid < width/grid_size && ygrid >= 0 && ygrid < height/grid_size) {
         grid[ygrid][xgrid].push_back(std::make_unique<Food>(x, y, size, energy, color));
         amount_of_antibiotic++;
      }
      else {
         //std::cout << x << " " << y << std::endl;
      }
    }
};
