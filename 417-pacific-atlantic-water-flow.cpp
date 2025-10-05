#include <vector>
#include <queue>
#include <sstream>

// Custom utilities header
#include <utilities.h>

// Use standard namespace
using namespace std;

class Solution {
private:
    // Define a struct to represent a cell's coordinates
    struct Cell {
        int row;
        int col;
    };
    // Valid directions to search in from a given cell
    vector<vector<int>> directions = {{0,1}, {0, -1}, {1, 0}, {-1, 0}};
    /**
     * Given a row and column, checks if the cell is within the bounds of heights,
     * hasn't been visited yet, and has a height greater than the parent cell (allows for runoff)
     */
    bool isValid(const vector<vector<int>>& heights, const vector<vector<bool>>& visited, int row, int col, int height) {
        int rows = heights.size();
        int cols = heights[0].size();
        return (row >= 0 && row < rows && col >= 0 && col < cols && !visited[row][col] && heights[row][col] >= height);
    }
    /**
     * Implementation of breadth-first search for finding cells connected to the ocean
     */
    void bfs(vector<vector<int>>& heights, vector<vector<bool>>& visited, int row, int col) {
        // Initialize a queue of cells and push the starter cell onto it
        queue<Cell> cells;
        cells.push({row, col});

        // Mark the cell as visited
        visited[row][col] = true;

        // While there are cells in the queue, loop
        while(!cells.empty()) {
            // Get and pop the first cell
            Cell current = cells.front();
            cells.pop();

            // Get the height of the cell
            int height = heights[current.row][current.col];

            // Loop through all possible directions to calculate adjacent cells
            for(const auto& direction : directions) {
                // Calculate the row and column of the neighboring cell
                int next_row = current.row + direction[0], next_col = current.col + direction[1];

                // If cell is valid, mark it as visited and push it onto the queue
                if (isValid(heights, visited, next_row, next_col, height)) {
                    visited[next_row][next_col] = true;
                    cells.push({next_row, next_col});
                }
            }
        }
    }
    /**
     * Implementation of depth-first search for finding cells connected to the ocean
     */
    void dfs(vector<vector<int>>& heights, vector<vector<bool>>& visited, int row, int col, int height) {
        // If cell is not valid, end recursion
        if(!isValid(heights, visited, row, col, height)) {
            return;
        }

        // Mark the cell as visited
        visited[row][col] = true;

        // For each valid direction, recursively call DFS with neighboring cell
        for(const auto& direction : directions) {
            // Calculate the row and column of the neighboring cell to search
            int next_row = row + direction[0], next_col = col + direction[1];
            // Recursively call DFS on the neighboring cell
            dfs(heights, visited, next_row, next_col, heights[row][col]);
        }
    }
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        // Get the rows and columns of the heights 2D vector
        int rows = heights.size(), cols = heights[0].size();

        // Initialize 2D visited vector of booleans for DFS corresponding to cells in heights connecting to pacific
        vector<vector<bool>> visitedPacific(rows, vector<bool>(cols, false));

        // Loop through all cells in the top row and call dfs
        for(int row = 0; row < rows; row++) {
            dfs(heights, visitedPacific, row, 0, heights[row][0]);
        }
        // Loop through all cells in the left column and call dfs
        for(int col = 0; col < cols; col++) {
            dfs(heights, visitedPacific, 0, col, heights[0][col]);
        }

        // Initialize 2D visited vector of booleans for BFS corresponding to cells in heights connecting to Atlantic
        vector<vector<bool>> visitedAtlantic(rows, vector<bool>(cols, false));

        // Loop through all cells in the bottom row
        for(int row = rows - 1; row >= 0; row--) {
            bfs(heights, visitedAtlantic, row, cols - 1);
        }
        // Loop through all cells in the right column
        for(int col = cols - 1; col >= 0; col--) {
            bfs(heights, visitedAtlantic, rows - 1, col);
        }

        // Initialize vector to store answer
        vector<vector<int>> answer;

        // Loop through all cells of the visited 2D vectors, adding the cell to answer if
        // it's been visited in both
        for(int r = 0; r < rows; r++) {
            for(int c = 0; c < cols; c++) {
                if(visitedPacific[r][c] && visitedAtlantic[r][c]) {
                    answer.push_back({r, c});
                }
            }
        }

        // Return the answer
        return answer;
    }
};

int main() {
    printStartBanner("417. Pacific Atlantic Water Flow", "O(m * n)", "O(m * n)");

    // Initialize solution
    Solution s;

    // Prompt user to select mode
    string mode = selectMode();

    if(isCustomMode(mode)) { // If mode is custom, run program with user input
        customModeSelected();

        // Initialize input string and loop
        string input;
        while(true) {
            // Initialize a 2D vector of height values
            vector<vector<int>> heights;
            while(true) {
                cout << "Enter row of height values as a comma-separated string or press enter to exit entries: ";
                getline(cin, input);
                toLowercase(input);

                if(isExitMode(input)) { // If exit mode selected, exit loop
                    exitModeSelected();
                    break;
                } else if(isQuitMode(input)) { // If quit mode selected, exit program
                    return quitModeSelected();
                }

                // Attempt to tokenize input into a vector of ints
                vector<int> values;
                stringstream ss(input);
                string token;
                while(getline(ss, token, ',')) {
                    try { // Attempt to convert token to int and push back onto values
                        values.push_back(stoi(token));
                    } catch(...) { // Catch invalid type and skip
                        cout << "ERROR: Invalid input '" << token << "'. Skipping..." << endl;
                        continue;
                    }
                }

                if(values.empty()) { // If no valid values entered, skip
                    cout << "No values entered. Skipping..." << endl;
                    continue;
                } else if(!heights.empty() && values.size() != heights[0].size()) { // If row is not the appropriate size for the matrix, skip
                    cout << "ERROR: Invalid length of input. Row requires " << heights[0].size() << " values, but " << values.size() << " were provided. Skipping..." << endl;
                    continue;
                }

                // Push values back onto heights
                heights.push_back(values);
            }

            // Print values
            cout << "Running program with values:" << endl;
            for(const auto& values : heights) {
                cout << "\t[ ";
                for(const auto& val : values) {
                    cout << val << " ";
                }
                cout << "]" << endl;
            }

            // Calculate the result
            vector<vector<int>> result = s.pacificAtlantic(heights);

            // Print the result
            cout << "Cells that connect to both the Atlantic and Pacific:" << endl;
            for(const auto& cell : result) {
                cout << "\t[" << cell[0] << ", " << cell[1] << "]" << endl;
            }
        }
    } else if(isDemoMode(mode)) { // If mode is demo, run program with demo data
        demoModeSelected();

        // Initialize 3D vector of demo data
        vector<vector<vector<int>>> demoData = {
            {
                {1,2,2,3,5},
                {3,2,3,4,4},
                {2,4,5,3,1},
                {6,7,1,4,5},
                {5,1,1,2,4}
            },
            {
                {1}
            }
        };

        // Loop through demoData, print out the values, then calculate and print out the resulting array
        for(vector<vector<int>> data : demoData) {
            cout << "Running program with values:" << endl;
            for(const auto& values : data) {
                cout << "\t[ ";
                for(const auto& val : values) {
                    cout << val << " ";
                }
                cout<< "]" << endl;
            }

            // Calculate the resulting vector
            vector<vector<int>> result = s.pacificAtlantic(data);

            // Print the resulting vector
            cout << "Cells that connect to both the Atlantic and Pacific:" << endl;
            for(const auto& cell : result) {
                cout << "\t[" << cell[0] << ", " << cell[1] << "]" << endl;
            }
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // If mode is exit or quit, exit the program
        return quitModeSelected();
    } else { // Else, unknown mode selected, error
        return unknownModeSelected(mode);
    }

    // Exit program successfully
    return 0;
}