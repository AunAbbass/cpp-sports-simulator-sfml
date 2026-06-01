#include "Match.hpp"
#include <iostream>


Match :: Match(Team* a, Team* b)
{
    teamA = a;
    teamB = b;
    resultText = "";
}

Team* Match :: getTeamA() const
{
    return teamA;
}

Team* Match :: getTeamB() const
{
    return teamB;
}

void Match :: simulate(const std::string& filename)
{
    //have to add
}

void Match :: printResult() const
{
    //have to add
}

const Scorecard& Match :: getScorecard() const
{
    return scorecard;
}