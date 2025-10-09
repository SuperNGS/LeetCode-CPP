#include <vector>
#include <sstream>

// Include custom utilities header
#include <utilities.h>

// Use standard namespace
using namespace std;

class Solution {
public:
    long long minTime(vector<int>& skill, vector<int>& mana) {
        // Get n, the number of wizards
        int n = skill.size();
        // Create a vector to store completion times
        vector<long long> times(n);

        // Loop through each potion
        for(const auto& m : mana){
            // Initialize a holder for this potions completion time
            long long complete = 0;

            // Loop through all wizards, compute when the last wizard finishes
            for(int i = 0; i < n; i++) {
                complete = max(complete, times[i]) + 1LL * skill[i] * m;
            }

            // Update the times vector with the last wizards time
            times[n-1] = complete;

            // Backwards pass, update times as start time + time for each wizard
            for(int i = n-2; i >= 0; i--) {
                times[i] = times[i + 1] - 1LL * skill[i + 1] * m;
            }
        }

        // Answer is the final wizards time
        return times[n - 1];
    }
};

int main() {
    printStartBanner("3494. Find the Minimum Amount ofTime to Brew Potions", "O(N^2)", "O(N)");

    // Initialize the solution
    Solution s;

    // Get the mode to run program in
    string mode = selectMode();

    if(isCustomMode(mode)) { // If custom mode, run with user input
        customModeSelected();

        // Initialize input and begin loop
        string input;
        while(true) {
            cout << "Input wizard skill levels as a comma-separated string: ";
            getline(cin, input);
            toLowercase(input);

            if(isExitMode(input)) { // if exit mode selected, break loop
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) { // If quit mode selected, exit program
                return quitModeSelected();
            }

            // Attempt to tokenize the input into the skills int vector
            vector<int> skills;
            stringstream sss(input);
            string token;
            while(getline(sss, token, ',')) {
                try { // Try to convert token to an int and push back onto skills
                    skills.push_back(stoi(token));
                } catch(...) { // Catch invalid type, error and skip
                    cout << "ERROR: Invalid input '" << token << "'. Please only enter integers. Skipping..." << endl;
                    continue;
                }
            }

            // If no skills, skip
            if(skills.empty()) {
                cout <<"ERROR: No skills entered. Skipping..." << endl;
                continue;
            }

            cout << "Enter mana costs as a comma-separated string: ";
            getline(cin, input);
            toLowercase(input);

            if(isExitMode(input)) { // if exit mode selected, break loop
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) { // If quit mode selected, exit program
                return quitModeSelected();
            }

            // Attempt to tokenize the input into mana vector
            vector<int> mana;
            stringstream ssm(input);
            while(getline(ssm, token, ',')) {
                try { // Try to convert the token to an int and push back onto mana
                    mana.push_back(stoi(token));
                } catch(...) { // Catch invalid type, error and skip
                    cout << "ERROR: Invalid input '" << token << "'. Please only enter integers. Skipping..." << endl;
                    continue;
                }
            }

            // If no mana values, skip
            if(mana.empty()) {
                cout << "ERROR: No mana values enterd. Skipping..." << endl;
                continue;
            }

            // Calculate and print result
            cout << "The minimum time to complete all potions is " << s.minTime(skills, mana) << endl;
        }
    } else if(isDemoMode(mode)) { // If demo mode, run with demo data
        demoModeSelected();

        // Create a 2D vector of the skill for each set of wizards
        vector<vector<int>> demoSkills = {
            {
                1,5,2,4
            },
            {
                1,1,1
            },
            {
                1,2,3,4
            }
        };
        // Create a 2D vector of the mana cost for each set of potions
        vector<vector<int>> demoMana = {
            {
                5,1,4,2
            },
            {
                1,1,1
            },
            {
                1,2
            }
        };

        // Loop through each set of demo data, print, then calculate min time and print
        for(int i = 0; i < demoSkills.size(); i++) {
            // Get the skills vector to use
            vector<int> skills = demoSkills[i];
            // Print skills
            cout << "Running program with skills: ";
            for(const auto& skill : skills) {
                cout << skill << " ";
            }
            cout << endl;

            // Get the mana vector to use
            vector<int> mana = demoMana[i];
            // print mana
            cout << "Running program with mana: ";
            for(const auto& m : mana) {
                cout << m << " ";
            }
            cout << endl;

            // Calculate and print result
            cout << "Minimimum time to complete all potions: " << s.minTime(skills, mana) << endl;
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // If exit or quit mode, exit program
        return quitModeSelected();
    } else { // Else, unknown mode, error
        return unknownModeSelected(mode);
    }

    // Exit program successfully
    return 0;
}