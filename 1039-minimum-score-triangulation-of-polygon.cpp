#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <limits>

// Custom utilities header
#include <utilities.h>

// Use standard namespace
using namespace std;
class Solution {
private:
    /**
     * Calculate the minimum score triangulation for the polygon defined by values between index i and n.
     * Uses Matrix Chain Multiplication (MCM) and memorization to store previously calculated results for subproblems.
     */
    int calculateMinimum(vector<int>& values, int i, int n, vector<vector<int>>& memorization) {
        // If only two points, no triangle can be formed, return 0
        if(i + 1 == n) {
            return 0;
        }

        // If result already calculated for this subproblem, return it
        if(memorization[i][n]) {
            return memorization[i][n];
        }

        // Initialize result to maximum integer value
        int result = INT_MAX;

        // Loop through all possible third points to form a triangle with points i and n
        for(int k = i + 1; k < n; k++) {
            // Calculate the score for the triangle formed by points i, k, and n, plus the minimum scores for the two resulting subproblems
            int current = calculateMinimum(values, i, k, memorization) + calculateMinimum(values, k, n, memorization) + (values[i] * values[k] * values[n]);

            // Update result if current score is lower
            result = min(current, result);
        }

        // Store the result for this subproblem in the memorization table
        memorization[i][n] = result;

        // Return the minimum score found for this subproblem
        return result;
    }
public:

    int minScoreTriangulation(vector<int>& values) {
        // Get the starting number of points in the polygon
        int n = values.size();
        // Initialize a 2D vector for memorization of size n*n, filled with zeros
        vector<vector<int>> memorization(n, vector<int>(n));

        // Start the calculation for the full polygon from point 0 to point n-1
        return calculateMinimum(values, 0, n - 1, memorization);
    }
};

int main() {
    printStartBanner("1039. Minimum Score Triangulation of Polygon", "O(n^3)", "O(n^2)");

    // Initialize the solution
    Solution s;

    // Get mode to run in from user (custom, demo, or quit)
    string mode = selectMode();

    if(isCustomMode(mode)) { // If custom mode selected, run solution with user input
        customModeSelected();

        // Create holder for input
        string input;

        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        // Loop until user breaks loop
        while(true) {
            // Get n value from user input
            cout << "Enter comma-seperated list of values or press enter to exit: ";
            getline(cin, input);
            toLowercase(input);

            if(input.empty() || isExitMode(input)) { // If no input entered or exit mode selected, break loop
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) { // If quit mode selected, exit program
                return quitModeSelected();
            }

            // Convert input string to vector of integers
            vector<int> values;
            stringstream ss(input);
            string token;
            while(getline(ss, token, ',')) {
                try { // Attempt to convert each token to an integer and add to values vector
                    values.push_back(stoi(token));
                } catch(...) { // If conversion fails, print error and skip token
                    cout << "Invalid input: " << token << ". Please enter only integers. Skipping..." << endl;
                    continue;
                }
            }

            // If less than 3 values entered, print error and continue loop
            if(values.size() < 3) { 
                cout << "ERROR: At least 3 values are required to form a polygon. Please try again." << endl;
                continue;
            }

            // Print the input values to console
            cout << "Running solution with values: ";
            for(const auto& value : values) {
                cout << value << " ";
            }
            cout << endl;

            // Get result from minScoreTriangulation and print result to console
            cout << "Result: " << s.minScoreTriangulation(values) << endl;
        }
    } else if(isDemoMode(mode)) { // If demo mode selected, run solution with demo data
        demoModeSelected();

        // Initialize 2D vector of demo data
        vector<vector<int>> demoData = {
            {1,2,3},
            {3,7,4,5},
            {1,3,1,4,1,5}
        };

        // Loop through each set of demo data
        for(vector<int> values : demoData) {
            // Print the values to console
            cout << "Running solution with values: ";
            for(const auto& value : values) {
                cout << value << " ";
            }
            cout << endl;

            // Get result of minScoreTriangulation and print to console
            cout << "Result: " << s.minScoreTriangulation(values) << endl;
        }
    } else if(isQuitMode(mode)) { // If quit mode selected, exit program
        return quitModeSelected();
    } else { // Else, unknown mode selected, print error and exit program
        return unknownModeSelected(mode);
    }

    // Exit program
    return 0;
}

