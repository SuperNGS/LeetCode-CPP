#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <set>
#include <sstream>
# include <limits>

// Custom utilities header
#include <utilities.h>

// Use standard namespace
using namespace std;

class Solution {
public:
    long long minOperations(vector<vector<int>>& queries) {
        // Setup a tracker for the running count of operations
        long long count = 0;

        // Loop through each query
        for(int i = 0; i < queries.size(); i++) {
            // Calculate the minOps to get the L value to 0
            long long minOps = log(queries[i][0]) / log(4) + 1;

            // Calculate the current power of 4
            long long stepper = pow(4, minOps);

            // Track the minOps from L to R needed to get to zero
            long long count2 = (queries[i][1] - queries[i][0] + 1) * minOps;

            // While stepper is less than or equal to the R value, iteratively calculate minOps for the next power of 4
            while(stepper <= queries[i][1]) {
                count2 += queries[i][1] - stepper + 1;
                stepper *= 4;
            }
            
            // Increment the counter by the ceiling of count2 / 2
            count += (count2 + 1) / 2;
        }
        // Return the count of operations
        return count;
    }
};

int main() {
    printStartBanner("3495. Minimum Operations to Make Array Elements Zero", "O(n log r)", "O(1)");
    
    // Initialize solution
    Solution s;

    // Get the mode to run program in from the user
    string mode = selectMode();

    if(isCustomMode(mode)) { // Custom mode selected, run with user input
        customModeSelected();

        // Create a 2D vector to hold user-entered pairs
        vector<vector<int>> pairs;

        // Initialize a holder for user input and loop
        string input;
        while(true) {
            // Get comma-seperated value pair from user
            cout << "Enter comma-separated pair of values to use or press enter to exit entries: ";
            getline(cin, input);
            toLowercase(input);

            if(isQuitMode(mode)) { // If quit entered, exit program
                return quitModeSelected();
            } else if(input.empty() || isExitMode(input)) { // If blank or exit entered, break loop
                exitModeSelected();
                break;
            }

            // Tokenize input and push onto pair int vector
            vector<int> pair;
            stringstream ss(input);
            string token;
            while(getline(ss, token, ',')) {
                try { // Attempt to convert each token to an integer and add to pair vector
                    pair.push_back(stoi(token));
                } catch(...) { // If conversion fails, print error and skip token
                    cout << "Invalid input: " << token << ". Please enter only integers. Skipping..." << endl;
                    break;
                }
            }

            if(pair.size() != 2) { // If pair does not contain exactly 2 integers, print error and continue loop
                cout << "ERROR: Please enter exactly two integers separated by a comma. Skipping..." << endl;
                continue;
            }

            // Push pair onto pairs 2D vector
            pairs.push_back(pair);
        }

        // Loop over and print all entered pairs
        cout << "Entered pairs:" << endl;
        for(const auto& pair : pairs) {
            cout << "\t[" << pair[0] << ", " << pair[1] << "]" << endl;
        }

        // Calculate and print out results
        cout << "Minimum operations to make array elements zero: " << s.minOperations(pairs) << endl;
    } else if(isDemoMode(mode)) { // Demo mode selected, run with demo data
        demoModeSelected();

        // Initialize 3D vector of demo data
        vector<vector<vector<int>>> demoData =  {
                                                    {
                                                        {1, 2},
                                                        {2, 4}
                                                    },
                                                    {
                                                        {2,6}
                                                    },
                                                    {
                                                        {855407150,876255590},
                                                        {967587865,990508908},
                                                        {730921172,766957042},
                                                        {132328523,582511466},
                                                        {52528451,342405685},
                                                        {960740165,993940388},
                                                        {295357365,972582056},
                                                        {301584043,674638635},
                                                        {22333241,50052834},
                                                        {172608385,644729129},
                                                        {571351581,610870532},
                                                        {866228725,927947734},
                                                        {543159135,986992629},
                                                        {510683126,726679179},
                                                        {43863970,292628606},
                                                        {841928053,874430013},
                                                        {382358163,977381025},
                                                        {948485147,956231401},
                                                        {968526821,972910650},
                                                        {100363133,120219835}
                                                    }
                                                };
        
        // Loop over each test case, print it out, then calculate and print minOperations()
        for(vector<vector<int>> data : demoData) {
            cout << "Running with test case:" << endl;
            for(const auto& d : data) {
                cout << "\t[" << d[0] << ", " << d[1] << "]" << endl;
            }
            cout << "Minimum operations to make array elements zero: " << s.minOperations(data) << endl;
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // Quit mode selected, exit program
        return quitModeSelected();
    } else { // Else, invalid mode. Error
        return unknownModeSelected(mode);
    }

    // Exit program
    return 0;
}