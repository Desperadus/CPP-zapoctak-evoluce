#pragma once

class Button {
public:
   sf::RectangleShape shape;
   sf::Text text;
   sf::Font& font;
   sf::Color idleColor;
   sf::Color hoverColor;
   sf::Color activeColor;
   int id;
   int font_size = 20;

   GameWorld& gw;
   Game& game;
   //unique_ptr<Statistics> stats;

   Button(float x, float y, float width, float height,
      sf::Font& font, const std::string text, sf::Color Color, GameWorld& gw, Game& game, int id) : font(font), gw(gw), game(game)
   {
      this->shape.setPosition(sf::Vector2f(x, y));
      this->shape.setSize(sf::Vector2f(width, height));
      this->shape.setFillColor(Color);

      this->font = font;
      this->text.setFont(this->font);
      this->text.setString(text);
      this->text.setFillColor(sf::Color::Black);
      this->text.setCharacterSize(font_size);
      this->text.setPosition(
      this->shape.getPosition().x + this->shape.getGlobalBounds().width / 2.f - this->text.getGlobalBounds().width / 2.f,
      this->shape.getPosition().y + this->shape.getGlobalBounds().height / 2.f - this->text.getGlobalBounds().height / 2.f
      );
      this->id = id;

      if (id == 6) {
         shape.setOutlineThickness(4.f);
         shape.setOutlineColor(sf::Color::Red);
      }

   }

   void draw(sf::RenderWindow& window) const
   {
      window.draw(shape);
      window.draw(text);
   }

   void handleEvent(sf::Event event, sf::RenderWindow& window)
   {
      if (event.type == sf::Event::MouseButtonPressed)
      {
         // Check if the mouse click is inside the text box
         sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
         sf::FloatRect bounds = shape.getGlobalBounds();
         if (bounds.contains(mousePosition))
         {
            //cout << id;
            if (id == 0) {
               game.clear_game();
               game.start_game();
               return;
            }
            if (id == 1) {
               game.pause_game();
            }
            if (id == 2) {
               gw.spawn_organisms(NUMBER_OF_ORGANISMS, ORGANISM_ENERGY);
            }
            if (id == 3) {
               game.game_speed /= GAME_SPEED_MULTIPLIER;
            }
            if (id == 4) {
               game.game_speed *= GAME_SPEED_MULTIPLIER;
               if (game.game_speed < 1)
                  game.game_speed = 1;
            }
            if (id == 5) {
               game.draw_stats(font);
            }

            if (id == 6) {
               if (gw.adding_antibiotics) {
                  gw.adding_antibiotics = false;
                  shape.setOutlineColor(sf::Color::Red);
               }
               else {
                  gw.adding_antibiotics = true;
                  shape.setOutlineColor(sf::Color::Green);
               }
            }
         }
      }
   }

};


class InputBox
{
public:
   std::string value;
   int& asociated_var;
   int font_size = 16;
   
   InputBox(const std::string& label, const sf::Font& font, const sf::Vector2f& position, int offset, int& asociated_var) : asociated_var(asociated_var)
   {  
      // Create label
      m_label.setFont(font);
      m_label.setString(label);
      m_label.setCharacterSize(16);
      m_label.setFillColor(sf::Color::White);
      m_label.setPosition(position);

      // Create text box
      m_textBox.setSize(sf::Vector2f(120, 20));
      m_textBox.setOutlineThickness(2.f);
      m_textBox.setOutlineColor(sf::Color::Green);
      m_textBox.setPosition(position + sf::Vector2f(offset, 0));

      // Create text object
      m_text.setFont(font);
      m_text.setString(std::to_string(asociated_var));
      m_text.setCharacterSize(font_size);
      m_text.setFillColor(sf::Color::Black);
      m_text.setPosition(position + sf::Vector2f(offset + 3, 2));

   }

   void draw(sf::RenderWindow& window) const
   {
      window.draw(m_label);
      window.draw(m_textBox);
      window.draw(m_text);
   }

   void handleEvent(sf::Event event, sf::RenderWindow& window)
   {
      if (event.type == sf::Event::MouseButtonPressed)
      {
         // Check if the mouse click is inside the text box
         sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
         sf::FloatRect bounds = m_textBox.getGlobalBounds();
         if (bounds.contains(mousePosition))
         {
               isSelected = true;
         }
         else
         {
               isSelected = false;
         }
      }
      else if (event.type == sf::Event::TextEntered && isSelected)
      {   
         //cout << "event.text.unicode: " << event.text.unicode << endl; 
         if (event.text.unicode == 8) // Backspace
         {     
               m_textBox.setOutlineColor(sf::Color::Red);
               if(m_input.size() == 0) {
                  m_text.setString("");
               }  

               if (m_input.size() > 0)
               {
                  m_input.pop_back();
                  m_text.setString(m_input);
               }
         }
         else if (event.text.unicode < 128 && event.text.unicode != 13) // normalni text
         {     
               m_textBox.setOutlineColor(sf::Color::Red);
               m_input += static_cast<char>(event.text.unicode);
               m_text.setString(m_input);
         }
         else if (event.text.unicode == 13) // Enter
         {     
               m_textBox.setOutlineColor(sf::Color::Green);
               isSelected = false;
               m_text.setString(m_input);
               try {
                  asociated_var = stoi(m_input);
               }
               catch (const std::exception& e) {
                  std::cout << "Invalid input" << std::endl;
               }
         }
         
      }
    }

private:
    std::string m_input;
    sf::Text m_label;
    sf::RectangleShape m_textBox;
    sf::Text m_text;
    bool isSelected = false;
};




class GUI {
public:
   sf::RenderWindow window;
   std::vector<InputBox> inputBoxes;
   std::vector<Button> buttons;
   sf::Font font;
   GameWorld& gw;
   Game& game;

   GUI(GameWorld& gw, Game& game) : gw(gw), game(game) {
      // Create window
      window.create(sf::VideoMode(WINDOW_WIDTH_GUI, WINDOW_HEIGHT_GUI), "SFML Input Boxes");

      // Load font
      
      if (!font.loadFromFile("ariblk.ttf"))
      {
         exit(EXIT_FAILURE);
      }

      // Create input boxes
      inputBoxes.emplace_back("Map: (1,2,3)", font, sf::Vector2f(10, 50), 170, MAP);
      inputBoxes.emplace_back("Number of lines:", font, sf::Vector2f(10, 100), 170, NUMBER_OF_LINES);
      inputBoxes.emplace_back("Organism size:", font, sf::Vector2f(10, 150), 170, ORGANISM_SIZE);
      inputBoxes.emplace_back("Reroduction E:", font, sf::Vector2f(10, 200), 170, REPRODUCTION_ENERGY);
      inputBoxes.emplace_back("Spawn rate:", font, sf::Vector2f(10, 250), 170, SPAWN_RATE);
      inputBoxes.emplace_back("Rand spawn rate:", font, sf::Vector2f(10, 300), 170, RANDOM_SPAWN_RATE);
      inputBoxes.emplace_back("Number of org:", font, sf::Vector2f(10, 350), 170, NUMBER_OF_ORGANISMS);
      inputBoxes.emplace_back("Food energy:", font, sf::Vector2f(10, 400), 170, FOOD_ENERGY);
      inputBoxes.emplace_back("Max num of food:", font, sf::Vector2f(10, 450), 170, NUMBER_OF_FOOD);
      inputBoxes.emplace_back("Anitibiotic dmg:", font, sf::Vector2f(10, 500), 170, ANTIBIOTIC_ENERGY);
      inputBoxes.emplace_back("Anti spawn rate:", font, sf::Vector2f(10, 550), 170, ANTIBIOTIC_SPAWN_RATE);
      inputBoxes.emplace_back("Max num of anti:", font, sf::Vector2f(10, 600), 170, NUMBER_OF_ANTIBIOTIC);

      // Create buttons
      buttons.emplace_back(550, 36, 100, 50, font, "Start", sf::Color::Green, gw, game, 0);
      buttons.emplace_back(550, 100, 170, 50, font, "Pause/Resume", sf::Color::Cyan, gw, game, 1);
      buttons.emplace_back(550, 164, 170, 50, font, "Add organisms", sf::Color::Green, gw, game, 2);
      buttons.emplace_back(550, 334, 170, 50, font, "Speed up", sf::Color::Green, gw, game, 3);
      buttons.emplace_back(550, 390, 170, 50, font, "Slow down", sf::Color::Red, gw, game, 4);
      buttons.emplace_back(550, 500, 170, 50, font, "Show stats", sf::Color::Cyan, gw, game, 5);
      buttons.emplace_back(550, 600, 170, 50, font, "Add anti", sf::Color::White, gw, game, 6);




   }

   void HandleEvents() {
      // Handle events
         sf::Event event;
         while (window.pollEvent(event))
         {
               if (event.type == sf::Event::Closed)
               {
                  window.close();
               }
               else if (event.type == sf::Event::TextEntered || event.type == sf::Event::MouseButtonPressed)
               {   
                  for (auto & inputBox : inputBoxes)
                  {
                     inputBox.handleEvent(event, window);
                  }
                  for (auto & button : buttons)
                  {
                     button.handleEvent(event, window);
                  }
               }
         }
   }

   void RenderScene() {
      // Draw input boxes
      window.clear(sf::Color::Black);
      for (const auto & inputBox : inputBoxes)
      {
         inputBox.draw(window);
      }
      for (const auto & button : buttons)
      {
         button.draw(window);
      }
   }
};
