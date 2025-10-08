#include <bits/stdc++.h>
#include <sstream>

// Custom utilities header
#include <utilities.h>

// Use standard namespace
using namespace std;

class Solution {
public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        // Create a vector to store valid pairs per spell
        vector<int> pairs;

        // Sort the potions by strength
        sort(potions.begin(), potions.end());

        // Get the size of spells and potions
        int n = spells.size();
        int m = potions.size();

        // Loop through each spell
        for(int i = 0; i < n; i++) {
            // Get the current spell
            long long spell = spells[i];

            // Track the lower and upper bounds
            int low = 0;
            int high = m - 1;

            // Set a tracker for the index of the weakest viable potion
            int ind = -1;

            // Loop until lower and upper bounds cross
            while(low <= high) {
                // Find the midpoint between the two bounds
                int mid = (high + low) / 2;

                if(spell * potions[mid] < success) { // If spell * potion is less than success, update lower bounds
                    low = mid + 1;
                } else if(spell * potions[mid] >= success){ // Else if spell * potion greater or equal that success, track index and update upper bounds
                    high = mid - 1;
                    ind = mid;
                }
            }

            // Assign the number of viable pairs or 0 to the next slot in the pairs vector
            ind == -1 ? pairs.push_back(0) : pairs.push_back(m - ind);
        }

        // Return the vector of pairs
        return pairs;
    }
};

int main() {
    printStartBanner("2300. Successful Pairs of Spells and Potions", "O(Nlogn + Mlogm)", "O(1)");

    // Initialize the solution
    Solution s;

    // Get the demo mode from the user
    string mode = selectMode();

    if(isCustomMode(mode)) { // If custom mode selected, run with user input
        customModeSelected();

        // Initialize input string and start loop
        string input;
        while(true) {
            cout << "Please enter spell strengths as a comma-separated string: ";
            getline(cin, input);
            toLowercase(input);

            if(isExitMode(input)) { // If exit mode selected, break loop
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) { // If quit mode selected, quit program
                return quitModeSelected();
            }

            // Initialize string stream and tokenize input into spells vector
            vector<int> spells;
            stringstream sss(input);
            string token;
            while(getline(sss, token, ',')) {
                try { // Try to convert token into int and push back onto spells
                    spells.push_back(stoi(token));
                } catch(...) { // Catch invalid type and skip
                    cout << "ERROR: Invalid input '" << token << "'. Please only enter integers. Skipping..." << endl;
                    continue;
                }
            }

            cout << "Please enter potion strengths as a comma-separated string: ";
            getline(cin, input);
            toLowercase(input);

            if(isExitMode(input)) { // If exit mode selected, break loop
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) { // If quit mode selected, quit program
                return quitModeSelected();
            }

            // Initialize string stream and tokenize input into spells vector
            vector<int> potions;
            stringstream ssp(input);
            while(getline(ssp, token, ',')) {
                try { // Try to convert token into int and push back onto potions
                    potions.push_back(stoi(token));
                } catch(...) { // Catch invalid type and skip
                    cout << "ERROR: Invalid input '" << token << "'. Please only enter integers. Skipping..." << endl;
                    continue;
                }
            }

            cout << "Please enter success threshold as an integer: ";
            getline(cin, input);
            toLowercase(input);

            if(isExitMode(input)) { // If exit mode selected, break loop
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) { // If quit mode selected, quit program
                return quitModeSelected();
            }

            // Get the success threshold from user input
            long long success;
            try { // Try to convert input into a long long
                success = (long long)stoi(input);
            } catch(...) { // Catch invalid input type, skip
                cout << "ERROR: Invalid input '" << input << "'. Please only enter integers. Skipping..." << endl;
                continue;
            }

            // Calculate the result
            vector<int> result = s.successfulPairs(spells, potions, success);

            // Print the result
            cout << "Number of successful pairs: [ ";
            for(const auto& res : result) {
                cout << res << " ";
            }
            cout << "]" << endl;
            
        }
    } else if(isDemoMode(mode)) { // If demo mode selected, run with demo data
        demoModeSelected();

        // Create 2D vectors of demo spells and potions
        vector<vector<int>> demoSpells = {
            {5,1,3},
            {3,1,2}
        };
        vector<vector<int>> demoPotions = {
            {1,2,3,4,5},
            {8,5,8}
        };
        // Create a vector of demo success thresholds
        vector<long long> demoSuccess = {7, 16};

        // Loop through each set of demo data, print it, and calculate the number of valid pairs
        for(int i = 0; i < demoSpells.size(); i++) {
            // Get and print the current demo's spells
            vector<int> spells = demoSpells[i];
            cout << "Demo spells:" << endl;
            for(int j = 0; j < spells.size(); j++) {
                cout << "\tSpell #" << j << ", Strength: " << spells[j] << endl;
            }

            // Get and print the current demo's potions
            vector<int> potions = demoPotions[i];
            cout << "Demo potions:" << endl;
            for(int j = 0; j < potions.size(); j++) {
                cout << "\tPotion #" << j << ", Strength: " << potions[j] << endl;
            }

            // Get and print the current demo's success integer
            int success = demoSuccess[i];
            cout << "Success: " << success << endl;

            // Calculate the resulting pairs int vector
            vector<int> result = s.successfulPairs(spells, potions, success);

            // Print the result
            cout << "Resulting valid pair counts: [ ";
            for(const auto& res : result) {
                cout << res << " ";
            }
            cout << "]" << endl;
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // If exit or quit mode selected, exit program
        return quitModeSelected();
    } else { // Else, unknown mode selected, error
        return unknownModeSelected(mode);
    }

    // Exit the program successfully
    return 0;
}