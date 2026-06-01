#include "InteractiveMatchScreen.hpp"
#include <sstream>
#include <iomanip>
#include <iostream>

InteractiveMatchScreen::InteractiveMatchScreen()
    : headerColor(sf::Color(62, 39, 35)), panelColor(sf::Color(240, 240, 240)),
      teamAName(""), teamBName(""),
      battingTeam(0), firstBattingTeam(0), currentInnings(0),
      totalScore(0), wickets(0), currentOver(0), ballInOver(0),
      firstInningsScore(0), firstInningsWickets(0),
      strikerIndex(0), nonStrikerIndex(1), bowlerIndex(0), nextBatsmanIndex(2),
      strikerRuns(0), strikerBalls(0), nonStrikerRuns(0), nonStrikerBalls(0),
      bowlerRunsConceded(0), bowlerWickets(0), bowlerOversBowled(0),
      targetScore(0), matchComplete(false), matchResult("")
{
}

bool InteractiveMatchScreen::loadFont(const std::string &fontPath)
{
    return font.loadFromFile(fontPath);
}

void InteractiveMatchScreen::setupUI(float windowWidth, float windowHeight)
{
    // Header
    header.setSize(sf::Vector2f(windowWidth, 80));
    header.setPosition(0, 0);
    header.setFillColor(headerColor);

    headerText.setFont(font);
    headerText.setString("Match in Progress");
    headerText.setCharacterSize(28);
    headerText.setFillColor(sf::Color::White);
    sf::FloatRect headerBounds = headerText.getLocalBounds();
    headerText.setPosition((windowWidth - headerBounds.width) / 2, 25);

    // Score panel
    scorePanel.setSize(sf::Vector2f(windowWidth - 40, 120));
    scorePanel.setPosition(20, 90);
    scorePanel.setFillColor(panelColor);
    scorePanel.setOutlineThickness(2);
    scorePanel.setOutlineColor(sf::Color::Black);

    teamANameText.setFont(font);
    teamANameText.setCharacterSize(20);
    teamANameText.setFillColor(sf::Color::Black);
    teamANameText.setPosition(30, 100);

    scoreText.setFont(font);
    scoreText.setCharacterSize(36);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition(30, 130);

    oversText.setFont(font);
    oversText.setCharacterSize(18);
    oversText.setFillColor(sf::Color::Black);
    oversText.setPosition(30, 180);

    // Batsman panel
    batsmanPanel.setSize(sf::Vector2f(windowWidth - 40, 100));
    batsmanPanel.setPosition(20, 220);
    batsmanPanel.setFillColor(sf::Color::White);
    batsmanPanel.setOutlineThickness(2);
    batsmanPanel.setOutlineColor(sf::Color::Black);

    strikerText.setFont(font);
    strikerText.setCharacterSize(18);
    strikerText.setFillColor(sf::Color::Black);
    strikerText.setPosition(30, 230);

    strikerStatsText.setFont(font);
    strikerStatsText.setCharacterSize(16);
    strikerStatsText.setFillColor(sf::Color(100, 100, 100));
    strikerStatsText.setPosition(30, 255);

    nonStrikerText.setFont(font);
    nonStrikerText.setCharacterSize(18);
    nonStrikerText.setFillColor(sf::Color::Black);
    nonStrikerText.setPosition(30, 280);

    nonStrikerStatsText.setFont(font);
    nonStrikerStatsText.setCharacterSize(16);
    nonStrikerStatsText.setFillColor(sf::Color(100, 100, 100));
    nonStrikerStatsText.setPosition(30, 305);

    // Bowler panel
    bowlerPanel.setSize(sf::Vector2f(windowWidth - 40, 60));
    bowlerPanel.setPosition(20, 330);
    bowlerPanel.setFillColor(panelColor);
    bowlerPanel.setOutlineThickness(2);
    bowlerPanel.setOutlineColor(sf::Color::Black);

    bowlerText.setFont(font);
    bowlerText.setCharacterSize(18);
    bowlerText.setFillColor(sf::Color::Black);
    bowlerText.setPosition(30, 340);

    bowlerStatsText.setFont(font);
    bowlerStatsText.setCharacterSize(16);
    bowlerStatsText.setFillColor(sf::Color(100, 100, 100));
    bowlerStatsText.setPosition(30, 365);

    // Controls panel
    controlsPanel.setSize(sf::Vector2f(windowWidth - 40, 80));
    controlsPanel.setPosition(20, 400);
    controlsPanel.setFillColor(sf::Color(220, 220, 220));
    controlsPanel.setOutlineThickness(2);
    controlsPanel.setOutlineColor(sf::Color::Black);

    instructionsText.setFont(font);
    instructionsText.setString("Press: 0, 1, 2, 3, 4, 6 for runs | W for wicket");
    instructionsText.setCharacterSize(16);
    instructionsText.setFillColor(sf::Color::Black);
    instructionsText.setPosition(30, 410);

    lastBallText.setFont(font);
    lastBallText.setCharacterSize(16);
    lastBallText.setFillColor(sf::Color::Black);
    lastBallText.setPosition(30, 435);

    currentOverText.setFont(font);
    currentOverText.setCharacterSize(14);
    currentOverText.setFillColor(sf::Color::Black);
    currentOverText.setPosition(30, 460);
}

void InteractiveMatchScreen::initializeMatch(const std::string& teamA, const std::string& teamB,
                                            const std::vector<std::string>& playersA,
                                            const std::vector<std::string>& playersB)
{
    teamAName = teamA;
    teamBName = teamB;
    teamAPlayers = playersA;
    teamBPlayers = playersB;

    battingTeam = 0;
    firstBattingTeam = 0; // Track which team batted first
    currentInnings = 0;
    totalScore = 0;
    wickets = 0;
    currentOver = 0;
    ballInOver = 0;
    
    firstInningsScore = 0;
    firstInningsWickets = 0;
    
    strikerIndex = 0;
    nonStrikerIndex = 1;
    bowlerIndex = 0;
    nextBatsmanIndex = 2;
    
    strikerRuns = 0;
    strikerBalls = 0;
    nonStrikerRuns = 0;
    nonStrikerBalls = 0;
    
    bowlerRunsConceded = 0;
    bowlerWickets = 0;
    bowlerOversBowled = 0;
    
    targetScore = 0;
    matchComplete = false;
    matchResult = "";
    overBalls.clear();

    updateDisplay();
}

void InteractiveMatchScreen::handleKeyPress(sf::Keyboard::Key key)
{
    if (matchComplete) return;

    switch (key)
    {
    case sf::Keyboard::Num0:
    case sf::Keyboard::Numpad0:
        processBall(0);
        break;
    case sf::Keyboard::Num1:
    case sf::Keyboard::Numpad1:
        processBall(1);
        break;
    case sf::Keyboard::Num2:
    case sf::Keyboard::Numpad2:
        processBall(2);
        break;
    case sf::Keyboard::Num3:
    case sf::Keyboard::Numpad3:
        processBall(3);
        break;
    case sf::Keyboard::Num4:
    case sf::Keyboard::Numpad4:
        processBall(4);
        break;
    case sf::Keyboard::Num6:
    case sf::Keyboard::Numpad6:
        processBall(6);
        break;
    case sf::Keyboard::W:
        processWicket();
        break;
    default:
        break;
    }
}

void InteractiveMatchScreen::processBall(int runs)
{
    totalScore += runs;
    strikerRuns += runs;
    strikerBalls++;
    bowlerRunsConceded += runs;
    
    ballInOver++;
    
    // Add to current over display
    overBalls.push_back(std::to_string(runs));
    
    std::stringstream ss;
    ss << "Last ball: " << runs << " run(s)";
    lastBallText.setString(ss.str());

    // Switch striker on odd runs
    if (runs % 2 == 1)
    {
        switchStriker();
    }

    // Check for end of over
    if (ballInOver == 6)
    {
        nextOver();
    }

    updateDisplay();
    checkMatchComplete();
}

void InteractiveMatchScreen::processWicket()
{
    wickets++;
    strikerBalls++;
    bowlerWickets++;
    ballInOver++;
    
    overBalls.push_back("W");
    lastBallText.setString("Last ball: WICKET!");

    // New batsman comes in
    auto& battingPlayers = (battingTeam == 0) ? teamAPlayers : teamBPlayers;

    if (nextBatsmanIndex < (int)battingPlayers.size() && wickets < 10)
    {
        strikerIndex = nextBatsmanIndex;
        nextBatsmanIndex++;
        strikerRuns = 0;
        strikerBalls = 0;
    }

    if (ballInOver == 6)
    {
        nextOver();
    }

    updateDisplay();
    checkMatchComplete();
}

void InteractiveMatchScreen::switchStriker()
{
    std::swap(strikerIndex, nonStrikerIndex);
    std::swap(strikerRuns, nonStrikerRuns);
    std::swap(strikerBalls, nonStrikerBalls);
}

void InteractiveMatchScreen::nextOver()
{
    currentOver++;
    ballInOver = 0;
    bowlerOversBowled++;
    overBalls.clear();
    
    // Switch striker at end of over
    switchStriker();
    
    // New bowler (simple rotation)
    if (battingTeam == 0)
    {
        bowlerIndex = (bowlerIndex + 1) % (int)teamBPlayers.size();
    }
    else
    {
        bowlerIndex = (bowlerIndex + 1) % (int)teamAPlayers.size();
    }
    
    bowlerRunsConceded = 0;
    bowlerWickets = 0;
    bowlerOversBowled = 0;
    
    // Check if innings complete (3 overs)
    if (currentOver >= 3)
    {
        nextInnings();
    }
}

void InteractiveMatchScreen::nextInnings()
{
    if (currentInnings == 0)
    {
        // Store first innings results
        firstInningsScore = totalScore;
        firstInningsWickets = wickets;
        
        // First innings complete
        targetScore = totalScore + 1;
        
        std::cout << "First innings complete. Team " << ((battingTeam == 0) ? teamAName : teamBName) 
                  << " scored " << totalScore << "/" << wickets << std::endl;
        std::cout << "Target: " << targetScore << std::endl;
        
        // Reset for second innings
        currentInnings = 1;
        battingTeam = 1 - battingTeam;
        totalScore = 0;
        wickets = 0;
        currentOver = 0;
        ballInOver = 0;
        
        strikerIndex = 0;
        nonStrikerIndex = 1;
        bowlerIndex = 0;
        nextBatsmanIndex = 2;
        
        strikerRuns = 0;
        strikerBalls = 0;
        nonStrikerRuns = 0;
        nonStrikerBalls = 0;
        
        bowlerRunsConceded = 0;
        bowlerWickets = 0;
        bowlerOversBowled = 0;
        
        overBalls.clear();
        
        std::stringstream ss;
        ss << "INNINGS BREAK - Target: " << targetScore;
        lastBallText.setString(ss.str());
    }
    else
    {
        // Match complete
        matchComplete = true;
        std::cout << "Match complete!" << std::endl;
    }
    
    updateDisplay();
}

void InteractiveMatchScreen::checkMatchComplete()
{
    if (wickets >= 10)
    {
        if (currentInnings == 0)
        {
            nextInnings();
        }
        else
        {
            matchComplete = true;
        }
    }
    
    if (currentInnings == 1 && totalScore >= targetScore)
    {
        matchComplete = true;
    }
}

void InteractiveMatchScreen::updateDisplay()
{
    // Update team name
    std::string battingTeamName = (battingTeam == 0) ? teamAName : teamBName;
    teamANameText.setString(battingTeamName);

    // Update score
    std::stringstream ss;
    ss << totalScore << "/" << wickets;
    scoreText.setString(ss.str());

    // Update overs
    ss.str("");
    ss << "Overs: " << currentOver << "." << ballInOver << "/3.0";
    if (currentInnings == 1)
    {
        ss << " | Target: " << targetScore;
    }
    oversText.setString(ss.str());

    // Update striker
    std::vector<std::string>& battingPlayers = (battingTeam == 0) ? teamAPlayers : teamBPlayers;
    ss.str("");
    ss << "* " << battingPlayers[strikerIndex] << " (Striker)";
    strikerText.setString(ss.str());

    ss.str("");
    ss << "   " << strikerRuns << " runs (" << strikerBalls << " balls)";
    strikerStatsText.setString(ss.str());

    // Update non-striker
    ss.str("");
    ss << "  " << battingPlayers[nonStrikerIndex];
    nonStrikerText.setString(ss.str());

    ss.str("");
    ss << "   " << nonStrikerRuns << " runs (" << nonStrikerBalls << " balls)";
    nonStrikerStatsText.setString(ss.str());

    // Update bowler
    std::vector<std::string>& bowlingPlayers = (battingTeam == 0) ? teamBPlayers : teamAPlayers;
    ss.str("");
    ss << "Bowler: " << bowlingPlayers[bowlerIndex];
    bowlerText.setString(ss.str());

    ss.str("");
    ss << bowlerOversBowled << "." << ballInOver << " overs, " 
       << bowlerRunsConceded << " runs, " << bowlerWickets << " wickets";
    bowlerStatsText.setString(ss.str());

    // Update current over
    ss.str("");
    ss << "This over: ";
    for (const std::string& ball : overBalls)
    {
        ss << ball << " ";
    }
    currentOverText.setString(ss.str());

    if (matchComplete)
    {
        instructionsText.setString("MATCH COMPLETE! Press ESC to continue");
    }
}

std::string InteractiveMatchScreen::getWinner() const
{
    // Determine winner based on final state
    if (currentInnings == 1)
    {
        // Second innings was played
        if (totalScore >= targetScore)
        {
            // Chasing team won
            return (battingTeam == 0) ? teamAName : teamBName;
        }
        else
        {
            // Chasing team lost, first batting team won
            return (battingTeam == 0) ? teamBName : teamAName;
        }
    }
    else
    {
        // Only first innings played (shouldn't happen)
        return (battingTeam == 0) ? teamAName : teamBName;
    }
}

// CORRECTED: Return Team A's final score
int InteractiveMatchScreen::getTeamAScore() const
{
    // Team A is always index 0
    if (firstBattingTeam == 0)
    {
        // Team A batted first, so their score is in firstInningsScore
        return firstInningsScore;
    }
    else
    {
        // Team A batted second, so their score is in totalScore (from second innings)
        return totalScore;
    }
}

// CORRECTED: Return Team B's final score
int InteractiveMatchScreen::getTeamBScore() const
{
    // Team B is always index 1
    if (firstBattingTeam == 1)
    {
        // Team B batted first, so their score is in firstInningsScore
        return firstInningsScore;
    }
    else
    {
        // Team B batted second, so their score is in totalScore (from second innings)
        return totalScore;
    }
}

// CORRECTED: Return Team A's final wickets
int InteractiveMatchScreen::getTeamAWickets() const
{
    if (firstBattingTeam == 0)
    {
        // Team A batted first
        return firstInningsWickets;
    }
    else
    {
        // Team A batted second
        return wickets;
    }
}

// CORRECTED: Return Team B's final wickets
int InteractiveMatchScreen::getTeamBWickets() const
{
    if (firstBattingTeam == 1)
    {
        // Team B batted first
        return firstInningsWickets;
    }
    else
    {
        // Team B batted second
        return wickets;
    }
}

void InteractiveMatchScreen::draw(sf::RenderWindow &window)
{
    window.draw(header);
    window.draw(headerText);
    window.draw(scorePanel);
    window.draw(teamANameText);
    window.draw(scoreText);
    window.draw(oversText);
    window.draw(batsmanPanel);
    window.draw(strikerText);
    window.draw(strikerStatsText);
    window.draw(nonStrikerText);
    window.draw(nonStrikerStatsText);
    window.draw(bowlerPanel);
    window.draw(bowlerText);
    window.draw(bowlerStatsText);
    window.draw(controlsPanel);
    window.draw(instructionsText);
    window.draw(lastBallText);
    window.draw(currentOverText);
}