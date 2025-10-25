// Include custom utilities header
#include <utilities.h>

// Use standard namespace
using namespace std;

class Solution {
public:
    int totalMoney(int n) {
        // Initialize day (current day starting at monday = 0), current (current money being added), and total (total money added)
        int day = 0, current = 1, total = 0;

        // While we haven't reached the final day, loop
        while(day != n) {
            if(day % 7 == 0) { // If day is a monday, set current to 1 + (day / 7)
                current = 1 + (day / 7);
            } else { // Else, increment current by 1
                current++;
            }

            // Increment total by current and increment day by 1
            total += current;
            day++;
        }

        // Return the total
        return total;
    }
};

int main() {
    printStartBanner("1716. Calculate Money in Leetcode Bank", "O(n)", "O(1)");

    // Initialize the solution
    Solution s;

    // Get input mode from user
    string mode = selectMode();

    if(isCustomMode(mode)) { // If custom mode, run with user input
        customModeSelected();

        // Initialize input string and loop
        string input;
        while(true) {
            cout << "Enter an integer value to act as n: ";
            getline(cin, input);
            toLowercase(input);

            // If exit or quit entered, exit program
            if(isExitMode(input) || isQuitMode(input)) {
                return quitModeSelected();
            }

            // Attempt to convert input to int n, error and skip if impossible
            int n;
            try {
                n = stoi(input);
            } catch(...) {
                cout << "ERROR: Invalid input '" << input << "'. Please only enter an integer. Skipping..." << endl;
                continue;
            }

            // Print the result
            cout << "Total money after " << n << " days is " << s.totalMoney(n) << endl;
        }
    } else if(isDemoMode(mode)) { // If demo mode, run with demo data
        demoModeSelected();

        // Initialize int vector demoNValues to act as sets of n
        vector<int> demoNValues = {4,10,20};

        // Loop through n values, print them, then calculate and print result of totalMoney()
        for(const auto& n : demoNValues) {
            cout << "Running program with n value: " << n << endl;
            cout << "Total money in bank after " << n << " days is " << s.totalMoney(n) << endl;
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // If exit or quit mode, exit program
        return quitModeSelected();
    } else { // Else, unknown mode, error
        return unknownModeSelected(mode);
    }

    // Exit program successfully
    return 0;
}