#ifndef MATCHRESULTSCREEN_HPP
#define MATCHRESULTSCREEN_HPP

#include <SFML/Graphics.hpp>
#include <string>

class MatchResultScreen
{
private:
    sf::Font font;
    
    sf::RectangleShape header;
    sf::RectangleShape resultPanel;
    sf::RectangleShape continueButton;
    
    sf::Text headerText;
    sf::Text winnerAnnouncementText;
    sf::Text team1NameText;
    sf::Text team2NameText;
    sf::Text team1ScoreText;
    sf::Text team2ScoreText;
    sf::Text continueButtonText;
    sf::Text instructionText;
    
    sf::Color headerColor;
    sf::Color panelColor;
    sf::Color buttonColor;
    sf::Color buttonHoverColor;
    
    std::string team1;
    std::string team2;
    int team1Score;
    int team2Score;
    int team1Wickets;
    int team2Wickets;
    std::string winner;
    bool buttonHovered;

public:
    MatchResultScreen();
    bool loadFont(const std::string &fontPath);
    void setupUI(float windowWidth, float windowHeight);
    void setMatchResult(const std::string& teamAName, const std::string& teamBName,
                       int teamAScore, int teamBScore, int teamAWickets, int teamBWickets);
    void handleMouseMove(const sf::Vector2f &mousePos);
    bool handleMouseClick(const sf::Vector2f &mousePos);
    void draw(sf::RenderWindow &window);
};

#endif