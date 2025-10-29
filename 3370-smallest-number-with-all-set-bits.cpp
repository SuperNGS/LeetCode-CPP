#include <cmath>

// Include custom utilities header
#include <utilities.h>

// Use standard namespace
using namespace std;

class Solution {
public:
    int smallestNumber(int n) {
        // Initialize current to 0
        int current = 0;

        // While 2 raised to current is less than or equal to n, loop and increment current
        while(pow(2, current) <= n) {
            current++;
        }

        // Return result, the smallest number with all set bits (2 raised to current minus 1)
        return pow(2, current) - 1;
    }
};

int main() {
    printStartBanner("3370. Smallest Number with All Set Bits", "O(log n)", "O(1)");

    // Initialize the solution
    Solution s;

    // Get the mode to run program in from user
    string mode = selectMode();

    if(isCustomMode(mode)) { // If custom mode, run with user input
        customModeSelected();

        // Initialize input string and loop
        string input;
        while(true) {
            // Get n input from user
            cout << "Enter n as an integer: ";
            getline(cin, input);
            toLowercase(input);

            // If exit or quit inputted, exit program
            if(isExitMode(input) || isQuitMode(input)) {
                return quitModeSelected();
            }

            // Attempt to convert input string to integer n, error and skip if impossible
            int n;
            try {
                n = stoi(input);
            } catch(...) {
                cout << "ERROR: Invalid input '" << input << "'. Please enter an integer. Skipping..." << endl;
                continue;
            }

            // Get result from solution and print to user
            int result = s.smallestNumber(n);
            cout << "Smallest number with all set bits for n = " << n << " is: " << result << endl;
        }
    } else if(isDemoMode(mode)) { // If demo mode, run with preset test cases
        demoModeSelected();

        // Initialize test cases
        vector<int> test_cases = {2, 3, 5, 10, 20};

        // Loop through test cases
        for(int n : test_cases) {
            // Get result from solution and print to user
            int result = s.smallestNumber(n);
            cout << "Smallest number with all set bits for n = " << n << " is: " << result << endl;
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // If exit or quit mode, exit program
        return quitModeSelected();
    } else { // Else, unknown mode, error
        return unknownModeSelected(mode);
    }

    // Exit program successfully
    return 0;
}