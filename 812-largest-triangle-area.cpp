# include <vector>
# include <algorithm>
# include <limits>
# include <sstream>

// Custom header utilities
# include <utilities.h>

// Use std namespace
using namespace std;

class Solution {
public:
    double largestTriangleArea(vector<vector<int>>& points) {
        // Initialize tracker for highest area
        double highest_area;
        // Initialize max bound of vector
        int n = points.size();

        // Loop through all combinations of points i, j, and k
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                for(int k = 0; k < n; k++) {
                    // Break points i, j, and k into x-y coordinates
                    int x1 = points[i][0], y1 = points[i][1];
                    int x2 = points[j][0], y2 = points[j][1];
                    int x3 = points[k][0], y3 = points[k][1];

                    // Solve for area using shoelace formula
                    double area = 0.5 * (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));

                    // Compare area to highestArea and update if needed
                    highest_area = max(highest_area, area);
                }
            }
        }

        // Return the highest area
        return highest_area;
    }
};

int main() {
    // Print the start banner
    printStartBanner("812. Largest Triangle Area", "O(n^3)", "O(1)");

    // Initialize solution
    Solution s;

    // Get mode to run program in from user
    string mode = selectMode();

    if(customMode.find(mode) != customMode.end()) { // Custom mode selected, run with user input
        customModeSelected();

        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Create a holder for user input, a 2D vector for entered pairs, and loop
        string input;
        vector<vector<int>> pairs;
        while(true) {
            // Get the comma-seperated pair from user input, lowercase input to check against modes
            cout << "Enter a pair of coordinates as a comma-seperated string or press enter to exit entries: ";
            getline(cin, input);
            toLowercase(input);
            
            if(input.empty() || exitMode.find(input) != exitMode.end()) { // Exit loop if blank line or exit entered
                break;
            } else if(quitMode.find(input) != quitMode.end()) { // Quit program if quit entered
                quitModeSelected();
            }

            // Parse the inputted string for inputted pair
            vector<int> pair;
            stringstream ss(input);
            string token;
            while(getline(ss, token, ',')) {
                try { // Attempt to convert the value to an int and push back onto pair
                    pair.push_back(stoi(token));
                } catch (const std::invalid_argument& e) { // Entered value was not a number
                    cout << "Invalid value " << token << " is not an int, skipping" << endl;
                } catch (const std::out_of_range& e) { // Value is out of range for an int
                    cout << "Invalid value " << token << " is out of range for an int, skipping" << endl;
                }
            }

            if(pair.size() < 2) { // Handle too few values (skip pair entry)
                cout << "Error: ";
                for(const auto& val : pair) {
                    cout << val << " ";
                }
                cout << "is not a valid pair, skipping..." << endl;
            } else if(pair.size() > 2) { // Handle too many values (add first two values to pairs)
                cout << "Warning: More than two values entered. Will use only first two values " << pair[0] << " and " << pair[1] << endl;
                pairs.push_back({pair[0], pair[1]});
            } else { // Two values enterd, add to pairs
                pairs.push_back(pair);
            }
        }

        // Print out the entered pairs
        cout << "Entered pairs:" << endl;
        for(const auto& pair : pairs) {
            cout << "\t[" << pair[0] << ", " << pair[1] << "]" << endl;
        }

        // If too few points have been entered to make a triangle, error
        if(pairs.size() < 3) {
            cout << "Error: Too few points have been entered to make a triangle" << endl;
            return -1;
        }

        // Calculate and print the largest triangle area
        cout << "Largest triangle area: " << s.largestTriangleArea(pairs) << endl;

    } else if(demoMode.find(mode) != demoMode.end()) { // Demo mode selected, run with demo data
        demoModeSelected();

        // Initialize 3D vector of demo data to run program with
        vector<vector<vector<int>>> demoData = {
            {
                {0,0}, {0,1}, {1,0}, {0,2}, {2,0}
            },
            {
                {1, 0}, {0, 0}, {0, 1}
            }
        };

        // Loop through each set of points, print the points, then calculate and print largest triangle area
        for(vector<vector<int>> points : demoData) {
            // Print the points
            cout << "Points:" << endl;
            for(const auto& point : points) {
                cout << "\t[" << point[0] << ", " << point[1] << "]" << endl;
            }

            // Calculate and print largest triangle area
            cout << "Largest triangle area: " << s.largestTriangleArea(points) << endl;;
        }
    } else if(quitMode.find(mode) != quitMode.end()) { // Quit mode selected, exit program
        return quitModeSelected();
    } else { // Else, unknown mode selected. Error
        return unknownModeSelected(mode);
    }

    // Exit program
    return 0;
}