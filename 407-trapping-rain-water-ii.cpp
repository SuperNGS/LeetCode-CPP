#include <vector>
#include <queue>

// Custom utilities header
#include <utilities.h>

// Use std namespace
using namespace std;

class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        // Get grid dimensions
        int rows = heightMap.size(), cols = (rows == 0) ? 0 : heightMap[0].size();        
        
        // If the grid is too small to trap any water (needs at least a 3x3 boundary), return 0
        if(rows < 3 || cols < 3) return 0;

        // Min-heap (priority queue) to store boundary cells sorted by height (smallest first)
        // Each element is: {height, {row, col}}
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

        // Visited matrix to mark which cells are already processed
        vector<vector<int>> visited(rows, vector<int>(cols, 0));

        // Add all boundary cells to the heap and mark them as visited
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                // Only process boundary cells (edges of the matrix)
                if(!(i == 0 || i == rows-1 || j == 0 || j == cols-1)) continue;

                pq.push(make_pair(heightMap[i][j], make_pair(i, j))); // Push height and coordinates
                visited[i][j] = 1; // Mark boundary as visited
            }
        }

        // Direction vector to explore 4-connected neighbors (up, right, down, left)
        vector<int> dir = {0, 1, 0, -1, 0};

        // Track the maximum height seen so far while processing (water will be trapped relative to this)
        int H = INT_MIN;

        // Variable to store the total amount of trapped water
        int res = 0;

        // Process the priority queue
        while(!pq.empty())
        {
            // Get the cell with the lowest current height
            auto p = pq.top(); pq.pop();
            int height = p.first, i = p.second.first, j = p.second.second;

            // Update max boundary height encountered so far
            H = max(H, height);

            // Explore all 4 neighboring cells
            for (int d = 0; d < 4; d++)
            {
                int x = i + dir[d], y = j + dir[d+1];

                // Skip if out of bounds or already visited
                if(x < 0 || x >= rows || y < 0 || y >= cols || visited[x][y]) continue;

                // Mark neighbor as visited
                visited[x][y] = 1;

                // If the neighbor is lower than current water boundary height, water can be trapped
                int diff = H - heightMap[x][y];
                if(diff > 0) res += diff;

                // Push the neighbor cell into the heap with its own height
                pq.push(make_pair(heightMap[x][y], make_pair(x, y)));
            }
        }

        // Return total accumulated trapped water
        return res;
    } 
};

int main() {
    printStartBanner("407. Trapping Rain Water II", "O(r * c * log(r * c))", "O(r * c)");

    // Initialize the solution
    Solution s;

    // Get mode to run program in from user
    string mode = selectMode();

    if(isCustomMode(mode)) { // If custom mode selected, run with user input
        customModeSelected();

        // Initialize input string, 2D int vector heights, and loop
        string input;
        vector<vector<int>> heights;
        while(true) {
            // Get the next row of heights grid or break loop
            cout << "Enter a row of the heights grid or press enter to stop entries: ";
            getline(cin, input);
            toLowercase(input);

            if(isExitMode(input)) { // If exit entered, break loop
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) { // If quit mode selected, exit program
                return quitModeSelected();
            }

            // Tokenize input string int int vector row
            vector<int> row = stringToIntVector(input);

            // If row empty, skip
            if(row.empty()) {
                cout << "INFO: No values entered for row. Skipping..." << endl;
                continue;
            }

            // If row does not match grid dimensions, error and skip
            if(!heights.empty() && row.size() != heights[0].size()) {
                cout << "ERROR: Row length does not match dimensions of grid. Needs " << heights[0].size() << " values, but " << row.size() << " provided. Skipping..." << endl;
                continue;
            }

            // Add the row to heights grid
            heights.push_back(row);
        }

        // if heights is not empty, print the grid, then calcualate and print the result
        if(!heights.empty()) {
            // Print the grid
            cout << "Running program with heights grid:" << endl;
            for(vector<int>& row : heights) {
                cout << "\t";
                for(int& cell : row) {
                    cout << cell << " ";
                }
                cout << endl;
            }

            // Calculate and print the result
            cout << "Total volume of water trapped is " << s.trapRainWater(heights) << endl;
        }
    } else if(isDemoMode(mode)) { // If demo mode selected, run with demo data
        demoModeSelected();

        // Initialize 3D int vector demoHieghts to act as sets of grid cell heights
        vector<vector<vector<int>>> demoHeights = {
            {
                {1,4,3,1,3,2},
                {3,2,1,3,2,4},
                {2,3,3,2,3,1}
            },
            {
                {3,3,3,3,3},
                {3,2,2,2,3},
                {3,2,1,2,3},
                {3,2,2,2,3},
                {3,3,3,3,3}
            }
        };

        // Loop through demoHeights, print the grid, then calculate and print the result
        for(vector<vector<int>>& heights : demoHeights) {
            // Print the heights grid
            cout << "Running program with heights grid:" << endl;
            for(vector<int>& row : heights) {
                cout << "\t";
                for(int& cell : row) {
                    cout << cell << " ";
                }
                cout << endl;
            }

            // Calculate and print the result
            cout << "Total volume of water trapped is " << s.trapRainWater(heights) << endl;
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // If exit or quit mode selected, exit program
        return quitModeSelected();
    } else { // Else, unknown mode selected, error
        return unknownModeSelected(mode);
    }

    // Exit program successfully
    return 0;
}
