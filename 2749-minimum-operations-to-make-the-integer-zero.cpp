// Custom utilities header
#include <utilities.h>
#include <vector>

// Use std namespace
using namespace std;

class Solution {
private:
    // Calculate the maximum number of operations to get num1 to 0
    long long calcMax(int& num1, int& num2, int& k) {
        return (1LL * num1) - (1LL * k * num2);
    }

    // Calculate if K is a valid K value
    bool isKValue(int& num1, int& num2, int& k) {
        long long max = calcMax(num1, num2, k);
        return (__builtin_popcountll(max) <= k) && (1LL * k <= max);
    }
public:
    int makeTheIntegerZero(int num1, int num2) {
        // Loop through posible K values, from 1 to 100
        for(int k = 1; k <= 100; k++) {
            // If K operations can set the target to 0, return it
            if(isKValue(num1, num2, k)) {
                return k;
            }
        }
        // If no number of operations can set target to 0, return false
        return -1;
    }
};

int main() {
    printStartBanner("2749. Minimum Operations to Make the Integer Zero", "O(1)", "O(1)");

    // Initialize the solution
    Solution s;

    // Get mode to run program in from user
    string mode = selectMode();

    if(isCustomMode(mode)) { //Custom mode selected, run with user input
        customModeSelected();

        // Initialize input string and loop
        string input;
        while(true) {
            cout << "Enter first value: ";
            getline(cin, input);
            toLowercase(input);

            if(isExitMode(input)) { // If exit selected, break loop
                exitModeSelected();
                break;
            } else if(isQuitMode) { // Quit mode selected, exit program
                return quitModeSelected();
            }

            int val1;
            try {
                val1 = stoi(input);
            } catch(...) {
                cout << "ERROR: invalid input '" << input << "'. Please only enter integers. Skipping..." << endl;
                continue;
            }

            cout << "Enter second value: ";
            getline(cin, input);
            toLowercase(input);

            if(isExitMode(input)) { // If exit selected, break loop
                exitModeSelected();
                break;
            } else if(isQuitMode) { // Quit mode selected, exit program
                return quitModeSelected();
            }

            int val2;
            try {
                val2 = stoi(input);
            } catch(...) {
                cout << "ERROR: invalid input '" << input << "'. Please only enter integers. Skipping..." << endl;
                continue;
            }

            cout << "The minimum operations to make " << val1 << " zero is " << s.makeTheIntegerZero(val1, val2) << endl;

        }
    } else if(isDemoMode(mode)) { // Demo mode selected, run with demo data
        demoModeSelected();

        // Initialize vector of pairs to use as test cases
        vector<pair<int, int>> demoData = {
            {3, -2},
            {5, 7}
        };

        // Loop through each pair of demo data, print out the pair, then calculate and print out the result
        for(const auto& data : demoData) {
            cout << "Running with values " << data.first << " and " << data.second << endl;
            cout << "Minimum operations to make " << data.first << " zero is " << s.makeTheIntegerZero(data.first, data.second) << endl;
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // Quit or exit selected, exit program
        return quitModeSelected();
    } else { // Unknown mode selected, error
        return unknownModeSelected(mode);
    }

    // Exit program successfully
    return 0;
}