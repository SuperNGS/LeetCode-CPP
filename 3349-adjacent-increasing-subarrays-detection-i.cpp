#include <bits/stdc++.h>

// Custom utlitities header
#include <utilities.h>

// Use standard namespace
using namespace std;

class Solution {
public:
    bool hasIncreasingSubarrays(vector<int>& nums, int k) {
        // Get n, the number of elements in nums vector
        int n = nums.size();

        // If nums vector too small for two adjacent segments, return false
        if (2 * k > n) {
            return false;
        }

        //  Creator vector inc to track the length of strictly increasing run that ends at index i (inc[i])
        vector<int> inc(n, 1);

        // Loop through all nums
        for (int i = 1; i < n; ++i) {
            if (nums[i] > nums[i - 1]) { // If nums i and nums i - 1 are increasing, increment streak
                inc[i] = inc[i - 1] + 1;
            } else { // Else, reset streak to 1
                inc[i] = 1;
            }
        }

        // Check every possible starting index j so that segments are
        // [j .. j+k-1] and [j+k .. j+2k-1]
        for (int j = 0; j <= n - 2 * k; ++j) {
            // Get the end of the first and second segment
            int endFirst  = j + k - 1;
            int endSecond = j + 2 * k - 1;

            // inc[endFirst] >= k means nums[s..endFirst] is strictly increasing
            // inc[endSecond] >= k means nums[s+k..endSecond] is strictly increasing
            if (inc[endFirst] >= k && inc[endSecond] >= k) return true;
        }

        // If no two adjacent segments are found to be strictly increasing, return false
        return false;
    }
};

int main() {
    printStartBanner("3349. Adjacent Increasing Subarrays detection I", "O(n)", "O(n)");

    // Initialize the solution
    Solution s;

    // Get the mode to run in from the user
    string mode = selectMode();

    if(isCustomMode(mode)) { // Custom mode selected, run with user input
        customModeSelected();

        // Initialize input string and loop
        string input;
        while(true) {
            cout << "Enter values to use as a comma-separated string: ";
            getline(cin, input);
            toLowercase(input);

            if(isExitMode(input)) { // Exit mode selected, break loop
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) { // Quit mode selected, exit program
                return quitModeSelected();
            }

            // Attempt to tokenize the input into int vector nums
            vector<int> nums;
            stringstream ss(input);
            string token;
            while(getline(ss, token, ',')) {
                try { // Attempt to convert token to an int and push back onto nums
                    nums.push_back(stoi(token));
                } catch(...) { // Catch unconvertable type, error and skip
                    cout << "ERROR: Invalid input '" << token << "'. Please only enter integers. Skipping..." << endl;
                    continue;
                }
            }

            // If no nums entered, skip
            if(nums.empty()) {
                cout << "INFO: No nums entered. Skipping..." << endl;
                continue;
            }

            // Get the k value from the user
            cout << "Enter a k value: ";
            getline(cin, input);
            toLowercase(input);

            if(isExitMode(input)) { // Exit mode selected, break loop
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) { // Quit mode selected, exit program
                return quitModeSelected();
            }

            // Attempt to convert input to int k
            int k;
            try { // Attempt to convert input to an int
                k = stoi(input);
            } catch(...) { // Catch unconvertable type, error and skip
                cout << "ERROR: Invalid input '" << input << "'. Please only enter an integer. Skipping..." << endl;
                continue;
            }

            // Calculate and print the result
            cout << "Nums contains adjacent increasing subarrays: " << (s.hasIncreasingSubarrays(nums, k) ? "yes" : "no") << endl;
        }
    } else if(isDemoMode(mode)) { // Demo mode selected, run with demo data
        demoModeSelected();

        // Initialize 2D int vector of demo data to use
        vector<vector<int>> demoData = {
            {2,5,7,8,9,2,3,4,3,1},
            {1,2,3,4,4,4,4,5,6,7},
            {-15,19}
        };
        // Initialize int vector of demo k values to use
        vector<int> demoKValues = {3, 5, 1};

        // Loop through the sets of demo data, print, then calculate result and print
        for(int i = 0; i < demoData.size(); i++) {
            // Print the current set of data
            cout << "Running program with vector: ";
            for(const auto& val : demoData[i]) {
                cout << val << " ";
            }
            cout << endl;

            // Print the current k value
            cout << "Running program with k value: " << demoKValues[i] << endl;

            // Calculate and print the result of hasIncreasingSubarrays() with data
            cout << "Data has increasing subarrays: " << (s.hasIncreasingSubarrays(demoData[i], demoKValues[i]) ? "yes" : "no") << endl;
        }
        
    } else if(isExitMode(mode) || isQuitMode(mode)) { // Exit or quit mode selected, exit program
        return quitModeSelected();
    } else {
        return unknownModeSelected(mode);
    }

    // Exit program successfully
    return 0;
}