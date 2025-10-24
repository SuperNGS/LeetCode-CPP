#include <unordered_map>

// Use custom utilities header
#include <utilities.h>

// Use standard namespace
using namespace std;

class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        int n = nums.size();
        if (n == 0) return 0;

        // Count exact occurrences
        unordered_map<int,int> eq;
        int mn = INT_MAX, mx = INT_MIN;
        for (int v : nums) {
            eq[v]++;
            mn = min(mn, v);
            mx = max(mx, v);
        }

        // Sweep range for possible targets T: [mn - k, mx + k]
        long long L = (long long)mn - k;
        long long R = (long long)mx + k;
        // To keep array size reasonable, shift index by offset = -L
        long long offset = -L;
        int size = (int)(R - L + 3); // +3 to safely allow R+1 index
        vector<int> diff(size, 0);

        // For each nums[i], add interval [nums[i]-k, nums[i]+k]
        for (int v : nums) {
            long long a = (long long)v - k;
            long long b = (long long)v + k;
            diff[(int)(a + offset)] += 1;
            diff[(int)(b + offset + 1)] -= 1;
        }

        int best = 0;
        int running = 0;
        for (long long t = L; t <= R; ++t) {
            int idx = (int)(t + offset);
            running += diff[idx];            // coverCount at t
            int coverCount = running;
            int eqCount = 0;
            auto it = eq.find((int)t);
            if (it != eq.end()) eqCount = it->second;

            // frequency achievable for target t:
            int freq = min(coverCount, eqCount + numOperations);
            best = max(best, freq);
        }

        return best;
    }
};

int main() {
    printStartBanner("3346. Maximum Frequency of an Element After Performing Operations I", "O(N+K)", "O(K)");

    // Initialize the solution
    Solution s;

    // Get mode to run program in from user
    string mode = selectMode();

    if(isCustomMode(mode)) { // If custom mode, run with user input
        customModeSelected();

        // Initialize input string and loop
        string input;
        while(true) {
            // Prompt user to enter nums vector as comma-separated string
            cout << "Enter nums as a comma-separated string of integers: ";
            getline(cin, input);
            toLowercase(input);

            // If exit or quit selected, exit program
            if(isExitMode(input) || isQuitMode(input)) {
                return quitModeSelected();
            }

            // Get the nums vector from input
            vector<int> nums = stringToIntVector(input);

            // If no nums entered, skip
            if(nums.empty()) {
                cout << "INFO: No nums entered. Skipping..." << endl;
                continue;
            }

            // Prompt user to enter k value
            cout << "Enter an integer to act as k: ";
            getline(cin, input);
            toLowercase(input);

            // If exit or quit selected, exit program
            if(isExitMode(input) || isQuitMode(input)) {
                return quitModeSelected();
            }

            // Attempt to convert input to int k, error and skip if impossible
            int k;
            try {
                k = stoi(input);
            } catch(...) {
                cout << "ERROR: Invalid input '" << input << "'. Please only enter an integer for k. Skipping..." << endl;
                continue;
            }

            // Prompt user to enter numOperations value
            cout << "Enter an integer to act as numOperations: ";
            getline(cin, input);
            toLowercase(input);

            // If exit or quit selected, exit program
            if(isExitMode(input) || isQuitMode(input)) {
                return quitModeSelected();
            }

            // Attempt to convert input to int numOperations, error and skip if impossible
            int numOperations;
            try {
                numOperations = stoi(input);
            } catch(...) {
                cout << "ERROR: Invalid input '" << input << "'. Please only enter an integer for numOperations. Skipping..." << endl;
                continue;
            }

            // Calculate and print the result of maxFrequency()
            cout << "The max frequency of nums after operations is " << s.maxFrequency(nums, k, numOperations) << endl;
        }
    } else if(isDemoMode(mode)) { // If demo mode, run with demo data
        demoModeSelected();

        // Initialize demoNums 2D int vector to act as sets of nums
        vector<vector<int>> demoNums = {
            {1,4,5},
            {5,11,20,20}
        };
        // Initialize demoKValues int vector to act as sets of k values
        vector<int> demoKValues = {1,5};
        // Initialize demoNumOperationsValues int vector to act as sets of numOperations values
        vector<int> demoNumOperationsValues = {2,1};

        // Loop through the sets of demo data, print them, then calculate and print the result of maxFrequency()
        for(int i = 0; i < demoNums.size(); i++) {
            // Print nums
            cout << "Running program with..." << endl;
            cout << "\tnums = [ ";
            for(const auto& num : demoNums[i]) {
                cout << num << " ";
            }
            cout << "]" << endl;

            // Print k value
            cout << "\tk = " << demoKValues[i] << endl;

            // Print the numOperations value
            cout << "\tnumOperations = " << demoNumOperationsValues[i] << endl;

            // Print the result of calling maxFrequency()
            cout << "The max frequency of nums after operations is " << s.maxFrequency(demoNums[i], demoKValues[i], demoNumOperationsValues[i]) << endl;

        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // If exit or quit mode, exit program
        return quitModeSelected();
    } else { // Else, unknown mode, error
        return unknownModeSelected(mode);
    }

    // Exit program successfully
    return 0;
}