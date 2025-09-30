#include <cstdlib>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

// Custom utilities header
#include <utilities.h>

// Use standard namespace
using namespace std;

class Solution {
public:
    int maxFrequencyElements(vector<int>& nums) {
        // Initialize map to hold values and their frequency
        unordered_map<int, int> frequency;

        // Loop through nums, assign to map and update frequency
        for(const auto& num : nums) {
            frequency[num]++;
        }

        // Set trackers for the highest frequency along with elements matching that frequency
        int highest_frequency = 0;
        int frequency_count = 0;

        // Loop through key-value pairs of map, tracking the highest frequency items
        for(const auto& kp: frequency) {
            if(kp.second > highest_frequency) { // If new highest frequency found, reassign highest_frequency and frequency_count
                highest_frequency = kp.second;
                frequency_count = kp.second;
            } else if(kp.second == highest_frequency) { // Else if frequency matches highest_frequency, update frequency count
                frequency_count += kp.second;
            }
        }

        // return frequency_count
        return frequency_count;
    }
};

int main() {
    printStartBanner("3005. Count Elements With Maximum Frequency", "O(n)", "O(n)");

    // Initialize solution
    Solution s;

    // Prompt user to select mode: custom, demo or quit
    string mode = selectMode();

    if(isCustomMode(mode)) { // If custom mode selected, run with user input
        customModeSelected();

        // Initialize input string and start loop
        string input;
        while(input != "quit" || input != "q") {
            // Prompt user to enter comma-separated string of values
            cout << "Enter values as a comma-separated string or press enter to exit: ";
            getline(cin, input);
            toLowercase(input);

            if(isExitMode(input)) { // If no input entered or exit mode selected, break loop
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) { // If quit mode selected, exit program
                return quitModeSelected();
            }

            // Replace all commas with spaces
            char delimiter = ',';
            replace(input.begin(), input.end(), delimiter, ' ');
            
            // Create a vector to hold values, initialize stringstream
            vector<int> values;
            istringstream iss(input);
            int value;
            
            // Extract integers directly from the stream, print to console
            try {
                cout << "Calculating max frequency of integers: ";
                while (iss >> value) {
                    cout << value << " ";
                    values.push_back(value);
                }
                cout << endl;
            } catch(...) { // If conversion fails, print error and skip to next iteration of loop
                cout << "Invalid input: " << input << ". Please enter only integers. Skipping..." << endl;
                continue;
            }

            // Calculate max frequency
            cout << "Max frequency is " << s.maxFrequencyElements(values) << endl;

        }


    } else if(isDemoMode(mode)) { // If demo mode selected, run with demo data
        demoModeSelected();

        // Create a vector of vectors to hold demo data
         vector<vector<int>> valuesVector = {{1, 2, 3, 4, 5}, {1,2,2,3,4,4,5,6}, {1,1,2,2,3,3,4,5,5,6,6,6,7}};
        
        // For each set of demo data, print it out and then calculate max frequency
        for(auto& values : valuesVector) {
            cout << "Calculating max frequency of integers: ";
            for(const auto& value : values) {
                cout << value << " ";
            }
            cout << endl;

            // Calculate and print max frequency
            cout << "Max frequency is " << s.maxFrequencyElements(values) << endl;
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // If quit or exit mode selected, exit program
        return quitModeSelected();
    } else { // Else, unknown mode, error
        return unknownModeSelected(mode);
    }

    // Exit program
    return 0;
}