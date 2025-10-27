// Include custom utilities header
#include <utilities.h>

// Use Standard namespace
using namespace std;

class Solution {
public:
    int numberOfBeams(vector<string>& bank) {
        // Track running total of beams as well as previous row security devices
        int total = 0, previous = 0;

        // Loop through all rows of bank
        for(const auto& row : bank) {
            // Get the count of security devices on row
            int current = count(row.begin(), row.end(), '1');

            // If there are security devices on row, calculate number of beams and add to total
            if(current > 0) {
                total += previous * current;
                previous = current;
            }
        }

        // Return total
        return total;
    }
};

int main() {
    printStartBanner("2125. Number of Laser Beams in a Bank", "O(m * n)", "O(1)");

    // Initialize solution
    Solution s;

    // Get input mode from user
    string mode = selectMode();

    if(isCustomMode(mode)) { // If custom mode, run with user input
        customModeSelected();

        // Initialize input string, grid vector, and loop
        string input;

        vector<string> grid;
        while(true) {
            // Get next row from user
            cout << "Enter next row of bank as a numeric string (0s or 1s) or press enter to exit: ";
            getline(cin, input);
            toLowercase(input);

            if(isExitMode(input)) { // If exit inputted, break loop
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) { // If quit inputted, exit program
                return quitModeSelected();
            } else { // Else, attempt to add row to grid. Error and skip if invalid entry
                int zero_count = count(input.begin(), input.end(), '0');
                int one_count = count(input.begin(), input.end(), '1');

                if(zero_count + one_count != input.length()) {
                    cout << "ERROR: Invalid input '" << input << "'. Please only enter a string containing 1s and 0s. Skipping..." << endl;
                    continue;
                } else if(!grid.empty() && input.length() != grid[0].length()) {
                    cout << "ERROR: Invalid input '" << input << "'. All rows must be the same length as the first row (" << grid[0].length() << "). Skipping..." << endl;
                    continue;
                } else {
                    grid.push_back(input);
                }
                
            }
        }

        // If no rows were added, exit program
        if(grid.empty()) {
            cout << "INFO: No rows were added. Exiting..." << endl;
            return quitModeSelected();
        }

        // Print the grid
        cout << "Bank layout:" << endl;
        for(const auto& row : grid) {
            cout << "\t" << row << endl;
        }

        // Calculate and print number of beams
        cout << "Number of beams: " << s.numberOfBeams(grid) << endl;
    } else if(isDemoMode(mode)) { // If demo mode, run with demo data
        demoModeSelected();

        // Create a 2D string vector demoData
        vector<vector<string>> demoData = {
            {"011001","000000","010100","001000"},
            {"000","111","000"},
            {"101","010","101"}
        };

        // Loop over each demo data set, print it, then calculate and print number of beams
        for(const auto& data : demoData) {
            // Print the bank layout
            cout << "Bank layout:" << endl;
            for(const auto& row : data) {
                cout << "\t" << row << endl;
            }

            // Calculate and print number of beams
            int result = s.numberOfBeams(const_cast<vector<string>&>(data));
            cout << "Number of laser beams: " << result << endl << endl;
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // If exit or quit mode, exit program
        return quitModeSelected();
    } else { // Else, invalid mode, error
        return unknownModeSelected(mode);
    }

    // Exit program successfully
    return 0;
}