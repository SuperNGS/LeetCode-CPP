#include <cstdlib>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>

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
    cout << "Triangle Demo" << endl << endl;

    Solution s = Solution();
    
    // Prompt the user to select a mode([c]ustom, [d]emo, [q]uit)
    string mode;
    cout << "Select mode ([c]ustom, [d]emo, or [q]uit): ";
    cin >> mode;

    transform(mode.begin(), mode.end(), mode.begin(), ::tolower);

    if(mode == "custom" || mode == "c") { // If mode 'custom' or 'c' selected, run program with user input
        cout << "Custom mode selected" << endl;

        // Create a holder variable for user input
        string input;

        // While user has not entered "quit" or "q", loop
        while(true) {
            // Create a 2D vector to hold the triangle
            vector<vector<int>> triangle;

            // Incrementer for row number
            int i = 1;

            // While user has entered 'e' for exit, loop
            while(true) {
                // Get the comma-separated string representing a row from the user
                cout << "Enter values for row " << i << " as a comma-seperated string (enter 'e' to exit): ";
                cin >> input;
                transform(input.begin(), input.end(), input.begin(), ::tolower);

                if(input == "e") { // If input was 'e', break
                    break;
                } else if(input == "quit" || input == "q") { // If input was 'quit' or 'q', exit program
                    cout << "Quitting..." << endl;
                    return 0;
                }

                // Break the comma-separated string into a vector of ints
                vector<int> row;
                stringstream ss(input);
                string token;
                cout << "Row " << i << ": ";
                while(getline(ss, token, ',')) {
                    cout << token << " ";
                    row.push_back(stoi(token));
                }
                cout << endl;

                // Add the row vector to the triangle and increment the row number
                triangle.push_back(row);
                i++;
            }
            
            // Calculate and print the shortest path
            cout << "Shortest path is: " << s.minimumTotal(triangle) << endl;
        }
    } else if(mode == "demo" || mode == "d") { // If mode 'demo' or 'd' selected, run program with demo data
        cout << "Demo mode selected" << endl;
        // Create a 3D vector of ints to represent the demo triangles
        vector<vector<vector<int>>> triangles = {{{1}, {2, 3}, {4, 5, 6}}, {{3}, {-7, -1}, {8, 9, -10}}, {{-10}, {7, 1}, {8, 9, 13}}};

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

    } else if(mode == "quit" || mode == "q") { // If mode 'quit' or 'q' selected, exit program
        cout << "Quitting..." << endl;
        return 0;
    } else { // Else invalid mode, error
        cout << "Invalid mode: " << mode << endl;
        return -1;
    }
    // Exit program
    return 0;
}