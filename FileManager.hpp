#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <string>
#include <vector>
#include "Team.hpp"
#include "Match.hpp"

class FileManager 
{
    public:
        // Saves tournament state
        static void saveTeams(const std::vector<Team>& teams, const std::string& path);
        static void saveMatches(const std::vector<Match>& matches, const std::string& path);

        // Loads tournament state
        static std::vector<Team> loadTeams(const std::string& path);
        static std::vector<Match> loadMatches(const std::string& path);
};

#endif
