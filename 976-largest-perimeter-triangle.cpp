#include <vector>
#include <algorithm>
#include <limits>
#include <sstream>

// Include custom utilities header
#include <utilities.h>

// Use std namespace
using namespace std;
class Solution {
public:
    int largestPerimeter(vector<int>& nums) {
        // Initialize variable to hold highest perimeter found
        int highestPerimeter = 0;

        // Sort the input vector
        sort(nums.begin(), nums.end());

        // Loop over the vector from largest to smallest value, checking if the current value and the two previous values can form a triangle
        for(int i = nums.size() - 1; i > 1; i--) {
            // If they can form a triangle and the perimeter is larger than the current highest perimeter, update the highest perimeter
            if(nums[i-1] + nums[i-2] > nums[i] && (nums[i] + nums[i-1] + nums[i-2]) > highestPerimeter) {
                highestPerimeter = nums[i] + nums[i-1] + nums[i-2];
            }
        }

        // Return the highest perimeter found, or 0 if no triangle could be formed
        return highestPerimeter;
    }
};

int main() {
    printStartBanner("976. Largest Perimeter Triangle", "O(n log n)", "O(1)");

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
            cout << "Enter comma-seperated list of values or press enter to exit: ";
            getline(cin, input);

            if(input.empty() || isExitMode(input)) { // If no input entered or exit mode selected, break loop
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) { // If quit mode selected, exit program
                return quitModeSelected();
            }

            // Convert input string to vector of integers
            vector<int> nums;
            stringstream ss(input);
            string token;
            while(getline(ss, token, ',')) {
                try {
                    nums.push_back(stoi(token));
                } catch(...) {
                    cout << "Invalid input: " << token << ". Please enter only integers. Skipping..." << endl;
                }
            }

            if(nums.size() < 3) { // If less than 3 values entered, print error and continue loop
                cout << "ERROR: At least 3 values are required to form a triangle. Please try again." << endl;
                continue;
            }

            // Print the result of the solution
            cout << "Result: " << s.largestPerimeter(nums) << endl;
        }
    } else if(isDemoMode(mode)) { // If demo mode selected, run solution with leetcode test cases
        demoModeSelected();

        // Create holder for test cases
        vector<vector<int>> testCases = {
            {2,1,2},
            {1,2,1},
            {3,2,3,4},
            {3,6,2,3},
            {1,2,3,4,5,6}
        };

        // Loop over each test case
        for(int i = 0; i < testCases.size(); i++) {
            // Print the result of the solution
            cout << "Test Case " << i + 1 << ": " << s.largestPerimeter(testCases[i]) << endl;
        }
    } else if(isQuitMode(mode)){ // If quit mode selected, exit program
        return quitModeSelected();
    } else { // Else, unknown mode selected. Error
        return unknownModeSelected(mode);
    }

    // Return success
    return 0;
}