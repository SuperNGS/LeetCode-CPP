#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>

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
    cout << "Cind Closest Person Demo" << endl << endl;

    // Initialize the Solution object
    Solution s = Solution();

    // Get the mode to run in from the user
    string mode;
    cout << "Select mode (custom or demo): ";
    cin >> mode;
    transform(mode.begin(), mode.end(), mode.begin(), ::tolower);
    
    if(mode == "custom" || mode == "c") { // If mode is "custom" or "c", custom mode selected
        string input;

        while(input != "quit" && input != "q") {
            // Get the x value from the user
            int x;
            cout << "Enter value for x: ";
            cin >> input;
            if(input == "quit" || input == "q") {
                break;
            } else {
                x = stoi(input);
            }

            // Get the y value from the user
            int y;
            cout << "Enter value for y: ";
            cin >> input;
            if(input == "quit" || input == "q") {
                break;
            } else {
                y = stoi(input);
            }

            // Get the z value from the user
            int z;
            cout << "Enter value for z: ";
            cin >> input;
            if(input == "quit" || input == "q") {
                break;
            } else {
                z = stoi(input);
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
    } else { // If mode matchest none of the above, print and return error
        cout << "Invalid mode: " << mode;
        return -1;
    }

    return 0;
}