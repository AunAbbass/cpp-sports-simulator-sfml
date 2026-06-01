#include "MatchFixturesScreen.hpp"

MatchFixturesScreen::MatchFixturesScreen()
    : headerColor(sf::Color(62, 39, 35)), tableHeaderColor(sf::Color(200, 200, 200)), tableRowColor(sf::Color::White), buttonColor(sf::Color(240, 240, 240)), buttonHoverColor(sf::Color(220, 220, 220)), nextButtonHovered(false), currentFixtureIndex(0)
{
}

bool MatchFixturesScreen::loadFont(const std::string &fontPath)
{
    return font.loadFromFile(fontPath);
}

void MatchFixturesScreen::setupUI(float windowWidth, float windowHeight)
{
    (void)windowHeight; // Suppress unused parameter warning

    // Header
    header.setSize(sf::Vector2f(windowWidth, 80));
    header.setPosition(0, 0);
    header.setFillColor(headerColor);

    headerText.setFont(font);
    headerText.setString("Match Fixtures");
    headerText.setCharacterSize(28);
    headerText.setFillColor(sf::Color::White);
    sf::FloatRect headerBounds = headerText.getLocalBounds();
    headerText.setPosition((windowWidth - headerBounds.width) / 2, 25);

    // Team A Header
    teamAHeader.setSize(sf::Vector2f(175, 40));
    teamAHeader.setPosition(20, 100);
    teamAHeader.setFillColor(tableHeaderColor);
    teamAHeader.setOutlineThickness(2);
    teamAHeader.setOutlineColor(sf::Color::Black);

    teamAText.setFont(font);
    teamAText.setString("Team A");
    teamAText.setCharacterSize(20);
    teamAText.setFillColor(sf::Color::Black);
    sf::FloatRect teamABounds = teamAText.getLocalBounds();
    teamAText.setPosition(20 + (175 - teamABounds.width) / 2, 110);

    // Team B Header
    teamBHeader.setSize(sf::Vector2f(175, 40));
    teamBHeader.setPosition(195, 100);
    teamBHeader.setFillColor(tableHeaderColor);
    teamBHeader.setOutlineThickness(2);
    teamBHeader.setOutlineColor(sf::Color::Black);

    teamBText.setFont(font);
    teamBText.setString("Team B");
    teamBText.setCharacterSize(20);
    teamBText.setFillColor(sf::Color::Black);
    sf::FloatRect teamBBounds = teamBText.getLocalBounds();
    teamBText.setPosition(195 + (175 - teamBBounds.width) / 2, 110);

    // Fixtures box
    fixturesBox.setSize(sf::Vector2f(350, 300));
    fixturesBox.setPosition(20, 140);
    fixturesBox.setFillColor(sf::Color::White);
    fixturesBox.setOutlineThickness(2);
    fixturesBox.setOutlineColor(sf::Color::Black);

    // Next match panel
    nextMatchPanel.setSize(sf::Vector2f(150, 200));
    nextMatchPanel.setPosition(390, 140);
    nextMatchPanel.setFillColor(sf::Color(240, 240, 240));
    nextMatchPanel.setOutlineThickness(2);
    nextMatchPanel.setOutlineColor(sf::Color::Black);

    nextMatchLabel.setFont(font);
    nextMatchLabel.setString("Next\nMatch");
    nextMatchLabel.setCharacterSize(22);
    nextMatchLabel.setFillColor(sf::Color::Black);
    nextMatchLabel.setPosition(420, 160);

    matchupText.setFont(font);
    matchupText.setString("... vs ...");
    matchupText.setCharacterSize(18);
    matchupText.setFillColor(sf::Color::Black);
    matchupText.setPosition(405, 240);

    // Next button
    nextButton.setSize(sf::Vector2f(120, 50));
    nextButton.setPosition(405, 280);
    nextButton.setFillColor(buttonColor);
    nextButton.setOutlineThickness(2);
    nextButton.setOutlineColor(sf::Color::Black);

    nextButtonText.setFont(font);
    nextButtonText.setString("Next");
    nextButtonText.setCharacterSize(20);
    nextButtonText.setFillColor(sf::Color::Black);
    sf::FloatRect nextBounds = nextButtonText.getLocalBounds();
    nextButtonText.setPosition(
        405 + (120 - nextBounds.width) / 2,
        280 + (50 - nextBounds.height) / 2 - 5);
}

void MatchFixturesScreen::generateFixtures(const std::vector<std::string> &teams)
{
    fixtures.clear();

    // Generate round-robin fixtures
    for (size_t i = 0; i < teams.size(); ++i)
    {
        for (size_t j = i + 1; j < teams.size(); ++j)
        {
            fixtures.push_back({teams[i], teams[j]});
        }
    }

    currentFixtureIndex = 0;
    updateFixturesList();

    if (!fixtures.empty())
    {
        matchupText.setString(fixtures[0].first + " vs " + fixtures[0].second);
        sf::FloatRect matchupBounds = matchupText.getLocalBounds();
        matchupText.setPosition(465 - matchupBounds.width / 2, 240);
    }
}

void MatchFixturesScreen::updateFixturesList()
{
    fixtureTexts.clear();
    fixtureBoxes.clear();

    float cellHeight = 50;
    float teamAX = 20;
    float teamBX = 195;
    float startY = 140;

    for (size_t i = 0; i < fixtures.size() && i < 6; ++i)
    {
        // Team A cell
        sf::RectangleShape cellA(sf::Vector2f(175, cellHeight));
        cellA.setPosition(teamAX, startY + i * cellHeight);
        cellA.setFillColor(tableRowColor);
        cellA.setOutlineThickness(1);
        cellA.setOutlineColor(sf::Color(150, 150, 150));
        fixtureBoxes.push_back(cellA);

        sf::Text textA;
        textA.setFont(font);
        textA.setString(fixtures[i].first);
        textA.setCharacterSize(16);
        textA.setFillColor(sf::Color::Black);
        textA.setPosition(teamAX + 10, startY + i * cellHeight + 15);
        fixtureTexts.push_back(textA);

        // Team B cell
        sf::RectangleShape cellB(sf::Vector2f(175, cellHeight));
        cellB.setPosition(teamBX, startY + i * cellHeight);
        cellB.setFillColor(tableRowColor);
        cellB.setOutlineThickness(1);
        cellB.setOutlineColor(sf::Color(150, 150, 150));
        fixtureBoxes.push_back(cellB);

        sf::Text textB;
        textB.setFont(font);
        textB.setString(fixtures[i].second);
        textB.setCharacterSize(16);
        textB.setFillColor(sf::Color::Black);
        textB.setPosition(teamBX + 10, startY + i * cellHeight + 15);
        fixtureTexts.push_back(textB);
    }
}

void MatchFixturesScreen::handleMouseMove(const sf::Vector2f &mousePos)
{
    if (nextButton.getGlobalBounds().contains(mousePos))
    {
        nextButtonHovered = true;
        nextButton.setFillColor(buttonHoverColor);
    }
    else
    {
        nextButtonHovered = false;
        nextButton.setFillColor(buttonColor);
    }
}

int MatchFixturesScreen::handleMouseClick(const sf::Vector2f &mousePos)
{
    if (nextButton.getGlobalBounds().contains(mousePos))
    {
        if (!fixtures.empty() && currentFixtureIndex < static_cast<int>(fixtures.size()))
        {
            return 1; // Next button was clicked
        }
    }
    return 0; // Nothing clicked
}

std::string MatchFixturesScreen::getCurrentMatchup() const
{
    if (!fixtures.empty() && currentFixtureIndex < static_cast<int>(fixtures.size()))
    {
        return fixtures[currentFixtureIndex].first + " vs " + fixtures[currentFixtureIndex].second;
    }
    return "... vs ...";
}

void MatchFixturesScreen::advanceToNextFixture()
{
    if (currentFixtureIndex < static_cast<int>(fixtures.size()))
    {
        currentFixtureIndex++;
        
        // Update the "Next Match" display
        if (currentFixtureIndex < static_cast<int>(fixtures.size()))
        {
            matchupText.setString(fixtures[currentFixtureIndex].first + " vs " + fixtures[currentFixtureIndex].second);
            sf::FloatRect matchupBounds = matchupText.getLocalBounds();
            matchupText.setPosition(465 - matchupBounds.width / 2, 240);
        }
        else
        {
            matchupText.setString("Tournament\nComplete!");
            sf::FloatRect matchupBounds = matchupText.getLocalBounds();
            matchupText.setPosition(465 - matchupBounds.width / 2, 240);
        }
    }
}

bool MatchFixturesScreen::hasMoreFixtures() const
{
    return currentFixtureIndex < static_cast<int>(fixtures.size());
}

void MatchFixturesScreen::draw(sf::RenderWindow &window)
{
    window.draw(header);
    window.draw(headerText);
    window.draw(teamAHeader);
    window.draw(teamAText);
    window.draw(teamBHeader);
    window.draw(teamBText);
    window.draw(fixturesBox);

    for (const auto &box : fixtureBoxes)
    {
        window.draw(box);
    }
    for (const auto &text : fixtureTexts)
    {
        window.draw(text);
    }

    window.draw(nextMatchPanel);
    window.draw(nextMatchLabel);
    window.draw(matchupText);
    window.draw(nextButton);
    window.draw(nextButtonText);
}