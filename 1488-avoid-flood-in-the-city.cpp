#include <unordered_map>

// Include custom utilities header
#include <utilities.h>

// Use standard namespace
using namespace std;

class Solution {
public:
    vector<int> avoidFlood(vector<int>& rains) {
        // Get total amount of rains
        int n = rains.size();
        // Initialize ans vector, fill dry days with any lake (1)
        vector<int> ans(n, 1);
        // Map lake to last day it was filled
        unordered_map<int, int> lastRain;
        // Set of dry day indices
        set<int> dryDays; 

        // Loop through all rain days
        for (int i = 0; i < n; ++i) {
            if (rains[i] == 0) { // If no rain on day i, add it as a dry day
                dryDays.insert(i);
            } else { // Else, rain occured, solve
                int lake = rains[i];
                ans[i] = -1; // must be -1 on rain days

                // If this lake was already full, find a dry day after lastRain[lake]
                if (lastRain.count(lake)) {
                    auto dry = dryDays.lower_bound(lastRain[lake] + 1);

                    // If no valid dry day, flood is inevitable. Return {}
                    if (dry == dryDays.end()) {
                        return {};
                    }

                    // Use this dry day to dry the lake
                    ans[*dry] = lake;
                    dryDays.erase(dry);
                }

                // Update the day this lake was last filled
                lastRain[lake] = i;
            }
        }

        // Return the answer
        return ans;
    }
};

int main() {
    printStartBanner("1488. Avoid Flood in the City", "O(Nlogn)", "O(N)");

    // initialize the solution
    Solution s;

    // Get mode to run program in from user
    string mode = selectMode();

    if(isCustomMode(mode)) { // If custom mode selected, run with user input
        customModeSelected();

        // Initialize input string and loop
        string input;
        while(true) {
            // Get the rains from user input
            cout << "Enter rains vector as a comma-separated string of positive ints: ";
            getline(cin, input);
            toLowercase(input);

            // If exit or quit entered, exit program
            if(isExitMode(input) || isQuitMode(input)) {
                return quitModeSelected();
            }

            // Convert input string to int vector rains
            vector<int> rains = stringToIntVector(input);

            // If no rains, skip
            if(rains.empty()) {
                cout << "INFO: No rains entered. Skipping..." << endl;
                continue;
            }

            // If negative rain value entered, skip
            if(any_of(rains.begin(), rains.end(), [](int value) {return value < 0;})) {
                cout << "ERROR: Negative rain value entered. Please only enter positive integers. Skipping..." << endl;
                continue;
            }

            // Print the rains
            cout << "Running program with rains:" << endl;
            for(int i = 0; i < rains.size(); i++) {
                if(rains[i] == 0) {
                    cout << "\tDay " << i << ": No rain" << endl;
                } else {
                    cout << "\tDay " << i << ": Rain over lake " << rains[i] << endl;
                }
            }

            // Calculate the resulting vector
            vector<int> result = s.avoidFlood(rains);

            // Print the resulting vector
            cout << "Result:" << endl;
            for(int i = 0; i < result.size(); i++) {
                if(result[i] == -1) {
                    cout << "\tDay " << i << ": A lake was filled" << endl;
                } else {
                    cout << "\tDay " << i << ": Lake " << result[i] << " was dried" << endl;
                }
            }

            // Handle edge case where result is empty vector (avoiding flood is impossible)
            if(result.empty()) {
                cout << "\tAvoiding flood is impossible" << endl;
            }
        }
    } else if(isDemoMode(mode)) { // If demo mode selected, run with demo data
        demoModeSelected();

        // Initialize 2D int vector demoRains to act as sets of rains
        vector<vector<int>> demoRains = {
            {1,2,3,4},
            {1,2,0,0,2,1},
            {1,2,0,1,2}
        };

        // Loop through the demo data, print the set, then calculate and print the result
        for(vector<int>& rains : demoRains) {
            // Print the set of rains
            cout << "Running program with rains:" << endl;
            for(int i = 0; i < rains.size(); i++) {
                if(rains[i] == 0) {
                    cout << "\tDay " << i << ": No rain" << endl;
                } else {
                    cout << "\tDay " << i << ": Rain over lake " << rains[i] << endl;
                }
            }

            // Calculate the resulting vector
            vector<int> result = s.avoidFlood(rains);

            // Print the result
            cout << "Result:" << endl;
            for(int i = 0; i < result.size(); i++) {
                if(result[i] == -1) {
                    cout << "\tDay " << i << ": A lake was filled" << endl;
                } else {
                    cout << "\tDay " << i << ": Lake " << result[i] << " was dried" << endl;
                }
            }

            // Handle edge case where result is empty array (flood occurs)
            if(result.empty()) {
                cout << "\tImpossible to avoid flood" << endl;
            }
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // If exit or quit mode selected, exit program
        return quitModeSelected();
    } else { // Else, unknown mode, error
        return unknownModeSelected(mode);
    }

    // Exit program successfully
    return 0;
}