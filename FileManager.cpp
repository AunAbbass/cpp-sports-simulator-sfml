#include "FileManager.hpp"
#include <fstream>
#include <iostream>

using namespace std;

void FileManager :: saveTeams(const vector<Team>& teams, const string& filename)
{
    ofstream file(filename);
    if (!file.is_open()) return;

    for (const Team& team : teams)
    {
        file << team.getName() << "\n";

        vector<Player> players = team.getPlayers();
        for (const Player& p : players)
        {
            file << p.getName() << "\n";
        }

        file << "---\n";
    }

    file.close();
}

void FileManager :: saveMatches(const vector<Match>& matches, const string& filename)
{
    ofstream file(filename);
    if (!file.is_open()) return;

    for (const Match& m : matches)
    {
        file << m.getTeamA()->getName()
             << " vs "
             << m.getTeamB()->getName()
             << "\n";
    }

    file.close();
}

vector<Team> FileManager::loadTeams(const string& filename)
{
    vector<Team> teams;
    ifstream file(filename);

    if (!file.is_open()) return teams;

    string line;
    string teamName;
    vector<Player> players;

    while (getline(file, line))
    {
        if (line == "---")
        {
            if (!teamName.empty())
            {
                Team t(teamName);
                t.addPlayers(players);
                teams.push_back(t);
            }

            teamName = "";
            players.clear();
        }
        else if (teamName.empty())
        {
            // First line = team name
            teamName = line;
        }
        else
        {
            // All following lines = players
            players.push_back(Player(line));
        }
    }

    file.close();
    return teams;
}


