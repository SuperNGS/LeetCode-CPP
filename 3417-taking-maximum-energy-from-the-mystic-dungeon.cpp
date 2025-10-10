#include <vector>
#include <sstream>

// Include custom utilities header
#include <utilities.h>

// Use standard namespace
using namespace std;

class Solution {
public:
    int maximumEnergy(vector<int>& energy, int k) {
        // Set res to minimum possible int, get the length of energy vector n
        int res = -INT_MAX, n = energy.size();
        
        // Loop through each valid starting position
        for(int start = 0; start < k; start++) {
            // Initialize holder for accrued energy to 0
            int accrued_energy = 0;

            // Loop through indexes, right to left, in k-steps
            for(int i = n - start - 1; i >= 0; i -= k) {
                // Add energy[i] to accrued
                accrued_energy += energy[i];
                // Set res to the max of res and accrued energy
                res = max(res, accrued_energy);
            }
        }

        return res;
    }
};

int main() {
    printStartBanner("3417. Taking Maximum Energy From the Mystic Dungeon", "O(n)", "O(1)");

    // Initialize the solution
    Solution s;

    // Get the mode to run in
    string mode = selectMode();

    if(isCustomMode(mode)) { // If custom mode selected, run with user input
        customModeSelected();

        // Initialize input holder and loop
        string input;
        while(true) {
            cout << "Please enter energies as a comma-separated string: ";
            getline(cin, input);
            toLowercase(input);

            if(isExitMode(input)) { // If exit mode selected, break loop
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) { // If quit mode selected, exit program
                return quitModeSelected();
            }

            // Attempt to tokenize input into energies int vector
            vector<int> energies;
            stringstream ss(input);
            string token;
            while(getline(ss, token, ',')) {
                try { // Attempt to convert token into an int and push back on energies
                    energies.push_back(stoi(token));
                } catch(...) { // Catch invalid type, error and skip
                    cout << "ERROR: Invalid input '" << token << "'. Please only enter integers. Skipping..." << endl;
                    continue;
                }
            }

            // If no energies, skip
            if(energies.empty()) {
                cout << "INFO: No energy values entered. Skipping..." << endl;
                continue;
            }

            // Get the k value from the user
            cout << "Enter a K value as an integer: ";
            getline(cin, input);
            toLowercase(input);

            if(isExitMode(input)) { // If exit mode selected, break loop
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) { // If quit mode selected, exit program
                return quitModeSelected();
            }

            // Initialize holder for a k value
            int k;
            try { // Try to convert input into an int and assign to k
                k = stoi(input);
            } catch(...) { // Catch unconvertable input, error and skip
                cout << "ERROR: Invalid input '" << input << "'. Please only enter integers. Skipping..." << endl;
                continue;
            }

            // Calculate and print the answer
            cout << "Maximum energy possible is: " << s.maximumEnergy(energies, k) << endl;
        }
    } else if(isDemoMode(mode)) { // If demo mode selected, run with demo data
        demoModeSelected();
        // Set up 2D vector of demoEnergies and vector of demoKs to run demo with
        vector<vector<int>> demoEnergies = {
            {5,2,-10,-5,1},
            {-2,-3,-1}
        };
        vector<int> demoKs = {3,2};

        // Loop through each set of demo data, print it, then calculate and print the result
        for(int i = 0; i < demoEnergies.size(); i++) {
            // Get the energies to run demo with and print
            vector<int> energies = demoEnergies[i];
            cout << "Energies to run demo with: ";
            for(const auto& energy : energies) {
                cout << energy << " ";
            }
            cout << endl;

            // Get the k value to run demo with and print
            int k = demoKs[i];
            cout << "K value to run demo with: " << k << endl;

            // Calculate and print result
            cout << "Maximum energy possible: " << s.maximumEnergy(energies, k) << endl;
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // If exit or quit mode selected, exit program
        return quitModeSelected();
    } else { // Else, unknown mode selected, error
        return unknownModeSelected(mode);
    }

    // Exit program successfully
    return 0;
}