#include "PlayerListScreen.hpp"
#include <iostream>

PlayerListScreen::PlayerListScreen()
    : headerColor(sf::Color(62, 39, 35)),
      backgroundColor(sf::Color(240, 240, 240)),
      backButtonHovered(false),
      windowWidth(560),
      windowHeight(500)
{
}

bool PlayerListScreen::loadFont(const std::string &fontPath)
{
    return font.loadFromFile(fontPath);
}

void PlayerListScreen::setupUI(float width, float height)
{
    windowWidth = width;
    windowHeight = height;
    
    // Header
    header.setSize(sf::Vector2f(windowWidth, 80));
    header.setPosition(0, 0);
    header.setFillColor(headerColor);

    headerText.setFont(font);
    headerText.setString("Team Players");
    headerText.setCharacterSize(28);
    headerText.setFillColor(sf::Color::White);
    headerText.setStyle(sf::Text::Bold);
    sf::FloatRect headerBounds = headerText.getLocalBounds();
    headerText.setPosition((windowWidth - headerBounds.width) / 2, 15);
    
    // Team name text (will be updated later)
    teamNameText.setFont(font);
    teamNameText.setCharacterSize(20);
    teamNameText.setFillColor(sf::Color::White);
    teamNameText.setPosition(40, 50);

    // Back button
    backButton.setSize(sf::Vector2f(100, 35));
    backButton.setPosition(40, 95);
    backButton.setFillColor(sf::Color(100, 100, 100));
    backButton.setOutlineThickness(2);
    backButton.setOutlineColor(sf::Color(70, 70, 70));

    backButtonText.setFont(font);
    backButtonText.setString("< Back");
    backButtonText.setCharacterSize(18);
    backButtonText.setFillColor(sf::Color::White);
    backButtonText.setPosition(55, 100);

    // Player list box
    playerListBox.setSize(sf::Vector2f(480, 350));
    playerListBox.setPosition(40, 140);
    playerListBox.setFillColor(backgroundColor);
    playerListBox.setOutlineThickness(2);
    playerListBox.setOutlineColor(sf::Color(100, 100, 100));
}

void PlayerListScreen::setTeamPlayers(const std::string& teamName, const std::vector<std::string>& players)
{
    currentTeamName = teamName;
    playerNames = players;
    
    // Update team name in header
    teamNameText.setString(teamName);
    sf::FloatRect bounds = teamNameText.getLocalBounds();
    teamNameText.setPosition((windowWidth - bounds.width) / 2, 50);
    
    std::cout << "\n=== PlayerListScreen::setTeamPlayers ===" << std::endl;
    std::cout << "Team: " << teamName << std::endl;
    std::cout << "Number of players: " << players.size() << std::endl;
    for (size_t i = 0; i < players.size(); ++i)
    {
        std::cout << "  " << (i+1) << ". " << players[i] << std::endl;
    }
    std::cout << "========================================\n" << std::endl;
    
    updatePlayerList();
}

void PlayerListScreen::updatePlayerList()
{
    playerBoxes.clear();
    playerNameTexts.clear();
    playerNumberTexts.clear();

    float startY = 150;
    float itemHeight = 32;
    float boxWidth = 470;
    float boxHeight = itemHeight - 2;

    for (size_t i = 0; i < playerNames.size(); ++i)
    {
        float yPos = startY + i * itemHeight;
        
        // Player box background
        sf::RectangleShape box(sf::Vector2f(boxWidth, boxHeight));
        box.setPosition(45, yPos);
        box.setFillColor(sf::Color::White);
        box.setOutlineThickness(1);
        box.setOutlineColor(sf::Color(180, 180, 180));
        playerBoxes.push_back(box);

        // Player number
        sf::Text numberText;
        numberText.setFont(font);
        numberText.setString(std::to_string(i + 1) + ".");
        numberText.setCharacterSize(18);
        numberText.setFillColor(sf::Color(80, 80, 80));
        numberText.setStyle(sf::Text::Bold);
        numberText.setPosition(55, yPos + 6);
        playerNumberTexts.push_back(numberText);

        // Player name
        sf::Text nameText;
        nameText.setFont(font);
        nameText.setString(playerNames[i]);
        nameText.setCharacterSize(18);
        nameText.setFillColor(sf::Color::Black);
        nameText.setPosition(90, yPos + 6);
        playerNameTexts.push_back(nameText);
    }
}

void PlayerListScreen::handleMouseMove(const sf::Vector2f &mousePos)
{
    // Check back button hover
    if (backButton.getGlobalBounds().contains(mousePos))
    {
        if (!backButtonHovered)
        {
            backButton.setFillColor(sf::Color(130, 130, 130));
            backButtonHovered = true;
        }
    }
    else
    {
        if (backButtonHovered)
        {
            backButton.setFillColor(sf::Color(100, 100, 100));
            backButtonHovered = false;
        }
    }
}

int PlayerListScreen::handleMouseClick(const sf::Vector2f &mousePos)
{
    // Check if back button clicked
    if (backButton.getGlobalBounds().contains(mousePos))
    {
        std::cout << "Back button clicked - returning to team list" << std::endl;
        return 1; // Return to previous screen
    }
    return 0;
}

void PlayerListScreen::draw(sf::RenderWindow &window)
{
    // Draw header
    window.draw(header);
    window.draw(headerText);
    window.draw(teamNameText);
    
    // Draw back button
    window.draw(backButton);
    window.draw(backButtonText);
    
    // Draw player list box
    window.draw(playerListBox);
    
    // Draw all player entries
    for (const auto &box : playerBoxes)
    {
        window.draw(box);
    }
    for (const auto &numberText : playerNumberTexts)
    {
        window.draw(numberText);
    }
    for (const auto &nameText : playerNameTexts)
    {
        window.draw(nameText);
    }
}