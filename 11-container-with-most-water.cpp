#include <vector>
#include <sstream>

// Custom utilities header
#include <utilities.h>

// Use standard namespace
using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        // Set a tracker for highest area and a tracker for current area
        int highest = 0, current = 0;
        // Set two pointers: left (start of array) and right (end of array)
        int left = 0, right = height.size() - 1;

        // While the two pointers have not crossed, loop
        while(left < right) {
            if(height[left] < height[right]) { // If left height is smaller, use it as width and increment pointer
                // Area is length (distance between left and right) * width (left height)
                current = (right - left) * height[left];
                left++;
            } else { // If right height is smaller, use it as length and decrement pointer
                // Area is length (distance between left and right) * width (right height)
                current = (right - left) * height[right];
                right--;
            }

            // If new highest area, set it
            if(highest < current) {
                highest = current;
            }
        }

        // Return highest area
        return highest;
    }
};

int main() {
    printStartBanner("11. Container With Most Water", "O(n)", "O(1)");

    // Initialize the solution
    Solution s;

    // Prompt user for mode
    string mode = selectMode();

    if(isCustomMode(mode)) { // If custom mode, run with user input
        customModeSelected();

        // Initialize input string and loop
        string input;
        while(true) {
            cout << "Input list of heights as a comma-separated string: ";
            getline(cin, input);
            toLowercase(input);

            if(isExitMode(input)) { // If exit mode, break loop
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) { // If quit mode, exit program
                return quitModeSelected();
            }

            // Attempt to tokenize input into int vector values
            vector<int> values;
            stringstream ss(input);
            string token;
            while(getline(ss, token, ',')) {
                try { // Attempt to convert token to int and push back onto values
                    values.push_back(stoi(token));
                } catch(...) { // Catch invalid type, error and skip
                    cout << "ERROR: Invalid input '" << token << "'. Please only enter integers. Skipping..." << endl;
                    continue;
                }
            }

            // If no values entered, reloop
            if(values.empty()) {
                cout << "INFO: No values entered. Skipping..." << endl;
                continue;
            }

            // Print out the values
            cout << "Running with values: ";
            for(const auto& val : values) {
                cout << val << " ";
            }
            cout << endl;

            // Calculate and print maxArea()
            cout << "Max area is " << s.maxArea(values) << endl;
        }
    } else if(isDemoMode(mode)) { // If demo mode selected, run with demo data
        demoModeSelected();

        // Create a 2D int vector of demo data
        vector<vector<int>> demoData = {
            {1,8,6,2,5,4,8,3,7},
            {1,1}
        };

        // Loop through sets of demo data, print, then calculate and print maxArea()
        for(vector<int> data : demoData) {
            cout << "Running with values: ";
            for(const auto& val : data) {
                cout << val << " ";
            }
            cout << endl;

            cout << "The max area is " << s.maxArea(data) << endl;
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // If quit or exit selected, quit program
        return quitModeSelected();
    } else { // Else, unknown mode selected, error
        return unknownModeSelected(mode);
    }

    // Exit program successfully
    return 0;
}