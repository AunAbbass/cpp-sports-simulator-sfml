#include "Scorecard.hpp"
#include <iostream>
#include <iomanip>

Scorecard :: Scorecard()
{
    teamAScore = 0;
    teamBScore = 0;
    teamAWickets = 0;
    teamBWickets = 0;
    resultText = "";
}

void Scorecard :: setTeamAPlayers(const std::vector<Player>& players)
{
    teamAPlayers = players;
}

void Scorecard :: setTeamBPlayers(const std::vector<Player>& players)
{
    teamBPlayers = players;
}

void Scorecard :: setTeamAScore(int runs, int wickets)
{
    teamAScore = runs;
    teamAWickets = wickets;
}

void Scorecard :: setTeamBScore(int runs, int wickets)
{
    teamBScore = runs;
    teamBWickets = wickets;
}

void Scorecard :: setResult(const std::string& text)
{
    resultText = text;
}

int Scorecard :: getTeamAScore() const
{
    return teamAScore;
}

int Scorecard :: getTeamBScore() const
{
    return teamBScore;
}

const std::string& Scorecard :: getResult() const
{
    return resultText;
}