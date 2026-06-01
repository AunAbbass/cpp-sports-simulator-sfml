#include "MatchResultScreen.hpp"
#include <sstream>

MatchResultScreen::MatchResultScreen()
    : headerColor(sf::Color(62, 39, 35)),
      panelColor(sf::Color(240, 240, 240)),
      buttonColor(sf::Color(100, 200, 100)),
      buttonHoverColor(sf::Color(120, 220, 120)),
      team1Score(0), team2Score(0), team1Wickets(0), team2Wickets(0), 
      buttonHovered(false)
{
}

bool MatchResultScreen::loadFont(const std::string &fontPath)
{
    return font.loadFromFile(fontPath);
}

void MatchResultScreen::setupUI(float windowWidth, float windowHeight)
{
    // Header
    header.setSize(sf::Vector2f(windowWidth, 80));
    header.setPosition(0, 0);
    header.setFillColor(headerColor);

    headerText.setFont(font);
    headerText.setString("Match Result");
    headerText.setCharacterSize(28);
    headerText.setFillColor(sf::Color::White);
    sf::FloatRect headerBounds = headerText.getLocalBounds();
    headerText.setPosition((windowWidth - headerBounds.width) / 2, 25);

    // Result panel
    resultPanel.setSize(sf::Vector2f(windowWidth - 80, 280));
    resultPanel.setPosition(40, 100);
    resultPanel.setFillColor(panelColor);
    resultPanel.setOutlineThickness(3);
    resultPanel.setOutlineColor(sf::Color::Black);

    // Winner announcement (at top center)
    winnerAnnouncementText.setFont(font);
    winnerAnnouncementText.setCharacterSize(28);
    winnerAnnouncementText.setFillColor(sf::Color(0, 120, 0));
    winnerAnnouncementText.setStyle(sf::Text::Bold);

    // Team 1 name (left side)
    team1NameText.setFont(font);
    team1NameText.setCharacterSize(24);
    team1NameText.setFillColor(sf::Color::Black);
    team1NameText.setStyle(sf::Text::Bold);

    // Team 2 name (right side)
    team2NameText.setFont(font);
    team2NameText.setCharacterSize(24);
    team2NameText.setFillColor(sf::Color::Black);
    team2NameText.setStyle(sf::Text::Bold);

    // Team 1 score (below team 1 name)
    team1ScoreText.setFont(font);
    team1ScoreText.setCharacterSize(32);
    team1ScoreText.setFillColor(sf::Color::Black);

    // Team 2 score (below team 2 name)
    team2ScoreText.setFont(font);
    team2ScoreText.setCharacterSize(32);
    team2ScoreText.setFillColor(sf::Color::Black);

    // Instruction text
    instructionText.setFont(font);
    instructionText.setString("Click anywhere to continue");
    instructionText.setCharacterSize(18);
    instructionText.setFillColor(sf::Color(100, 100, 100));
    sf::FloatRect instBounds = instructionText.getLocalBounds();
    instructionText.setPosition((windowWidth - instBounds.width) / 2, 420);

    // Continue button
    continueButton.setSize(sf::Vector2f(200, 50));
    continueButton.setPosition((windowWidth - 200) / 2, 400);
    continueButton.setFillColor(buttonColor);
    continueButton.setOutlineThickness(2);
    continueButton.setOutlineColor(sf::Color::Black);

    continueButtonText.setFont(font);
    continueButtonText.setString("Continue");
    continueButtonText.setCharacterSize(20);
    continueButtonText.setFillColor(sf::Color::White);
    sf::FloatRect btnBounds = continueButtonText.getLocalBounds();
    continueButtonText.setPosition(
        (560 - btnBounds.width) / 2,
        410);
}

void MatchResultScreen::setMatchResult(const std::string& teamAName, const std::string& teamBName,
                                      int teamAScore, int teamBScore, int teamAWickets, int teamBWickets)
{
    // Determine winner
    winner = (teamAScore > teamBScore) ? teamAName : teamBName;
    
    // Always keep team order as Team A (left) and Team B (right)
    team1 = teamAName;
    team2 = teamBName;
    team1Score = teamAScore;
    team2Score = teamBScore;
    team1Wickets = teamAWickets;
    team2Wickets = teamBWickets;

    std::stringstream ss;
    
    // Winner announcement at top center
    ss << winner << " Won";
    winnerAnnouncementText.setString(ss.str());
    sf::FloatRect winnerBounds = winnerAnnouncementText.getLocalBounds();
    winnerAnnouncementText.setPosition((560 - winnerBounds.width) / 2, 120);

    // Team 1 name (left side)
    team1NameText.setString(team1);
    sf::FloatRect team1Bounds = team1NameText.getLocalBounds();
    team1NameText.setPosition(120, 200);

    // Team 2 name (right side)
    team2NameText.setString(team2);
    sf::FloatRect team2Bounds = team2NameText.getLocalBounds();
    team2NameText.setPosition(440 - team2Bounds.width, 200);

    // Team 1 score/wickets (below team 1 name)
    ss.str("");
    ss << team1Score << "/" << team1Wickets;
    team1ScoreText.setString(ss.str());
    sf::FloatRect score1Bounds = team1ScoreText.getLocalBounds();
    team1ScoreText.setPosition(120 + (team1Bounds.width - score1Bounds.width) / 2, 250);

    // Team 2 score/wickets (below team 2 name)
    ss.str("");
    ss << team2Score << "/" << team2Wickets;
    team2ScoreText.setString(ss.str());
    sf::FloatRect score2Bounds = team2ScoreText.getLocalBounds();
    team2ScoreText.setPosition(440 - team2Bounds.width + (team2Bounds.width - score2Bounds.width) / 2, 250);
}

void MatchResultScreen::handleMouseMove(const sf::Vector2f &mousePos)
{
    if (continueButton.getGlobalBounds().contains(mousePos))
    {
        buttonHovered = true;
        continueButton.setFillColor(buttonHoverColor);
    }
    else
    {
        buttonHovered = false;
        continueButton.setFillColor(buttonColor);
    }
}

bool MatchResultScreen::handleMouseClick(const sf::Vector2f &mousePos)
{
    // Allow clicking anywhere to continue
    return true;
}

void MatchResultScreen::draw(sf::RenderWindow &window)
{
    window.draw(header);
    window.draw(headerText);
    window.draw(resultPanel);
    window.draw(winnerAnnouncementText);
    window.draw(team1NameText);
    window.draw(team2NameText);
    window.draw(team1ScoreText);
    window.draw(team2ScoreText);
    window.draw(continueButton);
    window.draw(continueButtonText);
}