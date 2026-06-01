#include "StandingsScreen.hpp"
#include <algorithm>

StandingsScreen::StandingsScreen()
    : headerColor(sf::Color(62, 39, 35)), tableHeaderColor(sf::Color(200, 200, 200)), tableRowColor(sf::Color::White), panelColor(sf::Color(200, 200, 200)), currentMatchup("... vs ...")
{
}

bool StandingsScreen::loadFont(const std::string &fontPath)
{
    return font.loadFromFile(fontPath);
}

void StandingsScreen::setupUI(float windowWidth, float windowHeight)
{
    (void)windowHeight; // Suppress unused parameter warning

    // Header
    header.setSize(sf::Vector2f(windowWidth, 80));
    header.setPosition(0, 0);
    header.setFillColor(headerColor);

    headerText.setFont(font);
    headerText.setString("Standings");
    headerText.setCharacterSize(28);
    headerText.setFillColor(sf::Color::White);
    sf::FloatRect headerBounds = headerText.getLocalBounds();
    headerText.setPosition((windowWidth - headerBounds.width) / 2, 25);

    // Table headers
    float headerY = 100;
    float headerHeight = 40;
    float col1X = 20;
    float col1W = 200;
    float col2X = col1X + col1W;
    float col2W = 110;
    float col3X = col2X + col2W;
    float col3W = 110;
    float col4X = col3X + col3W;
    float col4W = 110;

    // Team header
    teamHeader.setSize(sf::Vector2f(col1W, headerHeight));
    teamHeader.setPosition(col1X, headerY);
    teamHeader.setFillColor(tableHeaderColor);
    teamHeader.setOutlineThickness(2);
    teamHeader.setOutlineColor(sf::Color::Black);

    teamHeaderText.setFont(font);
    teamHeaderText.setString("Team");
    teamHeaderText.setCharacterSize(20);
    teamHeaderText.setFillColor(sf::Color::Black);
    sf::FloatRect teamBounds = teamHeaderText.getLocalBounds();
    teamHeaderText.setPosition(col1X + (col1W - teamBounds.width) / 2, headerY + 10);

    // Played header
    playedHeader.setSize(sf::Vector2f(col2W, headerHeight));
    playedHeader.setPosition(col2X, headerY);
    playedHeader.setFillColor(tableHeaderColor);
    playedHeader.setOutlineThickness(2);
    playedHeader.setOutlineColor(sf::Color::Black);

    playedHeaderText.setFont(font);
    playedHeaderText.setString("Played");
    playedHeaderText.setCharacterSize(20);
    playedHeaderText.setFillColor(sf::Color::Black);
    sf::FloatRect playedBounds = playedHeaderText.getLocalBounds();
    playedHeaderText.setPosition(col2X + (col2W - playedBounds.width) / 2, headerY + 10);

    // Won header
    wonHeader.setSize(sf::Vector2f(col3W, headerHeight));
    wonHeader.setPosition(col3X, headerY);
    wonHeader.setFillColor(tableHeaderColor);
    wonHeader.setOutlineThickness(2);
    wonHeader.setOutlineColor(sf::Color::Black);

    wonHeaderText.setFont(font);
    wonHeaderText.setString("Won");
    wonHeaderText.setCharacterSize(20);
    wonHeaderText.setFillColor(sf::Color::Black);
    sf::FloatRect wonBounds = wonHeaderText.getLocalBounds();
    wonHeaderText.setPosition(col3X + (col3W - wonBounds.width) / 2, headerY + 10);

    // Points header
    pointsHeader.setSize(sf::Vector2f(col4W, headerHeight));
    pointsHeader.setPosition(col4X, headerY);
    pointsHeader.setFillColor(tableHeaderColor);
    pointsHeader.setOutlineThickness(2);
    pointsHeader.setOutlineColor(sf::Color::Black);

    pointsHeaderText.setFont(font);
    pointsHeaderText.setString("Points");
    pointsHeaderText.setCharacterSize(20);
    pointsHeaderText.setFillColor(sf::Color::Black);
    sf::FloatRect pointsBounds = pointsHeaderText.getLocalBounds();
    pointsHeaderText.setPosition(col4X + (col4W - pointsBounds.width) / 2, headerY + 10);

    // Table box
    tableBox.setSize(sf::Vector2f(col1W + col2W + col3W + col4W, 200));
    tableBox.setPosition(col1X, headerY + headerHeight);
    tableBox.setFillColor(sf::Color::White);
    tableBox.setOutlineThickness(2);
    tableBox.setOutlineColor(sf::Color::Black);

    // Next Match panel
    nextMatchPanel.setSize(sf::Vector2f(windowWidth - 40, 100));
    nextMatchPanel.setPosition(20, 350);
    nextMatchPanel.setFillColor(panelColor);
    nextMatchPanel.setOutlineThickness(2);
    nextMatchPanel.setOutlineColor(sf::Color::Black);

    nextMatchLabel.setFont(font);
    nextMatchLabel.setString("Last Match");
    nextMatchLabel.setCharacterSize(24);
    nextMatchLabel.setFillColor(sf::Color::Black);
    sf::FloatRect nextBounds = nextMatchLabel.getLocalBounds();
    nextMatchLabel.setPosition((windowWidth - nextBounds.width) / 2, 380);

    matchupText.setFont(font);
    matchupText.setString(currentMatchup);
    matchupText.setCharacterSize(20);
    matchupText.setFillColor(sf::Color::Black);
    sf::FloatRect matchupBounds = matchupText.getLocalBounds();
    matchupText.setPosition((windowWidth - matchupBounds.width) / 2, 415);
}

void StandingsScreen::initializeStandings(const std::vector<std::string> &teams)
{
    standings.clear();
    for (const auto &team : teams)
    {
        standings[team] = TeamStats(team);
    }
    updateStandings();
}

void StandingsScreen::updateStandings()
{
    standingsTexts.clear();
    standingsBoxes.clear();

    // Convert map to vector for sorting
    std::vector<TeamStats> sortedStandings;
    for (const auto &pair : standings)
    {
        sortedStandings.push_back(pair.second);
    }

    // Sort by points (descending), then by wins (descending)
    std::sort(sortedStandings.begin(), sortedStandings.end(),
              [](const TeamStats &a, const TeamStats &b)
              {
                  if (a.points != b.points)
                      return a.points > b.points;
                  return a.won > b.won;
              });

    float cellHeight = 40;
    float startY = 140;
    float col1X = 20;
    float col1W = 200;
    float col2X = col1X + col1W;
    float col2W = 110;
    float col3X = col2X + col2W;
    float col3W = 110;
    float col4X = col3X + col3W;
    float col4W = 110;

    for (size_t i = 0; i < sortedStandings.size() && i < 5; ++i)
    {
        float rowY = startY + i * cellHeight;

        // Team name cell
        sf::RectangleShape cell1(sf::Vector2f(col1W, cellHeight));
        cell1.setPosition(col1X, rowY);
        cell1.setFillColor(tableRowColor);
        cell1.setOutlineThickness(1);
        cell1.setOutlineColor(sf::Color(150, 150, 150));
        standingsBoxes.push_back(cell1);

        sf::Text text1;
        text1.setFont(font);
        text1.setString(sortedStandings[i].name);
        text1.setCharacterSize(16);
        text1.setFillColor(sf::Color::Black);
        text1.setPosition(col1X + 10, rowY + 10);
        standingsTexts.push_back(text1);

        // Played cell
        sf::RectangleShape cell2(sf::Vector2f(col2W, cellHeight));
        cell2.setPosition(col2X, rowY);
        cell2.setFillColor(tableRowColor);
        cell2.setOutlineThickness(1);
        cell2.setOutlineColor(sf::Color(150, 150, 150));
        standingsBoxes.push_back(cell2);

        sf::Text text2;
        text2.setFont(font);
        text2.setString(std::to_string(sortedStandings[i].played));
        text2.setCharacterSize(16);
        text2.setFillColor(sf::Color::Black);
        sf::FloatRect bounds2 = text2.getLocalBounds();
        text2.setPosition(col2X + (col2W - bounds2.width) / 2, rowY + 10);
        standingsTexts.push_back(text2);

        // Won cell
        sf::RectangleShape cell3(sf::Vector2f(col3W, cellHeight));
        cell3.setPosition(col3X, rowY);
        cell3.setFillColor(tableRowColor);
        cell3.setOutlineThickness(1);
        cell3.setOutlineColor(sf::Color(150, 150, 150));
        standingsBoxes.push_back(cell3);

        sf::Text text3;
        text3.setFont(font);
        text3.setString(std::to_string(sortedStandings[i].won));
        text3.setCharacterSize(16);
        text3.setFillColor(sf::Color::Black);
        sf::FloatRect bounds3 = text3.getLocalBounds();
        text3.setPosition(col3X + (col3W - bounds3.width) / 2, rowY + 10);
        standingsTexts.push_back(text3);

        // Points cell
        sf::RectangleShape cell4(sf::Vector2f(col4W, cellHeight));
        cell4.setPosition(col4X, rowY);
        cell4.setFillColor(tableRowColor);
        cell4.setOutlineThickness(1);
        cell4.setOutlineColor(sf::Color(150, 150, 150));
        standingsBoxes.push_back(cell4);

        sf::Text text4;
        text4.setFont(font);
        text4.setString(std::to_string(sortedStandings[i].points));
        text4.setCharacterSize(16);
        text4.setFillColor(sf::Color::Black);
        sf::FloatRect bounds4 = text4.getLocalBounds();
        text4.setPosition(col4X + (col4W - bounds4.width) / 2, rowY + 10);
        standingsTexts.push_back(text4);
    }
}

void StandingsScreen::setCurrentMatchup(const std::string &matchup)
{
    currentMatchup = matchup;
    matchupText.setString(matchup);
    sf::FloatRect bounds = matchupText.getLocalBounds();
    matchupText.setPosition((560 - bounds.width) / 2, 415);
}

void StandingsScreen::recordMatchResult(const std::string &winner, const std::string &loser)
{
    // Update winner
    if (standings.find(winner) != standings.end())
    {
        standings[winner].played++;
        standings[winner].won++;
        standings[winner].points += 3; // 3 points for a win
    }
    
    // Update loser
    if (standings.find(loser) != standings.end())
    {
        standings[loser].played++;
        // Loser gets 0 points
    }
    
    updateStandings();
}

void StandingsScreen::draw(sf::RenderWindow &window)
{
    window.draw(header);
    window.draw(headerText);

    window.draw(teamHeader);
    window.draw(teamHeaderText);
    window.draw(playedHeader);
    window.draw(playedHeaderText);
    window.draw(wonHeader);
    window.draw(wonHeaderText);
    window.draw(pointsHeader);
    window.draw(pointsHeaderText);

    window.draw(tableBox);

    for (const auto &box : standingsBoxes)
    {
        window.draw(box);
    }
    for (const auto &text : standingsTexts)
    {
        window.draw(text);
    }

    window.draw(nextMatchPanel);
    window.draw(nextMatchLabel);
    window.draw(matchupText);
}