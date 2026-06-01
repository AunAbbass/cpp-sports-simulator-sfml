#ifndef SCORECARD_HPP
#define SCORECARD_HPP

#include <vector>
#include "Player.hpp"

/**
 * @brief Holds full match details: runs, wickets, overs and player performance.
 */
class Scorecard 
{
    private:
        int teamAScore;
        int teamBScore;
        int teamAWickets;
        int teamBWickets;

        std::vector<Player> teamAPlayers;
        std::vector<Player> teamBPlayers;

        std::string resultText;

    public:
        Scorecard();

        void setTeamAPlayers(const std::vector<Player>& players);
        void setTeamBPlayers(const std::vector<Player>& players);

        void setTeamAScore(int runs, int wickets);
        void setTeamBScore(int runs, int wickets);

        void setResult(const std::string& text);

        int getTeamAScore() const;
        int getTeamBScore() const;

        const std::string& getResult() const;
};

#endif // SCORECARD_HPP
