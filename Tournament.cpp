#include "Tournament.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

Tournament::Tournament() : pointsTable(std::vector<Team*>()) {}

Tournament :: ~Tournament() {}

void Tournament::loadTeams(const std::vector<Team>& teamList)
{
    teams = teamList;
}

void Tournament::generateFixtures()
{
    matches.clear();
    size_t n = teams.size();
    
    for (size_t i = 0 ; i < n ; i++)
    {
        for (size_t j = i + 1 ; j < n ;j++)
        {
            matches.emplace_back(&teams[i], &teams[j]);
        }
    }
}

void Tournament::start()
{
    // Validate tournament setup
    if (teams.empty())
    {
        std::cout << "Error: No teams loaded. Cannot start tournament.\n";
        return;
    }

    if (matches.empty())
    {
        std::cout << "Error: No fixtures generated. Cannot start tournament.\n";
        return;
    }

    for (size_t matchNum = 0; matchNum < matches.size(); matchNum++)
    {
        matches[matchNum].simulate();
        matches[matchNum].printResult();  //links to smfl thingy
    }

    std::vector<Team*> teamPtrs;
    for (auto& team : teams)
    {
        teamPtrs.push_back(&team);
    }

    PointsTable finalTable(teamPtrs);
    finalTable.updateStandings();
    finalTable.printTable();
}

void Tournament :: printStandings() const
{
    if (teams.empty())
    {
        std::cout << "No teams in tournament.\n";
        return;
    }

    std::vector<Team*> teamPtrs;
    for (const auto& team : teams)
    {
        teamPtrs.push_back(const_cast<Team*>(&team));
    }

    PointsTable table(teamPtrs);
    table.updateStandings();
    table.printTable();
}