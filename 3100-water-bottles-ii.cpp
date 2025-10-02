#include <vector>

// Use custom utilities header
#include <utilities.h>

// Use std namespace
using namespace std;

class Solution {
public:
    int maxBottlesDrunk(int numBottles, int numExchange) {
        // Set trackers for full, empty, and drunk bottles
        int full = numBottles;
        int empty = 0;
        int drunk = 0;

        // Keep looping while full bottles remain
        while (full > 0) {
            // Drink all full bottles
            drunk += full;
            empty += full;
            full = 0;

            // If we have enough empty bottles to exchange for a new one
            if (empty >= numExchange) {
                empty -= numExchange;
                full += 1;         // Get a new full bottle
                numExchange += 1;  // Cost increases
            }
        }

        // Answer is the number of bottles drunk
        return drunk;
    }
};

int main() {
    printStartBanner("3100. Water Bottles II", "O(numBottles)", "O(1)");

    // Initialize the solution
    Solution s;

    // Prompt user for mode
    string mode = selectMode();

    if(isCustomMode(mode)) { // Custom mode selected, run with user input
        customModeSelected();

        // Initialize input string and start loop
        string input;
        while(true) {
            cout << "Enter value for numBottles: ";
            getline(cin, input);
            toLowercase(input);

            if(isExitMode(input)) { // Exit mode selected, break loop
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) { // Quit mode selected, exit program
                return quitModeSelected();
            }

            int numBottles;
            try {
                numBottles = stoi(input);
            } catch(...) {
                cout << "ERROR: Invalid input '" << input << "'. Please enter an integer. Skipping..." << endl;
                continue;
            }

            cout << "Enter value for numExchange: ";
            getline(cin, input);
            toLowercase(input);

            if(isExitMode(input)) { // Exit mode selected, break loop
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) { // Quit mode selected, exit program
                return quitModeSelected();
            }

            int numExchange;
            try {
                numExchange = stoi(input);
            } catch(...) {
                cout << "ERROR: Invalid input '" << input << "'. Please enter an integer. Skipping..." << endl;
                continue;
            }

            // Calculate and print maxBottlesDrunk()
            cout << "The max number of bottles drunk is " << s.maxBottlesDrunk(numBottles, numExchange) << endl;
        }
    } else if(isDemoMode(mode)) { // Demo mode selected, run with demo data
        demoModeSelected();

        // Initialize vector of pairs (numBottles, numExchange) for demo data
        vector<pair<int, int>> demoData = {
            {13, 6},
            {10, 3}
        };

        // Loop through each pair of demo data, print, then calculate maxBottlesDrunk() and print
        for(const auto& data : demoData) {
            cout << "Running with: numBottles = " << data.first << ", numExchange = " << data.second << endl;
            cout << "The max number of bottles drunk is " << s.maxBottlesDrunk(data.first, data.second);
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // Quit or exit mode selected, exit program
        return quitModeSelected();
    } else { // Unknown mode selected, error
        return unknownModeSelected(mode);
    }

    // Exit successfully
    return 0;
}