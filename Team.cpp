#include "Team.hpp"
#include <iostream>
#include <iomanip>

Team :: Team() {}

Team :: Team(const std :: string& nme)
{
    name = nme;  //error resolved
    matchesPlayed = 0;
    wins = 0;
    losses = 0;
    ties = 0;
    points = 0;
    runsScored  = 0;
    runsConceded = 0;
}

void Team :: addPlayer(const Player& p) //might be redundant as we are adding them together (using addplayers) at start only
{
    players.push_back(p);
}

void Team::addPlayers(const std::vector<Player>& newPlayers)
{
    players = newPlayers;  
}

void Team :: addWin()
{
    wins++;
}

void Team :: addLoss()
{
    losses++;
}

void Team :: addTie()
{
    ties++;
}

void Team :: addRunsScored(int r)
{
    runsScored += r;;
}

void Team :: addRunsConceded(int r)
{
    runsConceded += r;
}

void Team :: incrementMatches()
{
    matchesPlayed++;
}

const std::string&  Team :: getName() const
{
    return name;
}

int Team :: getPoints() const
{
    return points;
}

int Team :: getWins() const
{
    return wins;
}

int Team :: getLosses() const
{
    return losses;
}

int Team :: getTies() const
{
    return ties;
}

int Team :: getRunsScored() const
{
    return runsScored;
}

int Team :: getRunsConceded() const
{
    return runsConceded;
}

const std :: vector<Player>& Team :: getPlayers() const
{
    return players;
}