#include <vector>

// Custom utilities header
#include <utilities.h>

using namespace std;

class Solution {
public:
    int numWaterBottles(int numBottles, int numExchange) {
        // If too few bottles to exchange, numBottles is the answer
        if(numBottles < numExchange) return numBottles;

        // Calculate the net cost of exchanging numExchange bottles for a new bottle
        int numNewBottles = (numBottles - 1) / (numExchange - 1);

        // Return the original number of bottles + the number of new bottles gained
        return numBottles + numNewBottles;
    }
};

int main() {
    printStartBanner("1518. Water Bottles", "O(1)", "O(1)");

    // Initialize solution
    Solution s;

    // Get mode to run demo in from user
    string mode = selectMode();

    if(isCustomMode(mode)) { // Custom mode selected, run with user input
        customModeSelected();
        
        string input;
        while(true) {
            // Get number of full bottles from user input
            cout << "Select number of full bottles: ";
            getline(cin, input);
            toLowercase(input);
            int numBottles;

            if(isExitMode(input)) { // If exit mode selected, break
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) { // If quit mode selected, exit program
                return quitModeSelected();
            }

            try{
                numBottles = stoi(input);
            } catch(...) {
                cout << "ERROR: Invalid input '" << input << "'. Number of full bottles must be an integer. Skipping..." << endl;
                continue;
            }

            // Get number of exchange bottles from user input
            cout << "Select number of exchange bottles: ";
            getline(cin, input);
            toLowercase(input);
            int numExchange;

            if(isExitMode(input)) { // If exit mode selected, break
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) { // If quit mode selected, exit program
                return quitModeSelected();
            }

            try { // Attempt to convert input to an int and store in numExchange
                numExchange = stoi(input);
            } catch(...) { // Catch invalid entry
                cout << "ERROR: Invalid input '" << input << "'.Number of bottles to exchange must be an integer. Skipping..." << endl;
                continue;
            }

            // Calculate numWaterBottles() and print result
            cout << "Max number of water bottles to drink is " << s.numWaterBottles(numBottles, numExchange) << endl;

        }
    } else if(isDemoMode(mode)) { // Demo mode selected, run with demo data
        demoModeSelected();

        // Initialize 2D vector of demo data
        vector<vector<int>> demoData = {
            {9, 3},
            {15, 4}
        };

        // Loop through each set of data, print it, then calculate result and print
        for(const auto& data : demoData) {
            cout << "Running with values: numBottles = " << data[0] << ", numExchange = " << data[1] << endl;
            cout << "Maximum number of water bottles to drink is " << s.numWaterBottles(data[0], data[1]) << endl;
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { //Quit or exit mode selected, exit program
        return quitModeSelected();
    } else { //Else, unknown mode selected, error
        return unknownModeSelected(mode);
    }

    // Exit program successfully
    return 0;
}