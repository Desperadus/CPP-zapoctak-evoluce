#include "Stats.hpp"

Text::Text(const sf::Font& font, const std::string& txt, int x, int y, int font_size, const sf::Color color) : font(font) {
      text.setFont(font);
      text.setCharacterSize(font_size);
      text.setFillColor(color);
      text.setPosition(x, y);
      text.setString(txt);
}

void Text::draw(sf::RenderWindow& window) {
      window.draw(text);
}

Statistics::Statistics(const sf::Font& font) : font(font) {
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

      for (int i = 0; i < 6; i++) {
         bac_stats.emplace_back(font, "0", 320, 120 + i * 20, 14, sf::Color::White);
      }
}

void Statistics::HandleEvents() {
   sf::Event event;
   while (window.pollEvent(event))
   {
      if (event.type == sf::Event::Closed)
      {
         window.close();
      }

   }
}

void Statistics::RenderScene() {
      for (auto && text : texts) {
         text.draw(window);
      }
      for (auto && bac_stat : bac_stats) {
         bac_stat.draw(window);
      }
}