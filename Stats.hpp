#pragma once

class Text {
public:
    sf::Text text;
    sf::Font& font;
    Text(sf::Font& font, std::string txt, int x, int y, int font_size, sf::Color color) : font(font) {
      text.setFont(font);
      text.setCharacterSize(font_size);
      text.setFillColor(color);
      text.setPosition(x, y);
      text.setString(txt);
    }
    void draw(sf::RenderWindow& window) {
      window.draw(text);
    }
};

class Statistics {
public:
   sf::RenderWindow window;
   sf::Font& font;

   std::vector<Text> texts;
   std::vector<Text> bac_stats; 


   Statistics(sf::Font& font) : font(font) {
      window.create(sf::VideoMode(500, 250), "Statistics");
      
      texts.emplace_back(font, "Statistics:", 10, 10, 24, sf::Color::Green);
      texts.emplace_back(font, "Number of organisms alive: ", 10, 40, 14, sf::Color::White);
      texts.emplace_back(font, "Number of food: ", 10, 60, 14, sf::Color::White);
      texts.emplace_back(font, "Most successful bacteria stats: ", 10, 100, 14, sf::Color::Cyan);
      texts.emplace_back(font, "Size: ", 10, 120, 14, sf::Color::White);
      texts.emplace_back(font, "Speed: ", 10, 140, 14, sf::Color::White);
      texts.emplace_back(font, "Chance of moving in right direction: ", 10, 160, 14, sf::Color::White);
      texts.emplace_back(font, "Chance of moving in left direction: ", 10, 180, 14, sf::Color::White);
      texts.emplace_back(font, "Chance of moving in down direction: ", 10, 200, 14, sf::Color::White);
      texts.emplace_back(font, "Chance of moving in up direction: ", 10, 220, 14, sf::Color::White);

      bac_stats.emplace_back(font, "0", 80, 120, 14, sf::Color::White);
      bac_stats.emplace_back(font, "0", 80, 140, 14, sf::Color::White);
      bac_stats.emplace_back(font, "0", 320, 160, 14, sf::Color::White);
      bac_stats.emplace_back(font, "0", 320, 180, 14, sf::Color::White);
      bac_stats.emplace_back(font, "0", 320, 200, 14, sf::Color::White);
      bac_stats.emplace_back(font, "0", 320, 220, 14, sf::Color::White);



   }

   void HandleEvents() {
   sf::Event event;
   while (window.pollEvent(event))
   {
      if (event.type == sf::Event::Closed)
      {
         window.close();
      }

   }
   }

   void RenderScene() {
      for (auto && text : texts) {
         text.draw(window);
      }
      for (auto && bac_stat : bac_stats) {
         bac_stat.draw(window);
      }
   }




};