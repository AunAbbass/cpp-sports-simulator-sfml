#ifndef TOURNAMENT_HPP
#define TOURNAMENT_HPP

#include <vector>
#include "Team.hpp"
#include "Match.hpp"
#include "PointsTable.hpp"

/**
 * @brief Controls tournament flow: teams, matches, standings.
 */
class Tournament 
{
    private:
        std::vector<Team> teams;
        std::vector<Match> matches;
        PointsTable pointsTable;

    public:
        Tournament();
        ~Tournament();

        void loadTeams(const std::vector<Team>& teamList);
        void generateFixtures();
        void start();

        void printStandings() const;
};

#endif // TOURNAMENT_HPP
