#include <climits>
#include <vector>
#include <algorithm>
#include <sstream>

// Custom utilities header
#include <utilities.h>

// Use std namespace
using namespace std;

class Solution {
public:
    int numberOfPairs(vector<vector<int>>& points) {
        //Sort the points by non-decreasing x, break ties by sorting by non-increasing y
        sort(points.begin(),points.end(),[](const vector<int> &m,const vector<int> &n){
            if(m[0] != n[0]) return m[0] < n[0];
            return m[1] > n[1];
        });

        // Loop through all points, track valid pairs
        int count = 0;
        for(int i=0; i < points.size(); i++){
            // Set a temporary value to track greatest Y value found
            int temp = INT_MIN;
            for(int j=i+1;j<points.size();j++){
                // If the Y coordinate for pointA is greater or equal to the Y of PointB
                // and the Y of pointB is greater than temp, increment and track new Y
                if(points[i][1] >= points[j][1] && points[j][1] > temp){
                    count++;
                    temp = points[j][1];
                }
            }
        }
        // Return the count
        return count;
    }
};

int main() {
    printStartBanner("3027. Find the Number of Ways to Place People II", "O(n^2)", "O(log n)");

    // Initialize the solution
    Solution s;

    // Prompt user to select mode
    string mode = selectMode();

    if(isCustomMode(mode)) { // Custom mode selected, run with user input
        customModeSelected();

        // Initialize input string and start loop
        string input;
        while(true) {
            // Holder of user-entered coordinate pairs
            vector<vector<int>> pairs;

            // Loop to enter coordinates
            while(true) {
                cout << "Enter coordinate pair as a comma-separated string (x,y) or press enter to exit entries: ";
                getline(cin, input);
                toLowercase(input);

                if(isExitMode(input)) { // Exit mode selected, break loop
                    exitModeSelected();
                    break;
                } else if(isQuitMode(input)) { // Quit mode selected, exit program
                    return quitModeSelected();
                }

                // Create an int vector to hold the pair and attempt to tokenize input into it
                vector<int> pair;
                stringstream ss(input);
                string token;
                while(getline(ss, token, ',')) {
                    try{ // Try to convert the token to an int and push back onto pair
                        pair.push_back(stoi(token));
                    } catch(...) { // Catch invalid type, error and skip
                        cout << "ERROR: Invalid input '" << token << "'. Please only enter two comma-separated integers. Skipping..." << endl;
                        continue;
                    }
                }

                // If too few values entered, skip this run
                if(pair.size() < 2) {
                    cout << "ERROR: Not enough values entered to make a pair. Skipping..." << endl;
                    continue;
                }

                // Push pair back onto pairs
                pairs.push_back(pair);
            }

            // If no pairs entered, exit program
            if(pairs.empty()) {
                cout << "INFO: No pairs entered." << endl;
                return quitModeSelected();
            }

            // Print out pairs to run program with
            cout << "Running with pairs:" << endl;
            for(const auto& pair : pairs) {
                cout << "\t[" << pair[0] << ", " << pair[1] << "]" << endl;
            }

            // Calculate and print out number of valid pairs
            cout << "Number of valid pairs = " << s.numberOfPairs(pairs) << endl;

            // Clear the pairs
            pairs.clear();
        }
    } else if(isDemoMode(mode)) { // Demo mode selected, run with demo data
        demoModeSelected();

        // Create a 3D vector of demo data to run the program with
        vector<vector<vector<int>>> demoData = {
            {
                {1,1}, {2,2}, {3,3}
            },
            {
                {6,2}, {4,4}, {2,6}
            },
            {
                {3,1}, {1,3}, {1,1}
            }
        };

        // Loop through each set of demo data, print the values, then calculate and print numberOfPairs()
        for(vector<vector<int>> data : demoData) {
            cout << "Running with pairs:" << endl;
            for(const auto& values : data) {
                cout << "\t[" << values[0] << ", " << values[1] << "]" << endl;
            }
            cout << "Number of valid pairs = " << s.numberOfPairs(data) << endl;
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // Quit or exit mode selected, exit program
        return quitModeSelected();
    } else { // Else, unknown mode selected, error
        return unknownModeSelected(mode);
    }

    // Exit program successfully
    return 0;
}