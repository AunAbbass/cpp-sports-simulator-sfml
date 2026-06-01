#include "TeamRegistrationScreen.hpp"
#include <iostream>

TeamRegistrationScreen::TeamRegistrationScreen()
    : headerColor(sf::Color(62, 39, 35)), listBoxColor(sf::Color(240, 240, 240))
{
}

bool TeamRegistrationScreen::loadFont(const std::string &fontPath)
{
    return font.loadFromFile(fontPath);
}

void TeamRegistrationScreen::setupUI(float windowWidth, float windowHeight)
{
    // Header
    header.setSize(sf::Vector2f(windowWidth, 80));
    header.setPosition(0, 0);
    header.setFillColor(headerColor);

    headerText.setFont(font);
    headerText.setString("Registered Teams");
    headerText.setCharacterSize(28);
    headerText.setFillColor(sf::Color::White);
    sf::FloatRect headerBounds = headerText.getLocalBounds();
    headerText.setPosition((windowWidth - headerBounds.width) / 2, 25);

    // Teams list label
    teamsListLabel.setFont(font);
    teamsListLabel.setString("Teams Loaded from data.txt (Click to view players)");
    teamsListLabel.setCharacterSize(20);
    teamsListLabel.setFillColor(sf::Color::Black);
    teamsListLabel.setPosition(40, 100);

    // Teams list box
    teamsListBox.setSize(sf::Vector2f(480, 350));
    teamsListBox.setPosition(40, 140);
    teamsListBox.setFillColor(listBoxColor);
    teamsListBox.setOutlineThickness(2);
    teamsListBox.setOutlineColor(sf::Color(100, 100, 100));
}

void TeamRegistrationScreen::setTeams(const std::vector<std::string>& teamNames, 
                                      const std::vector<int>& playerCounts)
{
    this->teams = teamNames;
    this->playerCounts = playerCounts;
    updateTeamsList();
}

void TeamRegistrationScreen::updateTeamsList()
{
    teamTexts.clear();
    teamBoxes.clear();
    playerCountTexts.clear();

    float startY = 150;
    float itemHeight = 45;

    for (size_t i = 0; i < teams.size(); ++i)
    {
        // Team box
        sf::RectangleShape box(sf::Vector2f(470, itemHeight - 5));
        box.setPosition(45, startY + i * itemHeight);
        box.setFillColor(sf::Color::White);
        box.setOutlineThickness(1);
        box.setOutlineColor(sf::Color(150, 150, 150));
        teamBoxes.push_back(box);

        // Team name text
        sf::Text text;
        text.setFont(font);
        text.setString(teams[i]);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::Black);
        text.setPosition(55, startY + i * itemHeight + 10);
        teamTexts.push_back(text);

        // Player count text
        sf::Text playerText;
        playerText.setFont(font);
        if (i < playerCounts.size())
        {
            playerText.setString("(" + std::to_string(playerCounts[i]) + " players)");
        }
        else
        {
            playerText.setString("(0 players)");
        }
        playerText.setCharacterSize(16);
        playerText.setFillColor(sf::Color(100, 100, 100));
        playerText.setPosition(400, startY + i * itemHeight + 12);
        playerCountTexts.push_back(playerText);
    }
}

void TeamRegistrationScreen::handleMouseMove(const sf::Vector2f &mousePos)
{
    // Highlight team boxes on hover
    for (size_t i = 0; i < teamBoxes.size(); ++i)
    {
        if (teamBoxes[i].getGlobalBounds().contains(mousePos))
        {
            teamBoxes[i].setFillColor(sf::Color(240, 240, 255));
        }
        else
        {
            teamBoxes[i].setFillColor(sf::Color::White);
        }
    }
}

int TeamRegistrationScreen::handleMouseClick(const sf::Vector2f &mousePos)
{
    // Check if any team box clicked
    for (size_t i = 0; i < teamBoxes.size(); ++i)
    {
        if (teamBoxes[i].getGlobalBounds().contains(mousePos))
        {
            std::cout << "Team clicked: " << teams[i] << " (index: " << i << ")" << std::endl;
            return static_cast<int>(i); // Return the team index
        }
    }
    return -1; // No team clicked
}

void TeamRegistrationScreen::draw(sf::RenderWindow &window)
{
    window.draw(header);
    window.draw(headerText);
    window.draw(teamsListLabel);
    window.draw(teamsListBox);

    for (const auto &box : teamBoxes)
    {
        window.draw(box);
    }
    for (const auto &text : teamTexts)
    {
        window.draw(text);
    }
    for (const auto &playerText : playerCountTexts)
    {
        window.draw(playerText);
    }
}