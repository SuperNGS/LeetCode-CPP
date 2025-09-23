#include <cstdlib>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

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
    cout << "Count Elements with Maximum Frequency Demo" << endl << endl;

    Solution s = Solution();

    // Prompt user to select mode, custom or demo
    string mode;
    cout << "Select mode (custom or demo): ";
    cin >> mode;

    if(mode == "custom" || mode == "c") {
        string input;
        while(input != "quit" || input != "q") {
            // Prompt user to enter comma-separated string of values
            cout << "Enter values as a comma-separated string: ";
            cin >> input;

            // If user types 'quit' or 'q', exit the loop
            if(input == "quit" || input == "q") {
                break;
            }

            // Replace all commas with spaces
            char delimiter = ',';
            replace(input.begin(), input.end(), delimiter, ' ');
            
            // Create a vector to hold values, initialize stringstream
            vector<int> values;
            istringstream iss(input);
            int value;
            
            // Extract integers directly from the stream, print to console
            cout << "Calculating max frequency of integers: ";
            while (iss >> value) {
                cout << value << " ";
                values.push_back(value);
            }
            cout << endl;

            // Calculate max frequency
            cout << "Max frequency is " << s.maxFrequencyElements(values) << endl;

        }


    } else if(mode == "demo" || mode == "d") {
        // Create a vector of vectors to hold demo data
         vector<vector<int>> valuesVector = {{1, 2, 3, 4, 5}, {1,2,2,3,4,4,5,6}, {1,1,2,2,3,3,4,5,5,6,6,6,7}};
        
        // For each set of demo data, print it out and then calculate max frequency
        for(auto& values : valuesVector) {
            cout << "Calculating max frequency of integers: ";
            for(const auto& value : values) {
                cout << value << " ";
            }
            cout << endl;

            cout << "Max frequency is " << s.maxFrequencyElements(values) << endl;
        }
    } else {
        cout << "Unknown mode: " << mode;
        return 1;
    }
    return 0;
}