#ifndef TEAM_HPP
#define TEAM_HPP

#include <string>
#include <vector>
#include "Player.hpp"

/**
 * @brief Represents a cricket team with players and tournament statistics.
 */
class Team 
{
    private:
        std::string name;
        std::vector<Player> players;

        int matchesPlayed;
        int wins;
        int losses;
        int ties;
        int points;
        int runsScored;
        int runsConceded;

    public:
        Team();
        Team(const std::string& name);

        void addPlayer(const Player& p);
        void addPlayers(const std::vector<Player>& newPlayers);

        // Stat updates
        void addWin();
        void addLoss();
        void addTie();
        void addRunsScored(int r);
        void addRunsConceded(int r);

        void incrementMatches();

        // Getters
        const std::string& getName() const;
        int getPoints() const;
        int getWins() const;
        int getLosses() const;
        int getTies() const;
        int getRunsScored() const;
        int getRunsConceded() const;

        const std::vector<Player>& getPlayers() const;
};

#endif // TEAM_HPP
