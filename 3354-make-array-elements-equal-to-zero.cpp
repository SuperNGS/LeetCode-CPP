#include <numeric>

// Include custom utilities header
#include <utilities.h>

// Use standard namespace
using namespace std;

class Solution {
public:
    int countValidSelections(vector<int>& nums) {
        // Initialize int result to 0
        int result = 0;

        // Set an iterator to the beginning of nums
        auto it = nums.begin();

        // Loop while there are more 0s in nums
        while ((it = find(it, nums.end(), 0)) != nums.end()) {
            // Calculate left and right sums and their absolute difference
            int left_sum = accumulate(nums.begin(), it, 0);
            int right_sum = accumulate(it, nums.end(), 0);
            int diff = abs(left_sum - right_sum);

            if(diff == 1) { // If difference is 1, increment result by 1 (one valid path)
                result++;
            } else if(diff == 0) { // If difference is 0, increment result by 2 (two valid paths)
                result += 2;
            }

            // Move iterator to the next element
            it++;
        }

        // Return result
        return result;
    }
};

int main() {
    printStartBanner("3354. Make Array Elements Equal to Zero", "O(n^2)", "O(1)");

    // Initialize the solution
    Solution s;

    // Get the mode to run program in from user
    string mode = selectMode();

    if(isCustomMode(mode)) { // If custom mode, run with user input
        customModeSelected();

        // Initialize input string and loop
        string input;
        while(true) {
            // Get nums input from user
            cout << "Enter nums as a comma-separated string of integers: ";
            getline(cin, input);
            toLowercase(input);

            // If exit or quit inputted, exit program
            if(isExitMode(input)) {
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) {
                return quitModeSelected();
            }

            // Parse nums input into nums vector
            vector<int> nums = stringToIntVector(input);

            // If no nums entered, skip
            if(nums.empty()) {
                cout << "INFO: No nums entered. Please try again. Skipping..." << endl;
                continue;
            }

            // Calculate and print count of valid selections
            int result = s.countValidSelections(nums);
            cout << "Count of valid selections: " << result << endl;
            cout << "----------------------------------------" << endl;
        }
    } else if(isDemoMode(mode)) { // If demo mode, run with demo data
        demoModeSelected();

        // Initialize 2D int vector demoNums
        vector<vector<int>> demoNums = {
            {1, 0, 2, 0, 3},
            {2, 3, 4, 0, 4, 1, 0}
        };

        // Loop over sets of demo data, print them, then calculate count of valid selections
        for(const auto& nums : demoNums) {
            // Print demo nums
            cout << "Running program with nums: [";
            for(int j = 0; j < nums.size(); j++) {
                cout << nums[j];
                if(j < nums.size() - 1) {
                    cout << ", ";
                }
            }
            cout << "]" << endl;

            // Calculate and print count of valid selections
            int result = s.countValidSelections(const_cast<vector<int>&>(nums));
            cout << "Count of valid selections: " << result << endl;
            cout << "----------------------------------------" << endl;
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // If exit or quit mode, exit program
        return quitModeSelected();
    } else { // Else, unknown mode, error
        return unknownModeSelected(mode);
    }

    // Exit program successfully
    return 0;
}