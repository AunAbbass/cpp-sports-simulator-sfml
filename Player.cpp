#include "Player.hpp"
#include <iostream>
#include <iomanip>

Player :: Player(const std :: string& nme)
{
    name = nme;
    runs = 0;
    ballsFaced = 0;
    fours = 0;
    sixes = 0;
    wickets = 0;
    oversBowled = 0;
    runsConceded = 0;
}

const std :: string& Player :: getName() const
{
    return name;
}

int Player :: getRuns() const
{
    return runs;
}

int Player :: getBallsFaced() const
{
    return ballsFaced;
}

void Player :: addRuns(int r)
{
    runs += r;
}

void Player :: faceBall()
{
    ballsFaced++;
}

void Player :: addFour()
{
    runs += 4;
    fours++;
    ballsFaced++;
}

void Player :: addSix()
{
    runs += 6;
    sixes++;
    ballsFaced++;
}

void Player :: addWicket()
{
    wickets++;
}

void Player :: bowlOver(int runs)
{
    oversBowled++;
    runsConceded += runs;
}

void Player :: resetStats()
{
    runs = 0;
    ballsFaced = 0;
    fours = 0;
    sixes = 0;
    wickets = 0;
    oversBowled = 0;
    runsConceded = 0;
}