// Include custom utilities header
#include <utilities.h>

// Use standard namespace
using namespace std;

class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        // Initialize int total, number of operations to make initial match target, to 0
        int total = 0;

        // Loop through all indexes of target, starting at index 1
        for(int i = 1; i < target.size(); i++) {
            // If value is decreasing (sloping down), add the difference between index i and index i - 1 of target to total
            if(target[i] < target[i-1]) {
                total += target[i - 1] - target[i];
            }

            // If at the end of the array, add index i of target to total (slope goes from target[i] to 0)
            if(i == target.size() - 1) {
                total += target[i];
            }
        }

        // Return the total
        return total;
    }
};

int main() {
    printStartBanner("1526. Minimum Number of Increments on Subarrays to Form a Target Array", "O(n)", "O(1)");

    // Initialize the solution
    Solution s;

    // Get the mode to run program in from user
    string mode = selectMode();

    if(isCustomMode(mode)) { // If custom mode, run with user input
        customModeSelected();

        // Initialize input string and loop
        string input;
        while(true) {
            // Get target input from user
            cout << "Enter target as a comma-separated string of integers (e.g. 1,2,3): ";
            getline(cin, input);
            toLowercase(input);

            // If exit or quit inputted, exit program
            if(isExitMode(input) || isQuitMode(input)) {
                return quitModeSelected();
            }

            // Attempt to convert input string to vector of integers target, error and skip if impossible
            vector<int> target;
            try {
                target = stringToIntVector(input);
            } catch(...) {
                cout << "ERROR: Invalid input '" << input << "'. Please enter a list of integers. Skipping..." << endl;
                continue;
            }

            // Get result from solution and print to user
            int result = s.minNumberOperations(target);
            cout << "Minimum number of increments on subarrays to form target is: " << result << endl;
        } 
    } else if(isDemoMode(mode)) { // If demo mode, run with demo data
        demoModeSelected();

        // Initialize demo data
        vector<vector<int>> demoData = {
            {1,2,3,2,1},
            {3,1,1,2},
            {1,1,1,1},
            {4,2,3,4,1},
            {1,3,2,1,2}
        };

        // Loop through demo data
        for(const vector<int>& target : demoData) {
            // Get result from solution and print to user
            int result = s.minNumberOperations(const_cast<vector<int>&>(target));
            cout << "Minimum number of increments on subarrays to form target [";
            for(int i = 0; i < target.size(); i++) {
                cout << target[i];
                if(i < target.size() - 1) {
                    cout << ", ";
                }
            }
            cout << "] is: " << result << endl;
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // If exit or quit mode, exit program
        return quitModeSelected();
    } else { // Else, unknown mode, error
        return unknownModeSelected(mode);
    }

    // Exit program successfully
    return 0;
}