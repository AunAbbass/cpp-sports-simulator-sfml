#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

/**
 * @brief Represents an individual cricket player.
 */
class Player 
{
    private:
        std::string name;
        int runs;
        int ballsFaced;
        int fours;
        int sixes;
        int wickets;
        int oversBowled;
        int runsConceded;

    public:
        Player(const std::string& name);

        // Getters
        const std::string& getName() const;
        int getRuns() const;
        int getBallsFaced() const;

        // Update methods
        void addRuns(int r);
        void faceBall();
        void addFour();
        void addSix();

        void addWicket();
        void bowlOver(int runs);

        void resetStats();
};

#endif // PLAYER_HPP
