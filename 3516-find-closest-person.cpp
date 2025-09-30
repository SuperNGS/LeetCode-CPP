#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>

// Custom utilities header
#include <utilities.h>

// Use standard namespace
using namespace std;

class Solution {
public:
    int findClosest(int x, int y, int z) {

        // Calculate how many steps z is from x
        int xSteps = std::abs(z - x);

        // Calculate how many steps z is from y
        int ySteps = std::abs(z - y);

        // Return 1 if x is closer, 2 if y is closer, or 0 if they are equal
        if(xSteps < ySteps) {
            return 1;
        } else if(ySteps < xSteps) {
            return 2;
        } else {
            return 0;
        }
    }
};

int main() {
    printStartBanner("3541. Find Closest Person", "O(1)", "O(1)");

    // Initialize the Solution
    Solution s;

    // Get the mode to run in from the user
    string mode = selectMode();
    
    if(isCustomMode(mode)) { // If custom mode selected, run with user input
        customModeSelected();

        // Initialize input string and start loop
        string input;
        while(true) {
            // Get the x value from the user
            int x;
            cout << "Enter value for x or press enter to exit: ";
            getline(cin, input);
            toLowercase(input);

            if(isQuitMode(input)) { // If quit mode selected, exit program
                return quitModeSelected();
            } else if(isExitMode(input)) { // If no input entered or exit mode selected, break loop
                exitModeSelected();
                break;
            }

            try {
                x = stoi(input);
            } catch(...) { // If conversion fails, print error and skip to next iteration of loop
                cout << "Invalid input: " << input << ". Please enter only integers. Skipping..." << endl;
                continue;
            }

            // Get the y value from the user
            int y;
            cout << "Enter value for y or press enter to quit: ";
            getline(cin, input);
            toLowercase(input);
            
            if(isQuitMode(input)) { // If quit mode selected, exit program
                return quitModeSelected();
            } else if(isExitMode(input)) { // If no input entered or exit mode selected, break loop
                exitModeSelected();
                break;
            }

            try {
                y = stoi(input);
            } catch(...) { // If conversion fails, print error and skip to next iteration of loop
                cout << "Invalid input: " << input << ". Please enter only integers. Skipping..." << endl;
                continue;
            }

            // Get the z value from the user
            int z;
            cout << "Enter value for z or press enter to quit: ";
            getline(cin, input);
            toLowercase(input);

            if(isQuitMode(input)) { // If quit mode selected, exit program
                return quitModeSelected();
            } else if(isExitMode(input)) { // If no input entered or exit mode selected, break loop
                exitModeSelected();
                break;
            }

            try {
                z = stoi(input);
            } catch(...) { // If conversion fails, print error and skip to next iteration of loop
                cout << "Invalid input: " << input << ". Please enter only integers. Skipping..." << endl;
                continue;
            }

            // Compute whose closer: x, y, or both equal
            int closest = s.findClosest(x, y, z);

            // Interpret output of closest (1 = x is closest, 2 = y is closest, 0 = equidistant)
            if(closest == 1) {
                cout << "x is closest to z" << endl;
            } else if(closest == 2) {
                cout << "y is closest to z" << endl;
            } else if(closest == 0){
                cout << "x and y are equally close to z" << endl;
            }
        }

    } else if(mode == "demo" || mode == "d") { // If mode is "demo" or "d", demo mode selected
        // Initialize demo data as a vector of tuples {x, y, z}
        vector<tuple<int, int, int>> values = {{1,2,3}, {5,3,7}, {4,-4,0}};

        // Loop through all tuples in demo data
        for(const auto& value : values) {
            cout << "Given values x = " << get<0>(value) << ", y = " << get<1>(value) << ", and z = " << get<2>(value) << ": ";

            int closest = s.findClosest(get<0>(value), get<1>(value), get<2>(value));

            // Interpret output of closest (1 = x is closest, 2 = y is closest, 0 = equidistant)
            if(closest == 1) {
                cout << "x is closest to z" << endl;
            } else if(closest == 2) {
                cout << "y is closest to z" << endl;
            } else if(closest == 0){
                cout << "x and y are equally close to z" << endl;
            }
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // If exit or quit mode selected, exit program
        return quitModeSelected();
    } else { // If mode matchest none of the above, print and return error
        cout << "Invalid mode: " << mode;
        return -1;
    }

    return 0;
}