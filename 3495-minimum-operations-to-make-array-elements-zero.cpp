#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <set>
#include <sstream>

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
    cout << "Minimum Operations to Make Array Elements Zero Demo" << endl << endl;
    
    // Get the mode to run program in from the user
    string mode;
    cout << "Select mode ([c]ustom, [d]emo, or [q]uit): ";
    cin >> mode;
    transform(mode.begin(), mode.end(), mode.begin(), ::tolower);

    // Create sets for matching the different modes
    set<string> customMode = {"custom", "[c]ustom", "c", "[c]"};
    set<string> demoMode = {"demo", "[d]emo", "d", "[d]"};
    set<string> quitMode = {"quit", "[q]uit", "q", "[q]"};

    // Initialize solution
    Solution s = Solution();

    if(customMode.find(mode) != customMode.end()) { // Custom mode selected, run with user input
        cout << "Custom mode selected" << endl;

        // Create set to handle exit command
        set<string> exitMode = {"exit", "[e]xit", "e", "[e]"};

        // Create a 2D vector to hold user-entered pairs
        vector<vector<int>> pairs;

        // Initialize a holder for user input and loop
        string input;
        while(true) {
            // Get comma-seperated value pair from user
            cout << "Enter comma-separated pair of values to use or [e]xit to stop entries: ";
            cin >> input;
            transform(input.begin(), input.end(), input.begin(), ::tolower);

            if(quitMode.find(input) != quitMode.end()) { // If quit entered, exit program
                cout << "Quitting..." << endl;
                return 0;
            } else if(exitMode.find(input) != exitMode.end()) { // If exit entered, break loop
                break;
            }

            // Tokenize input and push onto pair int vector
            vector<int> pair;
            stringstream ss(input);
            string token;
            while(getline(ss, token, ',')) {
                pair.push_back(stoi(token));
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
    } else if(demoMode.find(mode) != demoMode.end()) { // Demo mode selected, run with demo data
        cout << "Demo mode selected" << endl;

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
    } else if(quitMode.find(mode) != quitMode.end()) { // Quit mode selected, exit program
        cout << "Quitting..." << endl;
        return 0;
    } else { // Else, invalid mode. Error
        cout << "Invalid mode: " << mode << endl;
        return -1;
    }
    return 0;
}