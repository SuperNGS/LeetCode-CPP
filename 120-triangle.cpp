#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <limits>

// Custom utilities header
#include <utilities.h>

// Use std namespace
using namespace std;

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        // Loop through the rows, from the second to last row and up
        for(int i = triangle.size() - 2; i >= 0; --i) {
            // Loop through the columns, from zero and up
            for(int j = 0; j < triangle[i].size(); ++j) {
                // Recompute the value of triangle[i][j] to the smallest path
                triangle[i][j] += min(triangle[i+1][j], triangle[i+1][j+1]);
            }
        }
        // Return triangle[0][0], where the answer is stored
        return triangle[0][0];
    }
};

int main() {
    printStartBanner("120. Triangle", "O(n^2)", "O(1)");

    // Initialize solution
    Solution s;
    
    // Get the mode to run in from the user
    string mode = selectMode();

    if(isCustomMode(mode)) { // If custom mode selected, run program with user input
        customModeSelected();

        // Create a holder variable for user input and loop until user quits or exits
        string input;

        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // While user has not entered quit or exit, loop
        while(true) {
            // Create a 2D vector to hold the triangle
            vector<vector<int>> triangle;

            // Incrementer for row number
            int i = 1;

            // While user hasnt entered exit or quit, loop
            while(true) {
                // Get the comma-separated string representing a row from the user
                cout << "Enter values for row " << i << " as a comma-seperated string or press enter to exit: ";
                getline(cin, input);
                toLowercase(input);

                if(isExitMode(input) || input.empty()) { // If input was exit, break
                    break;
                } else if(isQuitMode(input)) { // If input was quit exit program
                    return quitModeSelected();
                }

                // Break the comma-separated string into a vector of ints
                vector<int> row;
                stringstream ss(input);
                string token;
                cout << "Row #" << i << ": ";
                while(getline(ss, token, ',')) {
                    cout << token << " ";
                    row.push_back(stoi(token));
                }
                cout << endl;

                // If the row size is not equal to the row number, error and break
                if(row.size() != i) {
                    cout << "Error: Row " << i << " must have " << i << " values" << endl;
                    break;
                }

                // Add the row vector to the triangle and increment the row number
                triangle.push_back(row);
                i++;
            }

            if(triangle.size() == 0) { // If triangle is empty, break
                cout << "No triangle entered, exiting" << endl;
                break;
            }
            
            // Calculate and print the shortest path
            cout << "Shortest path is: " << s.minimumTotal(triangle) << endl;
        }
    } else if(mode == "demo" || mode == "d") { // If mode 'demo' or 'd' selected, run program with demo data
        demoModeSelected();

        // Create a 3D vector of ints to represent the demo triangles
        vector<vector<vector<int>>> triangles = {
            {
                {1}, {2, 3}, {4, 5, 6}
            },
            {
                {3}, {-7, -1}, {8, 9, -10}
            },
            {
                {-10}, {7, 1}, {8, 9, 13}
            }
        };

        // Loop through each triangle
        for(int i = 0; i < triangles.size(); i++) {
            // Assign triangle to vector<vector<int>> for readability
            vector<vector<int>> triangle = triangles[i];

            // Loop through and print out the triangles row and columns
            cout << "For triangle with" << endl;
            for(int j = 0; j < triangle.size(); j++) {
                cout << "Row " << j << ": ";
                for(const auto& col : triangle[j]) {
                    cout << col << " ";
                }
                cout << endl;
            }

            // Calculate and print out the shortest path
            cout << "The shortest path is " << s.minimumTotal(triangle) << endl << endl;
        }

    } else if(isQuitMode(mode)) { // If quit mode selected, exit program
        return quitModeSelected();
    } else { // Else invalid mode, error
        return unknownModeSelected(mode);
    }

    // Exit program
    return 0;
}