#ifndef PLAYERLISTSCREEN_HPP
#define PLAYERLISTSCREEN_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class PlayerListScreen
{
private:
    sf::Font font;
    
    // Header
    sf::RectangleShape header;
    sf::Text headerText;
    sf::Text teamNameText;
    
    // Colors
    sf::Color headerColor;
    sf::Color backgroundColor;
    
    // Back button
    sf::RectangleShape backButton;
    sf::Text backButtonText;
    bool backButtonHovered;
    
    // Player list
    sf::RectangleShape playerListBox;
    std::vector<sf::RectangleShape> playerBoxes;
    std::vector<sf::Text> playerNameTexts;
    std::vector<sf::Text> playerNumberTexts;
    
    // Data
    std::string currentTeamName;
    std::vector<std::string> playerNames;
    
    float windowWidth;
    float windowHeight;

public:
    PlayerListScreen();
    bool loadFont(const std::string &fontPath);
    void setupUI(float windowWidth, float windowHeight);
    void setTeamPlayers(const std::string& teamName, const std::vector<std::string>& players);
    void handleMouseMove(const sf::Vector2f &mousePos);
    int handleMouseClick(const sf::Vector2f &mousePos);
    void draw(sf::RenderWindow &window);

private:
    void updatePlayerList();
};

#endif