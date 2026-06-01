#include "MainScreen.hpp"

MainScreen::MainScreen()
    : buttonColor(sf::Color(41, 128, 185)), buttonHoverColor(sf::Color(52, 152, 219)), headerColor(sf::Color(62, 39, 35)), hoveredButton(0)
{
}

bool MainScreen::loadFont(const std::string &fontPath)
{
    return font.loadFromFile(fontPath);
}

void MainScreen::setupUI(float windowWidth, float windowHeight)
{
    // Header setup
    header.setSize(sf::Vector2f(windowWidth, 80));
    header.setPosition(0, 0);
    header.setFillColor(headerColor);

    headerText.setFont(font);
    headerText.setString("Sports Tournament Simulator");
    headerText.setCharacterSize(28);
    headerText.setFillColor(sf::Color::White);
    sf::FloatRect headerBounds = headerText.getLocalBounds();
    headerText.setPosition((windowWidth - headerBounds.width) / 2, 25);

    // Button dimensions
    float buttonWidth = 300;
    float buttonHeight = 60;
    float centerX = (windowWidth - buttonWidth) / 2;
    float startY = 150;
    float spacing = 80;

    // Start Button
    startButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    startButton.setPosition(centerX, startY);
    startButton.setFillColor(buttonColor);

    startText.setFont(font);
    startText.setString("Start");
    startText.setCharacterSize(24);
    startText.setFillColor(sf::Color::White);
    sf::FloatRect startBounds = startText.getLocalBounds();
    startText.setPosition(
        centerX + (buttonWidth - startBounds.width) / 2,
        startY + (buttonHeight - startBounds.height) / 2 - 5);

    // View Teams Button
    viewTeamsButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    viewTeamsButton.setPosition(centerX, startY + spacing);
    viewTeamsButton.setFillColor(buttonColor);

    viewTeamsText.setFont(font);
    viewTeamsText.setString("View Teams");
    viewTeamsText.setCharacterSize(24);
    viewTeamsText.setFillColor(sf::Color::White);
    sf::FloatRect viewBounds = viewTeamsText.getLocalBounds();
    viewTeamsText.setPosition(
        centerX + (buttonWidth - viewBounds.width) / 2,
        startY + spacing + (buttonHeight - viewBounds.height) / 2 - 5);

    // Exit Button
    exitButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    exitButton.setPosition(centerX, startY + spacing * 2);
    exitButton.setFillColor(buttonColor);

    exitText.setFont(font);
    exitText.setString("Exit");
    exitText.setCharacterSize(24);
    exitText.setFillColor(sf::Color::White);
    sf::FloatRect exitBounds = exitText.getLocalBounds();
    exitText.setPosition(
        centerX + (buttonWidth - exitBounds.width) / 2,
        startY + spacing * 2 + (buttonHeight - exitBounds.height) / 2 - 5);
}

void MainScreen::handleMouseMove(const sf::Vector2f &mousePos)
{
    hoveredButton = 0;

    if (startButton.getGlobalBounds().contains(mousePos))
    {
        hoveredButton = 1;
        startButton.setFillColor(buttonHoverColor);
    }
    else
    {
        startButton.setFillColor(buttonColor);
    }

    if (viewTeamsButton.getGlobalBounds().contains(mousePos))
    {
        hoveredButton = 2;
        viewTeamsButton.setFillColor(buttonHoverColor);
    }
    else
    {
        viewTeamsButton.setFillColor(buttonColor);
    }

    if (exitButton.getGlobalBounds().contains(mousePos))
    {
        hoveredButton = 3;
        exitButton.setFillColor(buttonHoverColor);
    }
    else
    {
        exitButton.setFillColor(buttonColor);
    }
}

int MainScreen::handleMouseClick(const sf::Vector2f &mousePos)
{
    if (startButton.getGlobalBounds().contains(mousePos))
    {
        return 1; // Start clicked
    }
    if (viewTeamsButton.getGlobalBounds().contains(mousePos))
    {
        return 2; // View Teams clicked
    }
    if (exitButton.getGlobalBounds().contains(mousePos))
    {
        return 3; // Exit clicked
    }
    return 0; // No button clicked
}

void MainScreen::draw(sf::RenderWindow &window)
{
    window.draw(header);
    window.draw(headerText);
    window.draw(startButton);
    window.draw(startText);
    window.draw(viewTeamsButton);
    window.draw(viewTeamsText);
    window.draw(exitButton);
    window.draw(exitText);
}