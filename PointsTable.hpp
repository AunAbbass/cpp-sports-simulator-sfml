#ifndef POINTSTABLE_HPP
#define POINTSTABLE_HPP

#include <vector>
#include "Team.hpp"

/**
 * @brief Responsible for ranking teams based on points and run statistics.
 */
class PointsTable 
{
    private:
        std::vector<Team*> teams;

    public:
        PointsTable(const std::vector<Team*>& teams);

        void updateStandings();
        void printTable() const;
};

#endif // POINTSTABLE_HPP
