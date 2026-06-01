#include <SFML/Graphics.hpp>

// Core classes
#include "core/Tournament.hpp"
#include "core/Team.hpp"
#include "core/Player.hpp"
#include "core/Match.hpp"
#include "core/FileManager.hpp"
#include "core/PointsTable.hpp"
#include "core/Scorecard.hpp"

// UI classes
#include "ui/MainScreen.hpp"
#include "ui/TeamRegistrationScreen.hpp"
#include "ui/PlayerListScreen.hpp"
#include "ui/MatchFixturesScreen.hpp"
#include "ui/StandingsScreen.hpp"
#include "ui/InteractiveMatchScreen.hpp"
#include "ui/MatchResultScreen.hpp"
#include "ui/TournamentWinnerScreen.hpp"  // NEW

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

enum class GameState
{
    MAIN_MENU,
    TEAM_REGISTRATION,
    PLAYER_LIST,
    MATCH_FIXTURES,
    INTERACTIVE_MATCH,
    MATCH_RESULT,
    STANDINGS,
    TOURNAMENT_COMPLETE,  // Shows winner screen
    EXIT
};

int main()
{
    // Seed random number generator
    srand(static_cast<unsigned>(time(nullptr)));

    // Create window
    sf::RenderWindow window(sf::VideoMode(560, 500), "Sports Tournament Simulator");
    window.setFramerateLimit(60);

    GameState currentState = GameState::MAIN_MENU;

    // Initialize screens
    MainScreen mainScreen;
    TeamRegistrationScreen teamRegScreen;
    PlayerListScreen playerListScreen;
    MatchFixturesScreen fixturesScreen;
    StandingsScreen standingsScreen;
    InteractiveMatchScreen interactiveMatchScreen;
    MatchResultScreen matchResultScreen;
    TournamentWinnerScreen winnerScreen;  // NEW

    // Initialize core tournament system
    Tournament tournament;
    std::vector<Team> coreTeams;
    std::vector<Match> matches;
    size_t currentMatchIndex = 0;
    size_t totalMatches = 0;
    bool matchResultProcessed = false;

    // Load font
    if (!mainScreen.loadFont("assets/fonts/arial.ttf") ||
        !teamRegScreen.loadFont("assets/fonts/arial.ttf") ||
        !playerListScreen.loadFont("assets/fonts/arial.ttf") ||
        !fixturesScreen.loadFont("assets/fonts/arial.ttf") ||
        !standingsScreen.loadFont("assets/fonts/arial.ttf") ||
        !interactiveMatchScreen.loadFont("assets/fonts/arial.ttf") ||
        !matchResultScreen.loadFont("assets/fonts/arial.ttf") ||
        !winnerScreen.loadFont("assets/fonts/arial.ttf"))  // NEW
    {
        std::cerr << "Error: Could not load font 'assets/fonts/arial.ttf'" << std::endl;
        return -1;
    }

    // Setup UIs
    mainScreen.setupUI(560, 500);
    teamRegScreen.setupUI(560, 500);
    playerListScreen.setupUI(560, 500);
    fixturesScreen.setupUI(560, 500);
    standingsScreen.setupUI(560, 500);
    interactiveMatchScreen.setupUI(560, 500);
    matchResultScreen.setupUI(560, 500);
    winnerScreen.setupUI(560, 500);  // NEW

    // Auto-load teams from data.txt
    std::cout << "Loading teams from data\\data.txt..." << std::endl;
    try
    {
        coreTeams = FileManager::loadTeams("data/data.txt");
        if (!coreTeams.empty())
        {
            std::cout << "Successfully loaded " << coreTeams.size() << " teams:" << std::endl;
            for (const Team& team : coreTeams)
            {
                std::cout << "  - " << team.getName() << " (" << team.getPlayers().size() << " players)" << std::endl;
            }
        }
        else
        {
            std::cerr << "Warning: No teams loaded from file!" << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error loading teams: " << e.what() << std::endl;
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::MouseMoved)
            {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                switch (currentState)
                {
                case GameState::MAIN_MENU:
                    mainScreen.handleMouseMove(mousePos);
                    break;
                case GameState::TEAM_REGISTRATION:
                    teamRegScreen.handleMouseMove(mousePos);
                    break;
                case GameState::PLAYER_LIST:
                    playerListScreen.handleMouseMove(mousePos);
                    break;
                case GameState::MATCH_FIXTURES:
                    fixturesScreen.handleMouseMove(mousePos);
                    break;
                case GameState::MATCH_RESULT:
                    matchResultScreen.handleMouseMove(mousePos);
                    break;
                case GameState::TOURNAMENT_COMPLETE:  // NEW
                    winnerScreen.handleMouseMove(mousePos);
                    break;
                default:
                    break;
                }
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                    switch (currentState)
                    {
                    case GameState::MAIN_MENU:
                    {
                        int clicked = mainScreen.handleMouseClick(mousePos);
                        if (clicked == 1)
                        { // Start Tournament
                            std::cout << "Start button clicked" << std::endl;
                            
                            if (coreTeams.size() < 2)
                            {
                                std::cout << "Error: Need at least 2 teams to start tournament!" << std::endl;
                                std::cout << "Please check data/data.txt file." << std::endl;
                                break;
                            }

                            tournament.loadTeams(coreTeams);
                            tournament.generateFixtures();
                            
                            std::vector<std::string> teamNames;
                            for (const Team& team : coreTeams)
                            {
                                teamNames.push_back(team.getName());
                            }
                            fixturesScreen.generateFixtures(teamNames);
                            standingsScreen.initializeStandings(teamNames);
                            
                            currentMatchIndex = 0;
                            totalMatches = coreTeams.size() * (coreTeams.size() - 1) / 2;
                            currentState = GameState::MATCH_FIXTURES;
                            
                            std::cout << "Tournament initialized with " << coreTeams.size() << " teams" << std::endl;
                            std::cout << "Total matches to play: " << totalMatches << std::endl;
                        }
                        else if (clicked == 2)
                        { // View Teams
                            std::cout << "View Teams button clicked" << std::endl;
                            
                            std::vector<std::string> teamNames;
                            std::vector<int> playerCounts;
                            
                            for (const Team& team : coreTeams)
                            {
                                teamNames.push_back(team.getName());
                                playerCounts.push_back(team.getPlayers().size());
                            }
                            
                            teamRegScreen.setTeams(teamNames, playerCounts);
                            currentState = GameState::TEAM_REGISTRATION;
                        }
                        else if (clicked == 3)
                        { // Exit
                            std::cout << "Exit button clicked" << std::endl;
                            window.close();
                        }
                        break;
                    }
                    
                    case GameState::TEAM_REGISTRATION:
                    {
                        int teamIndex = teamRegScreen.handleMouseClick(mousePos);
                        if (teamIndex >= 0 && teamIndex < static_cast<int>(coreTeams.size()))
                        {
                            // Get the team's players
                            std::vector<std::string> playerNames;
                            for (const Player& p : coreTeams[teamIndex].getPlayers())
                            {
                                playerNames.push_back(p.getName());
                            }
                            
                            playerListScreen.setTeamPlayers(coreTeams[teamIndex].getName(), playerNames);
                            currentState = GameState::PLAYER_LIST;
                        }
                        break;
                    }
                    
                    case GameState::PLAYER_LIST:
                    {
                        int result = playerListScreen.handleMouseClick(mousePos);
                        if (result == 1)  // Back button clicked
                        {
                            currentState = GameState::TEAM_REGISTRATION;
                        }
                        break;
                    }
                    
                    case GameState::MATCH_FIXTURES:
                    {
                        int result = fixturesScreen.handleMouseClick(mousePos);
                        if (result == 1)
                        {
                            std::cout << "Starting match " << (currentMatchIndex + 1) << " of " << totalMatches << "..." << std::endl;
                            
                            std::string matchup = fixturesScreen.getCurrentMatchup();
                            standingsScreen.setCurrentMatchup(matchup);
                            
                            size_t vsPos = matchup.find(" vs ");
                            if (vsPos != std::string::npos)
                            {
                                std::string teamAName = matchup.substr(0, vsPos);
                                std::string teamBName = matchup.substr(vsPos + 4);
                                
                                std::vector<std::string> teamAPlayerNames;
                                std::vector<std::string> teamBPlayerNames;
                                
                                for (const Team& team : coreTeams)
                                {
                                    if (team.getName() == teamAName)
                                    {
                                        for (const Player& p : team.getPlayers())
                                        {
                                            teamAPlayerNames.push_back(p.getName());
                                        }
                                    }
                                    if (team.getName() == teamBName)
                                    {
                                        for (const Player& p : team.getPlayers())
                                        {
                                            teamBPlayerNames.push_back(p.getName());
                                        }
                                    }
                                }
                                
                                interactiveMatchScreen.initializeMatch(teamAName, teamBName,
                                                                      teamAPlayerNames, teamBPlayerNames);
                                matchResultProcessed = false;
                                currentState = GameState::INTERACTIVE_MATCH;
                            }
                        }
                        break;
                    }
                    
                    case GameState::MATCH_RESULT:
                    {
                        // Click anywhere to continue to standings
                        currentState = GameState::STANDINGS;
                        break;
                    }
                    
                    case GameState::STANDINGS:
                    {
                        if (currentMatchIndex < totalMatches)
                        {
                            std::cout << "Continuing to next match. Remaining: " 
                                    << (totalMatches - currentMatchIndex) << std::endl;
                            currentState = GameState::MATCH_FIXTURES;
                        }
                        else
                        {
                            std::cout << "All matches complete! Finding tournament winner..." << std::endl;
                            
                            // Find the team with most wins
                            Team* winner = nullptr;
                            int maxWins = -1;
                            
                            for (Team& team : coreTeams)
                            {
                                if (team.getWins() > maxWins)
                                {
                                    maxWins = team.getWins();
                                    winner = &team;
                                }
                            }
                            
                            if (winner != nullptr)
                            {
                                winnerScreen.setWinner(
                                    winner->getName(),
                                    winner->getWins(),
                                    winner->getLosses()
                                );
                            }
                            
                            currentState = GameState::TOURNAMENT_COMPLETE;
                        }
                        break;
                    }
                    
                    case GameState::TOURNAMENT_COMPLETE:  // NEW
                    {
                        int result = winnerScreen.handleMouseClick(mousePos);
                        if (result == 1)  // Return to main menu
                        {
                            std::cout << "Returning to main menu." << std::endl;
                            currentState = GameState::MAIN_MENU;
                        }
                        break;
                    }
                    
                    default:
                        break;
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (currentState == GameState::INTERACTIVE_MATCH)
                {
                    interactiveMatchScreen.handleKeyPress(event.key.code);
                    
                    if (interactiveMatchScreen.isMatchComplete() && !matchResultProcessed)
                    {
                        std::cout << "Match complete!" << std::endl;
                        
                        std::string winner = interactiveMatchScreen.getWinner();
                        std::cout << "Winner: " << winner << std::endl;
                        
                        std::string matchup = fixturesScreen.getCurrentMatchup();
                        size_t vsPos = matchup.find(" vs ");
                        std::string teamAName = matchup.substr(0, vsPos);
                        std::string teamBName = matchup.substr(vsPos + 4);
                        
                        std::string loser = (winner == teamAName) ? teamBName : teamAName;
                        
                        // Get scores and wickets for both teams (in original order)
                        int teamAScore = interactiveMatchScreen.getTeamAScore();
                        int teamBScore = interactiveMatchScreen.getTeamBScore();
                        int teamAWickets = interactiveMatchScreen.getTeamAWickets();
                        int teamBWickets = interactiveMatchScreen.getTeamBWickets();
                        
                        // Update team stats
                        for (Team& team : coreTeams)
                        {
                            if (team.getName() == winner)
                            {
                                team.addWin();
                                team.incrementMatches();
                            }
                            else if (team.getName() == loser)
                            {
                                team.addLoss();
                                team.incrementMatches();
                            }
                        }
                        
                        standingsScreen.recordMatchResult(winner, loser);
                        
                        currentMatchIndex++;
                        fixturesScreen.advanceToNextFixture();
                        
                        std::cout << "Matches completed: " << currentMatchIndex << "/" << totalMatches << std::endl;
                        
                        matchResultProcessed = true;
                        
                        // Set up match result screen - pass teams in original order (A, B)
                        matchResultScreen.setMatchResult(teamAName, teamBName, 
                                                        teamAScore, teamBScore,
                                                        teamAWickets, teamBWickets);
                        
                        if (currentMatchIndex >= totalMatches)
                        {
                            std::cout << "\n=== TOURNAMENT COMPLETE ===" << std::endl;
                            
                            try
                            {
                                FileManager::saveTeams(coreTeams, "data/final_results.txt");
                                std::cout << "Results saved to data/final_results.txt" << std::endl;
                            }
                            catch (...)
                            {
                                std::cout << "Could not save results" << std::endl;
                            }
                        }
                    }
                }
                
                if (event.key.code == sf::Keyboard::Escape)
                {
                    if (currentState == GameState::INTERACTIVE_MATCH)
                    {
                        if (interactiveMatchScreen.isMatchComplete())
                        {
                            currentState = GameState::MATCH_RESULT;
                        }
                    }
                    else if (currentState == GameState::PLAYER_LIST)
                    {
                        std::cout << "ESC pressed - returning to team registration" << std::endl;
                        currentState = GameState::TEAM_REGISTRATION;
                    }
                    else if (currentState == GameState::TOURNAMENT_COMPLETE)  // NEW
                    {
                        std::cout << "ESC pressed - returning to main menu" << std::endl;
                        currentState = GameState::MAIN_MENU;
                    }
                    else if (currentState != GameState::MAIN_MENU)
                    {
                        std::cout << "ESC pressed - returning to main menu" << std::endl;
                        currentState = GameState::MAIN_MENU;
                    }
                }
            }
        }

        window.clear(sf::Color(200, 200, 200));

        switch (currentState)
        {
        case GameState::MAIN_MENU:
            mainScreen.draw(window);
            break;
        case GameState::TEAM_REGISTRATION:
            teamRegScreen.draw(window);
            break;
        case GameState::PLAYER_LIST:
            playerListScreen.draw(window);
            break;
        case GameState::MATCH_FIXTURES:
            fixturesScreen.draw(window);
            break;
        case GameState::INTERACTIVE_MATCH:
            interactiveMatchScreen.draw(window);
            break;
        case GameState::MATCH_RESULT:
            matchResultScreen.draw(window);
            break;
        case GameState::STANDINGS:
            standingsScreen.draw(window);
            break;
        case GameState::TOURNAMENT_COMPLETE:  // NEW - Shows winner screen
            winnerScreen.draw(window);
            break;
        default:
            break;
        }

        window.display();
    }

    return 0;
}