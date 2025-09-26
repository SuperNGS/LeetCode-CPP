#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>

using namespace std;

class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        // Sort the nums vector
        sort(nums.begin(), nums.end());

        // Initialize count to 0
        int count = 0;

        // Loop over all possible k values
        for(int k = nums.size() - 1; k >= 2; k--) {

            // Calculate the left and right bounds to search
            int left = 0;
            int right = k - 1;

            // Loop while left is less than right
            while(left < right) {
                if(nums[left] + nums[right] > nums[k]) { // if left + right > mid, triangle found
                    count += right - left; // Increment count by right - left, all values satisfying the condition
                    right--; // Decrement the right pointer
                } else { // Else, triangle not found
                    left++; // Increment left pointer
                }
            }
        }

        // Return count
        return count;
    }
};

int main() {
    cout << "Valid Triangle Number Demo" << endl << endl;

    // Initialize solution
    Solution s = Solution();

    // Get the mode to run program in from user
    string mode;
    cout << "Select mode ([c]ustom, [d]emo, [q]uit): ";
    cin >> mode;
    transform(mode.begin(), mode.end(), mode.begin(), ::tolower);

    // Sets to match the various operation modes (custom, demo, or quit)
    set<string> customMode = {"custom", "[c]ustom", "c", "[c]"};
    set<string> demoMode = {"demo", "[d]emo", "d", "[d]"};
    set<string> quitMode = {"quit", "[q]uit", "q", "[q]"};

    if(customMode.find(mode) != customMode.end()) { // If custom mode, run with user input
        cout << "Custom mode selected" << endl;

        // Initialize holder for user input and start looping
        string input;
        while(true) {
            // Get the comma-separated string of values from user
            cout << "Enter values as a comma-separated string: ";
            cin >> input;
            transform(input.begin(), input.end(), input.begin(), ::tolower);

            // If quit entered, exit the loop
            if(quitMode.find(input) != quitMode.end()) {
                break;
            }

            // Tokenize the inputted string and print
            vector<int> tokens;
            stringstream ss(input);
            string token;
            cout << "Running with values: ";
            while(getline(ss, token, ',')) {
                cout << token << " ";
                tokens.push_back(stoi(token));
            }
            cout << endl;

            // Calculate the valid triangle number and print
            cout << "The total number of valid triangles in the set is " << s.triangleNumber(tokens) << endl;
        }
    } else if(demoMode.find(mode) != demoMode.end()) { // If demo mode, run with demo data
        cout << "Demo mode selected" << endl;

        // Initialize 2D vector of demo data
        vector<vector<int>> demoData =  {
                                            {2, 2, 3, 4},
                                            {4, 2, 3, 4},
                                            {1, 2, 3, 4, 5, 6, 7, 8, 9}
                                        };
        
        // Loop through all sets of demo data
        for(vector<int> data : demoData) {
            // Print the set of demo values
            cout << "Running with numbers: ";
            for(const auto& value : data) {
                cout << value << " ";
            }
            cout << endl;

            // Calculate and print the valid triangle number
            cout << "The total number of valid triangles in the set is " << s.triangleNumber(data) << endl;
        }
    } else if(quitMode.find(mode) != quitMode.end()) { // If quit mode, exit program
        cout << "Quitting..." << endl;
        return 0;
    } else { // Else, invalid mode. Error
        cout << "Invalid mode: " << mode << endl;
        return -1;
    }
    // Exit the program
    return 0;
}