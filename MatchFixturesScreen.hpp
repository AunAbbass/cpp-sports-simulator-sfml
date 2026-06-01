#ifndef MATCHFIXTURESSCREEN_HPP
#define MATCHFIXTURESSCREEN_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class MatchFixturesScreen
{
private:
    sf::RectangleShape header;
    sf::RectangleShape fixturesBox;
    sf::RectangleShape teamAHeader;
    sf::RectangleShape teamBHeader;
    sf::RectangleShape nextMatchPanel;
    sf::RectangleShape nextButton;

    sf::Font font;
    sf::Text headerText;
    sf::Text teamAText;
    sf::Text teamBText;
    sf::Text nextMatchLabel;
    sf::Text matchupText;
    sf::Text nextButtonText;

    sf::Color headerColor;
    sf::Color tableHeaderColor;
    sf::Color tableRowColor;
    sf::Color buttonColor;
    sf::Color buttonHoverColor;

    std::vector<std::pair<std::string, std::string>> fixtures;
    std::vector<sf::Text> fixtureTexts;
    std::vector<sf::RectangleShape> fixtureBoxes;

    bool nextButtonHovered;
    int currentFixtureIndex;

public:
    MatchFixturesScreen();
    bool loadFont(const std::string &fontPath);
    void draw(sf::RenderWindow &window);
    void handleMouseMove(const sf::Vector2f &mousePos);
    int handleMouseClick(const sf::Vector2f &mousePos);
    void setupUI(float windowWidth, float windowHeight);
    void generateFixtures(const std::vector<std::string> &teams);
    void updateFixturesList();
    std::string getCurrentMatchup() const;
    void advanceToNextFixture();  // NEW METHOD
    bool hasMoreFixtures() const; // NEW METHOD
};

#endif