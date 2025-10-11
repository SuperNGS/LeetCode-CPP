#include <bits/stdc++.h>
#include <sstream>

// Include custom utilities header
#include <utilities.h>

// Use standard namespace
using namespace std;

class Solution {
public:
    long long maximumTotalDamage(vector<int>& power) {
        // Initialize an {int, int} map count
        map<int, int> count;

        // Loop over power vector and assign to count
        for(int x : power) {
            count[x]++;
        }

        // Create a vector of int pairs to track key and value of map count
        vector<pair<int, int>> vec = {{-INT_MAX, 0}};
        for(auto &p : count) {
            vec.push_back(p);
        }

        // Get n, the length of vec, and initialize dp as a vector of long longs
        int n = vec.size();
        vector<long long> dp(n);

        // Initialize highest tracker to 0
        long long highest = 0;

        // Loop over all start indexes
        for(int i = 1, j = 1; i < n; i++) {
            // Loop and calculate new highest
            while(j < i && vec[j].first < vec[i].first - 2) {
                highest = max(highest, dp[j++]);
            }
            // Calculate the new value of dp[i]
            dp[i] = highest + 1LL * vec[i].first * vec[i].second;
        }

        // Return the max element of the dp vector
        return *max_element(dp.begin(), dp.end());
    }
};

int main() {
    printStartBanner("3186. Maximum Total Damage With Spell Casting", "O(N^2)", "O(N)");

    // Initialize solution
    Solution s;

    // Prompt user to select input mode
    string mode = selectMode();

    if(isCustomMode(mode)) { // If custom mode selected, run program with user input
        customModeSelected();

        // Initialize input holder and loop
        string input;
        while(true) {
            cout << "Enter power values as a comma-separated string: ";
            getline(cin, input);
            toLowercase(input);

            if(isExitMode(input)) { // If exit mode, break loop
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) { // If quit mode, exit program
                return quitModeSelected();
            }

            // Attempt to tokenize input into powers vector
            vector<int> powers;
            stringstream ss(input);
            string token;
            while(getline(ss, token, ',')) {
                try { // Try to convert token to an int and push back onto powers
                    powers.push_back(stoi(token));
                } catch(...) { // Catch invalid type, error and skip
                    cout << "ERROR: Invalid input '" << token << "'. Please only enter integers. Skipping..." << endl;
                    continue;
                }
            }

            // If no powers provided, skip
            if(powers.empty()) {
                cout << "INFO: No powers entered. Skipping..." << endl;
                continue;
            }

            // Calculate and print result
            cout << "Maximum total damage possible is " << s.maximumTotalDamage(powers) << endl;
        }
    } else if(isDemoMode(mode)) { // If demo mode selected, run program with demo input
        demoModeSelected();

        // Initialize 2D vector demoData, comprised of sets of ints
        vector<vector<int>> demoData = {
            {1,1,3,4},
            {7,1,6,6}
        };

        // Loop over and print demo data, calculate answer, and print the answer
        for(vector<int> data : demoData) {
            cout << "Running with data set: ";
            for(const auto& val : data) {
                cout << val << " ";
            }
            cout << endl;

            cout << "The maximum damage possible is " << s.maximumTotalDamage(data) << endl;
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // If exit or quit mode selected, quit program
        return quitModeSelected();
    } else { // Else, unknown mode selected, error
        return unknownModeSelected(mode);
    }

    // Exit program successfully
    return 0;
}