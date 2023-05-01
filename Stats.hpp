#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Text {
public:
    sf::Text text;
    const sf::Font& font;
    Text(const sf::Font& font, const std::string& txt, int x, int y, int font_size, const sf::Color color);
    void draw(sf::RenderWindow& window);
};

class Statistics {
public:
   sf::RenderWindow window;
   const sf::Font& font;

   std::vector<Text> texts;
   std::vector<Text> bac_stats; 


   Statistics(const sf::Font& font);

   void HandleEvents();

   void RenderScene();
};