#ifndef MATCH_HPP
#define MATCH_HPP

#include <string>
#include "Team.hpp"
#include "Scorecard.hpp"

/**
 * @brief Represents a single cricket match between two teams.
 */
class Match 
{
    private:
        Team* teamA;
        Team* teamB;
        Scorecard scorecard;   // Each match has a scorecard
        std::string resultText;

    public:
        Match(Team* a, Team* b);

        /**
         * @brief Simulates the match by reading score input from file or user.
         * @param filename If not empty, loads the match score from file.
         */
        void simulate(const std::string& filename = "");

        /**
         * @brief Returns Team A.
         */
        Team* getTeamA() const;

        /**
         * @brief Returns Team B.
         */
        Team* getTeamB() const;

        /**
         * @brief Prints or returns the match result.
         */
        void printResult() const;

        /**
         * @brief Accessor for the scorecard.
         */
        const Scorecard& getScorecard() const;
};

#endif // MATCH_HPP
