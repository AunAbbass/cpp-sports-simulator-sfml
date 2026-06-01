#ifndef TOURNAMENTWINNERSCREEN_HPP
#define TOURNAMENTWINNERSCREEN_HPP

#include <SFML/Graphics.hpp>
#include <string>

class TournamentWinnerScreen
{
private:
    sf::Font font;
    
    // Background
    sf::Color backgroundColor;
    
    // Text elements
    sf::Text winnerLabelText;
    sf::Text winnerNameText;
    sf::Text winsLabelText;
    sf::Text winsValueText;
    sf::Text lossLabelText;
    sf::Text lossValueText;
    
    // Return button
    sf::RectangleShape returnButton;
    sf::Text returnButtonText;
    bool returnButtonHovered;
    
    // Data
    std::string winnerName;
    int wins;
    int losses;
    
    float windowWidth;
    float windowHeight;

public:
    TournamentWinnerScreen();
    bool loadFont(const std::string &fontPath);
    void setupUI(float windowWidth, float windowHeight);
    void setWinner(const std::string& teamName, int wins, int losses);
    void handleMouseMove(const sf::Vector2f &mousePos);
    int handleMouseClick(const sf::Vector2f &mousePos);
    void draw(sf::RenderWindow &window);

private:
    void updateDisplay();
};

#endif