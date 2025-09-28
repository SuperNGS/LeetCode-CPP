#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>

// Custom utilities header
#include <utilities.h>

// Use std namespace
using namespace std;

class Solution {
public:
    std::vector<int> sumZero(int n) {
        // Initialize an empty vector to store the results
        std::vector<int> values;

        // If n is odd, add 0 to the vector and decrement n
        if( n % 2 != 0) {
            values.push_back(0);
            n--;
        }

        // Calculate how many pairs of values are needed in the vector
        int pairs = n / 2;

        // For each pair, push a pair of values that sum to 0
        for(int i = 1; i <= pairs; i++) {
            values.push_back(i);
            values.push_back(-i);
        }

        // Return the vector
        return values;
    }
};

int main() {
    printStartBanner("1304. Find N Unique Integers Sum up to Zero", "O(n)", "O(n)");

    // Initialize the solution
    Solution s;

    // Get the mode to run in from user
    string mode = selectMode();

    if(isCustomMode(mode)) { // If custom mode selected, run solution with user input
        customModeSelected();

        // Create holder for input
        string input;

        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        // Loop until user breaks loop
        while(true) {
            // Get n value from user input
            cout << "Select n value or press enter to exit: ";
            getline(cin, input);
            toLowercase(input);

            if(input.empty() || isExitMode(input)) { // If input is exit, break loop
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) {  // If input is quit, exit program
                return quitModeSelected();
            }

            // Calculate the N unique integers summing up to zero, store in vector
            vector<int> values = s.sumZero(stoi(input));

            // Loop over vector and print
            cout << "The " << input << " values summing to 0 are: ";
            for(const auto& value : values) {
                cout << value << " ";
            }
            cout << endl;

        }
    } else if(isDemoMode(mode)) { // if demo mode selected, run solution with demo data
        demoModeSelected();

        // Create a vector<int> of demo n values to use
        vector<int> nValues = {3, 5, 10, 15};

        // Loop over each n value in demo data and compute
        for(const auto& n : nValues) {
            vector<int> values = s.sumZero(n);

            cout << "The " << n << " values summing to 0 are: ";
            for(const auto& value : values) {
                cout << value << " ";
            }
            cout << endl;
        }
    } else if(isQuitMode(mode)) { // If quit mode selected, exit program
        return quitModeSelected();
    } else { // Else unknown mode selected, error
        return unknownModeSelected(mode);
    }

    // Exit the program
    return 0;
}