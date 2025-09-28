#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <limits>

// Custom utilities
#include <utilities.h>

// Using standard namespace
using namespace std;

class Solution {
private:
    // Helper method, returns true if number does not contain a 0. False otherwise
    bool isNoZero(int n) {
        // Convert to string
        string s = to_string(n);
        // Check that there is no 0 character
        return s.find('0') == string::npos;
    }
public:
    vector<int> getNoZeroIntegers(int n) {

        // Initialize a and b
        int a, b;
        
        // Loop through all integers from 1 to n-1
        for(int i = 1; i < n; i++) {
            // If i contains a 0, skip
            if(!isNoZero(i)) {
                continue;
            }

            // Calculate a and b such that b is the complement of a, both summing to n
            a = i;
            b = n - i;

            // If b is a No-Zero Integer, return a and b
            if( isNoZero(b) ) {
                return {a, b};
            }
        }

        // Return {a, b} = {0, 0} if no solution is found
        return {a, b};
    }
};

int main() {
    printStartBanner("1317. Convert Integer to the Sum of Two No-Zero Integers", "O(n log n)", "O(log n)");

    // Initialize solution
    Solution s;

    // Get the mode to run in from user input
    string mode = selectMode();

    if(isCustomMode(mode)) { // If running in custom mode, run with user input
        customModeSelected();

        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        // Create holdeers for user input and valid n entries, loop until exit or quit
        string input;
        int n;
        while(true) {
            // Get user-entered n value, lowercase to check for exit or quit
            cout << "Enter a positive integer value for n or press enter to exit: ";
            getline(cin, input);
            toLowercase(input);
            
            if(input.empty() || isExitMode(input)) { // If input is empty or exit, break loop
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) { // If quit mode selected, exit program
                return quitModeSelected();
            }

            try { // Attempt to convert input to integer
                n = stoi(input);
            } catch(...) { // If conversion fails, error and continue
                cout << "ERROR: Invalid input. Please enter a positive integer." << endl;
                continue;
            }

            // Calculate result of getNoZeroIntegers(n)
            vector<int> value = s.getNoZeroIntegers(n);

            if(value != vector<int>{0, 0}) { // If result is not {0, 0}, it's a valid decomposition. Print
                cout << "Value " << n << " decomposes into integers " << value[0] << " and " << value[1] << endl;
            } else { // Else, no valid decomposition found. Print
                cout << "Value " << n << " can't be decomposed into two no-zero integers" << endl;
            }

        }
    } else if(isDemoMode(mode)) { // If running in demo mode, run with demo data
        // Initialize vector of n values to use
        vector<int> demoData = {5, 31, 100};
        // Initialize result vector for storing results
        vector<int> result;

        for(const auto& n : demoData) {
            cout << "Using n = " << n << endl;

            // Calculate result of getNoZeroIntegers(n)
            result = s.getNoZeroIntegers(n);

            if(result != vector<int>{0, 0}) { // If result is not {0, 0}, valid decomposition found. Print
                cout << "Value " << n << " decomposes into integers " << result[0] << " and " << result[1] << endl;
            } else { // Else, no valid decomposition found. Print
                cout << "Value " << n << " can't be decomposed into two no-zero integers" << endl;
            }
        }
    } else if(isQuitMode(mode)) { // If quit mode selected, exit program
        return quitModeSelected();
    } else { // Else, unknown mode. Error
        return unknownModeSelected(mode);
    }

    // Exit the program
    return 0;
}