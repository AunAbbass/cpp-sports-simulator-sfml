#ifndef STANDINGSSCREEN_HPP
#define STANDINGSSCREEN_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>

struct TeamStats
{
    std::string name;
    int played;
    int won;
    int points;

    TeamStats() : name(""), played(0), won(0), points(0) {}
    TeamStats(const std::string &n) : name(n), played(0), won(0), points(0) {}
};

class StandingsScreen
{
private:
    sf::RectangleShape header;
    sf::RectangleShape tableBox;
    sf::RectangleShape nextMatchPanel;

    // Table headers
    sf::RectangleShape teamHeader;
    sf::RectangleShape playedHeader;
    sf::RectangleShape wonHeader;
    sf::RectangleShape pointsHeader;

    sf::Font font;
    sf::Text headerText;
    sf::Text teamHeaderText;
    sf::Text playedHeaderText;
    sf::Text wonHeaderText;
    sf::Text pointsHeaderText;
    sf::Text nextMatchLabel;
    sf::Text matchupText;

    sf::Color headerColor;
    sf::Color tableHeaderColor;
    sf::Color tableRowColor;
    sf::Color panelColor;

    std::map<std::string, TeamStats> standings;
    std::vector<sf::Text> standingsTexts;
    std::vector<sf::RectangleShape> standingsBoxes;

    std::string currentMatchup;

public:
    StandingsScreen();
    bool loadFont(const std::string &fontPath);
    void draw(sf::RenderWindow &window);
    void setupUI(float windowWidth, float windowHeight);
    void initializeStandings(const std::vector<std::string> &teams);
    void updateStandings();
    void setCurrentMatchup(const std::string &matchup);
    void recordMatchResult(const std::string &winner, const std::string &loser);
    const std::map<std::string, TeamStats> &getStandings() const { return standings; }
};

#endif