using namespace std;

class GameWorld{
public:
   int& height;
   int& width;
   int& org_size;
   int grid_size = 250;
   int number_of_food = 5000;
   std::vector<unique_ptr<Organism> > organisms;
   Grid grid;
   GameWorld(int& height, int& width, int& org_size) : grid(height, width, grid_size), height(height), width(width), org_size(org_size) {
      this->height = height;
      this->width = width;
      this->org_size = org_size;
   }

    int sum_of_vector(vector<int> & v) {
        int sum = 0;
        for (int i = 0; i < v.size(); i++) {
            sum += v[i];
        }
        return sum;
    }

   void spawn_organisms(int amount, int energy) {
      srand((unsigned) time(NULL));
      for (int i = 0; i < amount; i++) {
         int x = rand() % width;
         int y = rand() % height;
         int size = org_size;
         int speed = rand() % org_size;
         if (speed < 1) {
            speed = 1;
         }

         int color = rand() % 255;
         int id = i;
         
         vector<int> chances = { 0, 0, 0, 0 };
         for (int i = 0; i < 4; i++) {
            chances[i] = rand() % 100;
         }
         int sum = sum_of_vector(chances);
         for (int i = 0; i < 4; i++) {
            chances[i] = chances[i] * 100 / sum;
         }
         int sum2 = sum_of_vector(chances);
         if (sum2 != 100) {
            chances[0] += 100 - sum2;
         }
      
         organisms.push_back(make_unique<Organism>(x, y, size, speed, energy, color, id, chances, height, width));
      }

   }

   void spawn_food_in_lines(int amount_of_lines, int amount_of_food_in_line, int food_energy) {
    //   if (grid.amount_of_food == 0) {
    //      grid = Grid(height, width, grid_size);
    //   }
        if (number_of_food < grid.amount_of_food) return;
    
        for (int i = 1; i < amount_of_lines; i++) {
            for (int j = 0; j < amount_of_food_in_line; j++) {
            int x = (width / amount_of_lines) * i;
            int y = rand() % height;

            int size = 2;
            int energy = food_energy;
            int color = rand() % 255;
            int id = i;
            grid.addFood(x, y, size, energy, color, id);


            x = rand() % width;
            y = (height / amount_of_lines) * i;

            size = 2;
            energy = 5;
            color = rand() % 255;
            id = i;
            grid.addFood(x, y, size, energy, color, id);

            }
        }
   }
      
   void spawn_random_food(int amount_of_food, int food_energy) {
    //   if (grid.amount_of_food == 0) {
    //      grid = Grid(height, width, grid_size);
    //   }
        if (number_of_food < grid.amount_of_food) return;
        for (int i = 0; i < amount_of_food; i++) {
            int x = rand() % width;
            int y = rand() % height;

            int size = 2;
            int energy = food_energy;
            int color = rand() % 255;
            int id = i;
            grid.addFood(x, y, size, energy, color, id);
        }
   }

   void spawn_food_in_rectangle(int amout_of_food, int food_energy) {

        if (number_of_food < grid.amount_of_food) return;
        for (int i = 0; i < amout_of_food; i++) {
            int x = rand() % (width / 2) + width / 4;
            int y = rand() % (height / 2) + height / 4;

            int size = 2;
            int energy = food_energy;
            int color = rand() % 255;
            int id = i;
            grid.addFood(x, y, size, energy, color, id);
        }
   }

};