#include "TournamentWinnerScreen.hpp"
#include <iostream>

TournamentWinnerScreen::TournamentWinnerScreen()
    : backgroundColor(sf::Color(240, 240, 240)),
      returnButtonHovered(false),
      windowWidth(560),
      windowHeight(500),
      wins(0),
      losses(0)
{
}

bool TournamentWinnerScreen::loadFont(const std::string &fontPath)
{
    return font.loadFromFile(fontPath);
}

void TournamentWinnerScreen::setupUI(float width, float height)
{
    windowWidth = width;
    windowHeight = height;
    
    // Winner Label
    winnerLabelText.setFont(font);
    winnerLabelText.setString("Winner:");
    winnerLabelText.setCharacterSize(32);
    winnerLabelText.setFillColor(sf::Color::Black);
    sf::FloatRect winnerLabelBounds = winnerLabelText.getLocalBounds();
    winnerLabelText.setPosition((windowWidth - winnerLabelBounds.width) / 2, 100);
    
    // Winner Name
    winnerNameText.setFont(font);
    winnerNameText.setCharacterSize(36);
    winnerNameText.setFillColor(sf::Color::Black);
    winnerNameText.setStyle(sf::Text::Bold);
    
    // Wins Label
    winsLabelText.setFont(font);
    winsLabelText.setString("Wins:");
    winsLabelText.setCharacterSize(28);
    winsLabelText.setFillColor(sf::Color::Black);
    sf::FloatRect winsLabelBounds = winsLabelText.getLocalBounds();
    winsLabelText.setPosition((windowWidth - winsLabelBounds.width) / 2, 220);
    
    // Wins Value
    winsValueText.setFont(font);
    winsValueText.setCharacterSize(28);
    winsValueText.setFillColor(sf::Color::Black);
    
    // Loss Label
    lossLabelText.setFont(font);
    lossLabelText.setString("Loss:");
    lossLabelText.setCharacterSize(28);
    lossLabelText.setFillColor(sf::Color::Black);
    sf::FloatRect lossLabelBounds = lossLabelText.getLocalBounds();
    lossLabelText.setPosition((windowWidth - lossLabelBounds.width) / 2, 280);
    
    // Loss Value
    lossValueText.setFont(font);
    lossValueText.setCharacterSize(28);
    lossValueText.setFillColor(sf::Color::Black);
    
    // Return button
    returnButton.setSize(sf::Vector2f(220, 45));
    returnButton.setPosition((windowWidth - 220) / 2, windowHeight - 80);
    returnButton.setFillColor(sf::Color(100, 100, 100));
    returnButton.setOutlineThickness(2);
    returnButton.setOutlineColor(sf::Color(70, 70, 70));

    returnButtonText.setFont(font);
    returnButtonText.setString("Return to Main Menu");
    returnButtonText.setCharacterSize(20);
    returnButtonText.setFillColor(sf::Color::White);
    sf::FloatRect buttonTextBounds = returnButtonText.getLocalBounds();
    returnButtonText.setPosition(
        (windowWidth - buttonTextBounds.width) / 2,
        windowHeight - 72
    );
}

void TournamentWinnerScreen::setWinner(const std::string& teamName, int w, int l)
{
    winnerName = teamName;
    wins = w;
    losses = l;
    
    std::cout << "\n========================================" << std::endl;
    std::cout << "    TOURNAMENT WINNER: " << winnerName << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Wins: " << wins << " | Losses: " << losses << std::endl;
    std::cout << "========================================\n" << std::endl;
    
    updateDisplay();
}

void TournamentWinnerScreen::updateDisplay()
{
    // Update winner name
    winnerNameText.setString(winnerName);
    sf::FloatRect nameBounds = winnerNameText.getLocalBounds();
    winnerNameText.setPosition((windowWidth - nameBounds.width) / 2, 150);
    
    // Update wins value
    winsValueText.setString(std::to_string(wins));
    sf::FloatRect winsValueBounds = winsValueText.getLocalBounds();
    winsValueText.setPosition((windowWidth - winsValueBounds.width) / 2, 260);
    
    // Update loss value
    lossValueText.setString(std::to_string(losses));
    sf::FloatRect lossValueBounds = lossValueText.getLocalBounds();
    lossValueText.setPosition((windowWidth - lossValueBounds.width) / 2, 320);
}

void TournamentWinnerScreen::handleMouseMove(const sf::Vector2f &mousePos)
{
    // Check return button hover
    if (returnButton.getGlobalBounds().contains(mousePos))
    {
        if (!returnButtonHovered)
        {
            returnButton.setFillColor(sf::Color(130, 130, 130));
            returnButtonHovered = true;
        }
    }
    else
    {
        if (returnButtonHovered)
        {
            returnButton.setFillColor(sf::Color(100, 100, 100));
            returnButtonHovered = false;
        }
    }
}

int TournamentWinnerScreen::handleMouseClick(const sf::Vector2f &mousePos)
{
    // Check if return button clicked
    if (returnButton.getGlobalBounds().contains(mousePos))
    {
        std::cout << "Returning to main menu from winner screen" << std::endl;
        return 1; // Return to main menu
    }
    return 0;
}

void TournamentWinnerScreen::draw(sf::RenderWindow &window)
{
    // Draw all text elements
    window.draw(winnerLabelText);
    window.draw(winnerNameText);
    window.draw(winsLabelText);
    window.draw(winsValueText);
    window.draw(lossLabelText);
    window.draw(lossValueText);
    
    // Draw return button
    window.draw(returnButton);
    window.draw(returnButtonText);
}