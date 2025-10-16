#include <unordered_map>

// Include custom utilities header
#include <utilities.h>

// Use standard namespace
using namespace std;

class Solution {
public:
    int findSmallestInteger(vector<int>& nums, int value) {
        // Initialize an unordered map to track count of positive remainders
        unordered_map<int,int> cnt;

        // Count remainders, handling negatives
        for (auto x : nums) {
            int r = ((x % value) + value) % value;
            cnt[r]++;
        }

        // Initialize minimum excluded value to 0
        int mex = 0;

        // Loop until minimum excluded value found
        while (true) {
            // Calculate the remainder of minimum excluded value % value
            int rem = mex % value;

            if(cnt[rem] > 0) { // Can form this number, decrement counter
                cnt[rem]--; 
            } else { // Can't form this number, break
                break;
            }

            // Increment minimum excluded value                
            mex++;
        }

        // Return the minimum excluded value
        return mex;
    }
};

int main() {
    printStartBanner("2598. Smallest Missing Non-Negative Integer After Opeerations", "O(N)", "O(value)");

    // Initialize the solution
    Solution s;

    // Get the mode to run program in from user
    string mode = selectMode();

    if(isCustomMode(mode)) { // If custom mode, run with user input
        customModeSelected();

        // Initialize input string and loop
        string input;
        while(true) {
            // Get the nums vector to use from the user
            cout << "Enter nums to use as a comma-separated string: ";
            getline(cin, input);
            toLowercase(input);

            // If exit or quit inputted, exit program
            if(isExitMode(input) || isQuitMode(input)) {
                return quitModeSelected();
            }

            // Tokenize input into int vector nums
            vector<int> nums = stringToIntVector(input);

            // If no nums entered, skip
            if(nums.empty()) {
                cout << "INFO: No nums entered. Skipping..." << endl;
                continue;
            }

            // Get the value to use from the user
            cout << "Enter value to use as an int: ";
            getline(cin, input);
            toLowercase(input);

            // If exit or quit inputted, exit program
            if(isExitMode(input) || isQuitMode(input)) {
                return quitModeSelected();
            }

            // Attempt to convert input to int value
            int value;
            try { // Try to convert the input
                value = stoi(input);
            } catch(...) { // Catch unconvertable type, error and skip
                cout << "ERROR: Invalid input '" << input << "'. Please only enter an integer. Skipping..." << endl;
                continue;
            }

            // Calculate and print result
            cout << "The minimum excluded value is " << s.findSmallestInteger(nums, value) << endl;

        }
    } else if(isDemoMode(mode)) { // If demo mode, run with demo data
        demoModeSelected();

        // Create a 2D int vector demoData to hold sets of demo vectors to run program with
        vector<vector<int>> demoData = {
            {1,-10,7,13,6,8},
            {1,-10,7,13,6,8}
        };

        // Create an int vector to hold demoValues to run program with
        vector<int> demoValues = {5,7};

        // Loop over sets of demo data, print, then calculate and print the minimum excluded value
        for(int i = 0; i < demoData.size(); i++) {
            // Print out the demo data set being used
            cout << "Running program with data: ";
            for(const auto& data : demoData[i]) {
                cout << data << " ";
            }
            cout << endl;

            // Print out the demo value being used
            cout << "Running program with value: " << demoValues[i] << endl;

            // Calculate and print result
            cout << "Minimum excluded value is " << s.findSmallestInteger(demoData[i], demoValues[i]) << endl;
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // If exit or quit mode selected, exit program
        return quitModeSelected();
    } else { // Else, unknown mode, error
        return unknownModeSelected(mode);
    }

    // Exit program successfully
    return 0;
}