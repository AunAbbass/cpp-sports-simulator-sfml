#ifndef INTERACTIVEMATCHSCREEN_HPP
#define INTERACTIVEMATCHSCREEN_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class InteractiveMatchScreen
{
private:
    sf::RectangleShape header;
    sf::RectangleShape scorePanel;
    sf::RectangleShape batsmanPanel;
    sf::RectangleShape bowlerPanel;
    sf::RectangleShape controlsPanel;

    sf::Font font;
    sf::Text headerText;
    sf::Text teamANameText;
    sf::Text teamBNameText;
    sf::Text scoreText;
    sf::Text oversText;
    sf::Text wicketsText;
    
    sf::Text strikerText;
    sf::Text strikerStatsText;
    sf::Text nonStrikerText;
    sf::Text nonStrikerStatsText;
    
    sf::Text bowlerText;
    sf::Text bowlerStatsText;
    
    sf::Text instructionsText;
    sf::Text lastBallText;
    sf::Text currentOverText;

    sf::Color headerColor;
    sf::Color panelColor;

    // Match state
    std::string teamAName;
    std::string teamBName;
    std::vector<std::string> teamAPlayers;
    std::vector<std::string> teamBPlayers;
    
    int battingTeam; // 0 = teamA, 1 = teamB (current batting team)
    int firstBattingTeam; // Track which team batted first (0 = teamA, 1 = teamB)
    int currentInnings; // 0 = first innings, 1 = second innings
    
    int totalScore;
    int wickets;
    int currentOver;
    int ballInOver;
    
    // Store first innings results
    int firstInningsScore;
    int firstInningsWickets;
    
    int strikerIndex;
    int nonStrikerIndex;
    int bowlerIndex;
    int nextBatsmanIndex;
    
    // Striker stats
    int strikerRuns;
    int strikerBalls;
    
    // Non-striker stats
    int nonStrikerRuns;
    int nonStrikerBalls;
    
    // Bowler stats
    int bowlerRunsConceded;
    int bowlerWickets;
    int bowlerOversBowled;
    
    int targetScore;
    bool matchComplete;
    std::string matchResult;
    
    std::vector<std::string> overBalls;

public:
    InteractiveMatchScreen();
    bool loadFont(const std::string &fontPath);
    void setupUI(float windowWidth, float windowHeight);
    void initializeMatch(const std::string& teamA, const std::string& teamB,
                        const std::vector<std::string>& playersA,
                        const std::vector<std::string>& playersB);
    void handleKeyPress(sf::Keyboard::Key key);
    void draw(sf::RenderWindow &window);
    
    bool isMatchComplete() const { return matchComplete; }
    std::string getWinner() const;
    int getTeamAScore() const;
    int getTeamBScore() const;
    int getTeamAWickets() const;
    int getTeamBWickets() const;

private:
    void processBall(int runs);
    void processWicket();
    void switchStriker();
    void nextOver();
    void nextInnings();
    void updateDisplay();
    void checkMatchComplete();
}; 

#endif