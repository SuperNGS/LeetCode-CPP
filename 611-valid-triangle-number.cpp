#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>

// Custom utilities header
#include <utilities.h>

// Use std namespace
using namespace std;

class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        // Sort the nums vector
        sort(nums.begin(), nums.end());

        // Initialize count to 0
        int count = 0;

        // Loop over all possible k values
        for(int k = nums.size() - 1; k >= 2; k--) {

            // Calculate the left and right bounds to search
            int left = 0;
            int right = k - 1;

            // Loop while left is less than right
            while(left < right) {
                if(nums[left] + nums[right] > nums[k]) { // if left + right > mid, triangle found
                    count += right - left; // Increment count by right - left, all values satisfying the condition
                    right--; // Decrement the right pointer
                } else { // Else, triangle not found
                    left++; // Increment left pointer
                }
            }
        }

        // Return count
        return count;
    }
};

int main() {
    printStartBanner("611. Valid Triangle Number", "O(n^2)", "O(1)");

    // Initialize solution
    Solution s;

    // Get the mode to run program in from user
    string mode = selectMode();

    if(isCustomMode(mode)) { // If custom mode, run with user input
        customModeSelected();

        // Initialize holder for user input and start looping
        string input;
        
        while(true) {
            // Get the comma-separated string of values from user
            cout << "Enter values as a comma-separated string or enter to exit: ";
            getline(cin, input);
            toLowercase(input);

            // If exit entered, exit the loop
            if(isExitMode(input) || input.empty()) {
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) { // If quit entered, exit program
                return quitModeSelected();
            }

            // Tokenize the inputted string and print
            vector<int> tokens;
            stringstream ss(input);
            string token;
            cout << "Running with values: ";
            while(getline(ss, token, ',')) {
                cout << token << " ";
                try { // Try to convert token to int and add to tokens vector
                    tokens.push_back(stoi(token));
                } catch(...) { // If conversion fails, error and break
                    cout << "\nError: Invalid input '" << token << "', please enter only integers" << endl;
                }
            }
            cout << endl;

            // Calculate the valid triangle number and print
            cout << "The total number of valid triangles in the set is " << s.triangleNumber(tokens) << endl;
        }
    } else if(isDemoMode(mode)) { // If demo mode, run with demo data
        demoModeSelected();

        // Initialize 2D vector of demo data
        vector<vector<int>> demoData =  {
                                            {2, 2, 3, 4},
                                            {4, 2, 3, 4},
                                            {1, 2, 3, 4, 5, 6, 7, 8, 9}
                                        };
        
        // Loop through all sets of demo data
        for(vector<int> data : demoData) {
            // Print the set of demo values
            cout << "Running with numbers: ";
            for(const auto& value : data) {
                cout << value << " ";
            }
            cout << endl;

            // Calculate and print the valid triangle number
            cout << "The total number of valid triangles in the set is " << s.triangleNumber(data) << endl;
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // If quit or exit mode, exit program
        return quitModeSelected();
    } else { // Else, invalid mode. Error
        return unknownModeSelected(mode);
    }
    // Exit the program
    return 0;
}