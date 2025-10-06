#include <vector>
#include <queue>
#include <sstream>

// Custom utilities header
#include <utilities.h>

// Use standard namespace
using namespace std;

class Solution {
private:
    // Custom struct denoting a cell in the grid
    struct Cell {
        int height;
        int row;
        int col;
        bool operator()(Cell a, Cell b) const {
            return a.height > b.height; 
        }
    };
    // 2D vector of valid directional movements
    vector<vector<int>> directions = {{0,1}, {0,-1}, {1,0}, {-1,0}};
public:
    int swimInWater(vector<vector<int>>& grid) {
        // Initialize highest to 0
        int highest = 0;

        // Create a min priority queue and push the first cell
        priority_queue<Cell, vector<Cell>, Cell> min_pq;
        min_pq.push({grid[0][0], 0, 0});

        // Create a 2D vector of visited cells
        vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));

        // Loop through the priority queue until it's empty or we hit the target cell
        while(!min_pq.empty()) {
            // Get the highest priority cell and pop it from the queue
            Cell cell = min_pq.top();
            min_pq.pop();

            // Mark the cell as visited
            visited[cell.row][cell.col] = true;

            // If new max height, update highest
            if(highest < cell.height) {
                highest = cell.height;
            }

            // If cell is target cell (grid[grid.size()-1][grid[0].size()-1]), stop iterating
            if(cell.row == grid.size() - 1 && cell.col == grid[0].size() - 1) {
                break;
            }

            // For each possible movement direction, evaluate if the cell is valid.
            // If it is, push it onto the priority queue
            for(const auto& direction : directions) {
                // Get the new row and column
                int row = cell.row + direction[0], col = cell.col + direction[1];

                // If row and column within grid dimensions and cell is not visited, add it to priority queue
                if(
                    row >= 0 && row < grid.size() &&
                    col >= 0 && col < grid[0].size() &&
                    !visited[row][col]
                ) {
                    min_pq.push({grid[row][col], row, col});
                }
            }
        }

        // Return the highest elevation found on the path
        return highest;
    }
};

int main() {
    printStartBanner("778. Swim in Rising Water", "O(m*n log m*n)", "O(m*n)");

    // Initialize solution
    Solution s;

    // Prompt user to select mode
    string mode = selectMode();

    if(isCustomMode(mode)) { // If custom mode, run program with user input
        customModeSelected();

        // Initialize holder for user input, 2D vector of heights, and loop
        string input;
        vector<vector<int>> grid;
        while(true) {
            cout << "Enter height values for row as a comma-separated string or press enter to stop entries: ";
            getline(cin, input);
            toLowercase(input);

            if(isExitMode(input)) { // If exit mode, exit loop
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) { // If quit mode, exit program
                return quitModeSelected();
            }

            // Attempt to tokenize the input into int vector row
            vector<int> row;
            stringstream ss(input);
            string token;
            while(getline(ss, token, ',')) {
                try { // Try to convert token to an int and push back onto row
                    row.push_back(stoi(token));
                } catch(...) { // Catch invalid input type, error and skip
                    cout << "ERROR: Invalid input '" << token << "'. Please only enter integers. Skipping..." << endl;
                    continue;
                }
            }

            // If row is empty, error and skip
            if(row.empty()) {
                cout << "ERROR: No values entered for row. Skipping..." << endl;
                continue;
            }

            // If row has values that don't match dimensions of grid, error and skip
            if(!grid.empty() && grid[0].size() != row.size()) {
                cout << "ERROR: Row does not match dimensions of grid (" << row.size() << " values provided, " << grid[0].size() << " required). Skipping..." << endl;
                continue;
            }

            // Push the row back onto grid
            grid.push_back(row);
        }

        // Print out grid
        cout << "Running solution with values:" << endl;
        for(const auto& cells : grid) {
            cout << "\t[ ";
            for(const auto& cell : cells) {
                cout << cell << " ";
            }
            cout << "]" << endl;
        }

        // Calculate and print out result
        cout << "Minimum time to get from (0, 0) to (n-1, n-1) is " << s.swimInWater(grid) << endl;
    } else if(isDemoMode(mode)) { // If demo mode, run program with demo data
        demoModeSelected();

        // Initialize a 3D int vector of demo heights
        vector<vector<vector<int>>> demoGrid = {
            {
                {0,2}, {1,3}
            },
            {
                {0,1,2,3,4}, {24,23,22,21,5}, {12,13,14,15,16}, {11,17,18,19,20}, {10,9,8,7,6}
            }
        };

        // Loop through each set of demo cells, print, and calculate result
        for(vector<vector<int>> cells : demoGrid) {
            cout << "Running program with values: " << endl;
            for(const auto& cell : cells) {
                cout << "\t[ ";
                for(const auto& val : cell) {
                    cout << val << " ";
                }
                cout << "]" << endl;
            }

            // Calculate and print the minimum time to traverse the grid
            cout << "Minimum time to get from (0, 0) to (n-1, n-1) is " << s.swimInWater(cells) << endl;
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // If quit or exit mode, exit program
        return quitModeSelected();
    } else { // Else, unknown mode selected. Error
        return unknownModeSelected(mode);
    }

    // Successfully exit the program
    return 0;
}