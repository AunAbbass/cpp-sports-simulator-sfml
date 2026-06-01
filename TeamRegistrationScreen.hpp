#ifndef TEAMREGISTRATIONSCREEN_HPP
#define TEAMREGISTRATIONSCREEN_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class TeamRegistrationScreen
{
private:
    sf::Font font;
    
    // Header
    sf::RectangleShape header;
    sf::Text headerText;
    
    // Colors
    sf::Color headerColor;
    sf::Color listBoxColor;
    
    // Teams list
    sf::Text teamsListLabel;
    sf::RectangleShape teamsListBox;
    std::vector<sf::RectangleShape> teamBoxes;
    std::vector<sf::Text> teamTexts;
    std::vector<sf::Text> playerCountTexts;
    
    std::vector<std::string> teams;
    std::vector<int> playerCounts;
    std::vector<std::vector<std::string>> teamPlayers; // Store players for each team
    
    // Player detail view
    int selectedTeamIndex;
    bool showingPlayers;
    sf::RectangleShape playerDetailBox;
    sf::Text playerDetailHeader;
    sf::Text backButtonText;
    sf::RectangleShape backButton;
    std::vector<sf::Text> playerDetailTexts;
    bool backButtonHovered;

public:
    TeamRegistrationScreen();
    bool loadFont(const std::string &fontPath);
    void setupUI(float windowWidth, float windowHeight);
    void setTeams(const std::vector<std::string>& teamNames, 
                  const std::vector<int>& playerCounts);
    void handleMouseMove(const sf::Vector2f &mousePos);
    int handleMouseClick(const sf::Vector2f &mousePos);
    void draw(sf::RenderWindow &window);

private:
    void updateTeamsList();
    void showPlayerDetails(int teamIndex);
    void hidePlayerDetails();
};

#endif