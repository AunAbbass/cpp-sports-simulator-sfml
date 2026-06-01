#ifndef MAINSCREEN_HPP
#define MAINSCREEN_HPP

#include <SFML/Graphics.hpp>
#include <string>

class MainScreen
{
private:
    sf::RectangleShape startButton;
    sf::RectangleShape viewTeamsButton;
    sf::RectangleShape exitButton;
    sf::RectangleShape header;

    sf::Font font;
    sf::Text headerText;
    sf::Text startText;
    sf::Text viewTeamsText;
    sf::Text exitText;

    sf::Color buttonColor;
    sf::Color buttonHoverColor;
    sf::Color headerColor;

    int hoveredButton; // 0: none, 1: start, 2: view teams, 3: exit

public:
    MainScreen();
    bool loadFont(const std::string &fontPath);
    void draw(sf::RenderWindow &window);
    void handleMouseMove(const sf::Vector2f &mousePos);
    int handleMouseClick(const sf::Vector2f &mousePos);
    void setupUI(float windowWidth, float windowHeight);
};

#endif