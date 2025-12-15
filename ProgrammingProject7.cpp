#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>   // for exit()
using namespace std;

// Function prototypes
void getTeams(const string& filename, vector<string>& teams);
int findWinner(const string& teamName, const vector<string>& winners);
void displayTeams(const vector<string>& teams);

int main()
{
    // Vectors to store team names and winners
    vector<string> teams;
    vector<string> winners;

    // Read Teams.txt into teams vector
    getTeams("Teams.txt", teams);

    // Read WorldSeriesWinners.txt into winners vector
    getTeams("WorldSeriesWinners.txt", winners);

    // Display the list of team names
    cout << "World Series Teams (1903–2012):\n";
    cout << "--------------------------------\n";
    displayTeams(teams);
    cout << "--------------------------------\n\n";

    cout << "Enter a team name exactly as shown above.\n";
    cout << "Type \"quit\" to end the program.\n\n";

    string teamName;

    // Loop so user can repeatedly enter team names
    while (true)
    {
        cout << "Enter team name (or \"quit\" to exit): ";
        getline(cin, teamName);

        if (teamName == "quit")
        {
            cout << "Exiting program.\n";
            break;
        }

        // Count how many times this team appears in the winners list
        int numWins = findWinner(teamName, winners);

        if (numWins == 0)
        {
            cout << "\"" << teamName
                << "\" did not win the World Series from 1903 to 2012,\n"
                << "or the name was not entered exactly as listed.\n\n";
        }
        else
        {
            cout << teamName << " won the World Series "
                << numWins << " time";

            if (numWins > 1)
                cout << "s";
            cout << " between 1903 and 2012.\n\n";
        }
    }

    return 0;
}

// getTeams()
// Reads lines from the specified file and stores each line in the vector.
// Uses push_back() to add names to the end of the vector.
// If the file fails to open, prints an error and terminates.
void getTeams(const string& filename, vector<string>& teams)
{
    ifstream inFile(filename);

    if (!inFile)
    {
        cout << "Error: Could not open file \"" << filename << "\".\n";
        exit(1);
    }

    string line;
    while (getline(inFile, line))
    {
        if (!line.empty())
        {
            teams.push_back(line);  // add team name to the vector
        }
    }

    inFile.close();
}

// findWinner()
// Counts how many times teamName appears in the winners vector.
// Uses a range-based for loop as required.
int findWinner(const string& teamName, const vector<string>& winners)
{
    int count = 0;

    for (const string& winner : winners)
    {
        if (winner == teamName)
        {
            count++;
        }
    }

    return count;
}

// displayTeams()
// Displays each team name on its own line.
void displayTeams(const vector<string>& teams)
{
    for (const string& team : teams)
    {
        cout << team << '\n';
    }
}
