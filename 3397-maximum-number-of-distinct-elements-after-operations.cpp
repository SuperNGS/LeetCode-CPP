// Include custom utilities header
#include <utilities.h>

// Use standard namespace
using namespace std;

class Solution {
public:
    int maxDistinctElements(vector<int>& nums, int k) {
        // Initialize int val to be lowest possible adjustment, get size of nums n
        int val = -k, n = nums.size();
        // Sort the nums
        sort(nums.begin(), nums.end());
        // Set tracker to find distinct values
        int distinct = 1;

        // Loop through all nums, starting at nums[1]
        for(int i = 1; i < n; i++) {
            // Increment val
            val++;
            // Get the difference between nums[i] and nums[i-1]
            int diff = nums[i] - nums[i - 1];
            // Val equals the max between negative k and val - diff
            val = max(val - diff, -k);
            
            if(val > k) { // If val greater than k, set to k
                val = k;
            } else { // Else, increment distinct
                distinct++;
            }
        }

        // Return distinct
        return distinct;
    }
};

int main() {
    printStartBanner("3397. Maximum Number of Distinct Elements After Operations", "O(Nlogn)", "O(1)");

    // Initialize solution
    Solution s;

    // Get mode to run program in from user
    string mode = selectMode();

    if(isCustomMode(mode)) { // Custom mode selected, run with user input
        customModeSelected();

        // Initialize input string and loop
        string input;
        while(true) {
            // Get the nums vector from the user
            cout << "Enter nums vector as a comma-separated string: ";
            getline(cin, input);
            toLowercase(input);

            // If exit or quit mode, exit program
            if(isExitMode(input) || isQuitMode(input)) {
                return quitModeSelected();
            }

            // Tokenize input into nums vector
            vector<int> nums = stringToIntVector(input);

            // If nums empty, skip
            if(nums.empty()) {
                cout << "INFO: No nums entered. Skipping..." << endl;
                continue;
            }

            // Get k value from the user
            cout << "Enter k value as an int: ";
            getline(cin, input);
            toLowercase(input);

            // If exit or quit mode, exit program
            if(isExitMode(input) || isQuitMode(input)) {
                return quitModeSelected();
            }

            // Attempt to convert input to int k, skip if unconvertable
            int k;
            try {
                k = stoi(input);
            } catch(...) {
                cout << "ERROR: Invalid input '" << input << "'. Please only enter an integer. Skipping..." << endl;
                continue;
            }

            // Print the nums
            cout << "Running program with nums: ";
            for(const auto& num : nums) {
                cout << num << " ";
            }
            cout << endl;

            // Print the k value
            cout << "Running program with k value: " << k << endl;

            // Calculate and print the max number of distinct elements after operations
            cout << "Max number of distinct elements after operations: " << s.maxDistinctElements(nums, k) << endl;
        }
    } else if(isDemoMode(mode)) { // Demo mode selected, run with demo data
        demoModeSelected();

        // Initialize 2D int vector of demoNums
        vector<vector<int>> demoNums = {
            {1,2,2,3,3,4},
            {4,4,4,4}
        };
        // Initialize int vector of demoKValues
        vector<int> demoKValues = {2,1};

        // Loop over sets of demo data, print, then calculate max distinct elements and print
        for(int i = 0; i < demoNums.size(); i++) {
            // Print nums
            cout << "Running program with nums: ";
            for(const auto& num : demoNums[i]) {
                cout << num << " ";
            }
            cout << endl;

            // Print k value
            cout << "Running program with k value: " << demoKValues[i] << endl;

            // Calcualte and print max number of distinct elements
            cout << "Max number of distinct elements after operations: " << s.maxDistinctElements(demoNums[i], demoKValues[i]) << endl;
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // Exit or quit mode selected, exit proram
        return quitModeSelected();
    } else { // Else, unknown mode selected, error and quit
        return unknownModeSelected(mode);
    }

    // Exit program successfully
    return 0;
}