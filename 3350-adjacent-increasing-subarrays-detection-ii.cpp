// Custom utilities header
#include <utilities.h>

// Use standard namespace
using namespace std;

class Solution {
public:
    int maxIncreasingSubarrays(vector<int>& nums) {
        // Get n, the number of elements in num
        int n = nums.size();
        // Track max K value found, previous streak, and current streak
        int maxK = 0, prev = 0, curr = 1;

        // Loop over all nums, track previous and current streak
        for (int i = 1; i < n; i++) {
            if (nums[i] > nums[i - 1]) { // If nums[i] greater than nums[i - 1], streak is strictly increasing
                curr++;
            } else { // Else, streak is over, check for max and assign curr to previous + reset curr
                maxK = max({maxK, curr / 2, min(prev, curr)});
                prev = curr;
                curr = 1;
            }
        }

        // Check the ending streak for max k
        maxK = max({maxK, curr / 2, min(prev, curr)});

        // Return the max k value found found      
        return maxK;
    }
};

int main() {
    printStartBanner("3550. Adjacent Increasing Subarrays Detection II", "O(N)", "O(1)");

    // Initialize the solution
    Solution s;

    // Get mode from user
    string mode = selectMode();

    if(isCustomMode(mode)) { // If custom mode, run with user input
        customModeSelected();

         // Initialize input string and loop
        string input;
        while(true) {
            cout << "Enter values as a comma-separated string: ";
            getline(cin, input);
            toLowercase(input);

            if(isExitMode(input)) { // If exit mode, break loop
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) { // Quit mode selected, exit program
                return quitModeSelected();
            }

            // Attempt to tokenize the input into int vector nums
            vector<int> nums = stringToIntVector(input);

            // If no nums entered, skip
            if(nums.empty()) {
                cout << "INFO: No values entered. Skipping..." << endl;
                continue;
            }

            // Loop over and print values to run program with
            cout << "Running program with values: ";
            for(const auto& num : nums) {
                cout << num << " ";
            }
            cout << endl;

            // Calculate max K value and print
            cout << "Max K value is " << s.maxIncreasingSubarrays(nums) << endl;
        }
    } else if(isDemoMode(mode)) { // If demo mode, run with demo data
        demoModeSelected();

        // Initialize 2D int vector of demo data
        vector<vector<int>> demoData = {
            {2,5,7,8,9,2,3,4,3,1},
            {1,2,3,4,4,4,4,5,6,7}
        };

        // Loop through the sets of demo data, print them, then calculate the max k value and print
        for(vector<int> data : demoData) {
            // Print the data
            cout << "Running program with vector: ";
            for(const auto& val : data) {
                cout << val << " ";
            }
            cout << endl;

            // Calculate and print the max K value
            cout << "Max K value is " << s.maxIncreasingSubarrays(data) << endl;

        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // If exit or quit mode, exit program
        return quitModeSelected();
    } else { // Else, unknown mode, error
        return unknownModeSelected(mode);
    }

    // Exit program successfully
    return 0;
}