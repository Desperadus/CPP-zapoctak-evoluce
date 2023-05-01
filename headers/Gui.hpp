#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "GameWorld.hpp"
#include "Game.hpp"

class Button {
public:
    sf::RectangleShape shape;
    sf::Text text;
    const sf::Font& font;
    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;
    int id;
    int font_size = 20;

    GameWorld& gw;
    Game& game;

    Button(float x, float y, float width, float height,
           const sf::Font& font, const std::string text, sf::Color Color, GameWorld& gw, Game& game, int id);

    void draw(sf::RenderWindow& window) const;

    void handleEvent(sf::Event event, sf::RenderWindow& window);
};


class InputBox {
public:
    int& asociated_var;
    int font_size = 16;

    InputBox(const std::string& label, const sf::Font& font, const sf::Vector2f& position, int offset, int& asociated_var);

    void draw(sf::RenderWindow& window) const;

    void handleEvent(sf::Event event, sf::RenderWindow& window);

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

    int last_input_box_coords = 0;
    int last_button_id = -1;

    GUI(GameWorld& gw, Game& game);

    void create_input_box(const std::string& description, int& asociated_var);

    void create_button(const std::string& description, sf::Color color, int y_coord, int width = 170);

    void HandleEvents();

    void RenderScene();
};