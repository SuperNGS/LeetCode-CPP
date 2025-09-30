#include <vector>
#include <iostream>
#include <string>
#include <sstream>

// Custom utilities header
#include <utilities.h>

// Use std namespace
using namespace std;
class Solution {
public:
    int triangularSum(vector<int>& nums) {
        // Loop until nums only contains one element
        while(nums.size() != 1) {
            // Initialize the newNums vector
            vector<int> newNums(nums.size() - 1);

            // Calculate the triangular sum for newNums[i]
            for(int i = 0; i < nums.size() - 1; i++) {
                newNums[i] = (nums[i] + nums[i+1]) % 10;
            }

            // Reassign nums to newNums before repeating loop
            nums = newNums;
        }

        // Return the single element in nums
        return nums[0];
    }
};

int main() {
    printStartBanner("2221. Find Triangular Sum of an Array", "O(n^2)", "O(n)");

    // Initialize solution
    Solution s;

    // Prompt user to select mode
    string mode = selectMode();

    if(isCustomMode(mode)) { // Custom mode selected, run with user input
        customModeSelected();

        // Initialize input string and begin looping
        string input;
        while(true) {
            cout << "Enter comma-separated values or press enter to exit: ";
            getline(cin, input);
            toLowercase(input);

            if(isExitMode(input)) { // If exit mode selected, break loop
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) { // If quit mode selected, exit program
                return quitModeSelected();
            }

            // Attempt to tokenize input into int vector
            vector<int> values;
            stringstream ss(input);
            string token;
            while(getline(ss, token, ',')) {
                try { // Try to convert token to an int and push back on values
                    values.push_back(stoi(token));
                } catch(...) { // Token can't be converted to an int, print error and loop
                    cout << "ERROR: Invalid input '" << token << "'. Please only enter integers. Skipping..." << endl;
                    continue;
                }
            }

            // If no values entered, skip and repeat loop
            if(values.size() == 0) {
                cout << "ERROR: No values entered. Please enter at least one int value. Skipping..." << endl;
                continue;
            }

            // Print out the values being used to run triangularSum()
            cout << "Running triangularSum() with values: ";
            for(const auto& value : values) {
                cout << value << " ";
            }
            cout << endl;

            // Calculate and print out triangular sum of the array
            cout << "Triangular sum of array: " << s.triangularSum(values) << endl;
        }
    } else if(isDemoMode(mode)) { // Demo mode selected, run with demo data
        demoModeSelected();

        // Initialize 2D vector of demo data
        vector<vector<int>> demoData = {
            {1,2,3,4,5},
            {5},
            {2,2,2,2,2,2},
            {3,7,4,2,4},
            {1,9,8,5,6,4,3}
        };

        // Loop through each demo data set
        for(vector<int> data : demoData) {
            // Print out the demo data
            cout << "Input vector: ";
            for(const auto& value : data) {
                cout << value << " ";
            }
            cout << endl;

            // Calculate and print out the triangular sum of the data
            cout << "Triangular Sum: " << s.triangularSum(data) << endl << endl;
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // Exit or quit mode selected, exit program
        return quitModeSelected();
    } else { // Else, unknown mode selected, error
        return unknownModeSelected(mode);
    }

    // Exit program successfully
    return 0;
}