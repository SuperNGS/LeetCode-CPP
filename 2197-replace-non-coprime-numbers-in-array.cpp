#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <set>
#include <sstream>

using namespace std;

class Solution {
public:
    vector<int> replaceNonCoprimes(vector<int>& nums) {
        // Use a vector as a stack
        vector<int> stack;

        // Loop through all the values in nums
        for(int i = 0; i < nums.size(); i++) {

            // Push the value onto the stack
            stack.push_back(nums[i]);

            // While the stack has more than one value, check for non-coprimes
            while(stack.size() > 1) {

                // Remove the first two elements from the stack
                int first = stack.back();
                stack.pop_back();
                int second = stack.back();
                stack.pop_back();

                // If elements are non-coprime, push their LCM onto the stack
                // Else, add the elements back to the stack and break
                if( gcd(first, second) > 1 ) {
                    stack.push_back(lcm(first, second));
                } else {
                    stack.push_back(second);
                    stack.push_back(first);
                    break;
                }
            }
        }
        // Return the stack
        return stack;
    }
};

int main() {
    cout << "Replace Non-Coprime Numbers in Array Demo" << endl << endl;

    // Get the mode (custom, demo, or quit) from user input
    string mode;
    cout << "Select mode ([c]ustom, [d]emo, or [q]uit): ";
    cin >> mode;
    transform(mode.begin(), mode.end(), mode.begin(), ::tolower);

    // Create sets to match given modes
    set<string> customMode = {"custom", "[c]ustom", "c", "[c]"};
    set<string> demoMode = {"demo", "[d]emo", "d", "[d]"};
    set<string> quitMode = {"quit", "[q]uit", "q", "[q]"};

    // Initialize solution
    Solution s = Solution();

    if(customMode.find(mode) != customMode.end()) { // Custom mode selected, run with user input
        cout << "Custom mode selected" << endl;

        // Get the vector of values to use as a comma-seperated string from the user
        string input;
        cout << "Enter values as a comma-seperated string: ";
        cin >> input;
        transform(input.begin(), input.end(), input.begin(), ::tolower);

        if(quitMode.find(input) != quitMode.end()) { // If user entered quit, exit program
            cout << "Quitting..." << endl;
        } else { // Else, create vector from input and run program
            // Create an int vector values and tokenize input into it
            vector<int> values;
            stringstream ss(input);
            string token;

            // Print and tokenize input into values
            cout << "Running with values: ";
            while(getline(ss, token, ',')) {
                cout << token << " ";
                values.push_back(stoi(token));
            }
            cout << endl;

            // Calculate the resulting vector
            vector<int> result = s.replaceNonCoprimes(values);

            // Print the resulting vector
            cout << "Resulting vector: ";
            for(const auto& res : result) {
                cout << res << " ";
            }
            cout << endl;
        }

    } else if(demoMode.find(mode) != demoMode.end()) { // Demo mode selected, run with demo data
        cout << "Demo mode selected" << endl;

        // Initialize 2D vector demoData
        vector<vector<int>> demoData =  {
                                            {6,4,3,2,7,6,2},
                                            {2,2,1,1,3,3,3}
                                        };

        // Loop through all demo data
        for(vector<int> data : demoData) {
            // Print the data values
            cout << "Running demo with values: ";
            for(const auto& value : data) {
                cout << value << " ";
            }
            cout << endl;

            // Store the resulting vector of calling replaceNonCoprimes() with data
            vector<int> result = s.replaceNonCoprimes(data);

            // Print the result
            cout << "Resulting vector: ";
            for(const auto& res : result) {
                cout << res << " ";
            }
            cout << endl;
        }
    } else if(quitMode.find(mode) != quitMode.end()) { // Quit mode selected, exit program
        cout << "Quitting..." << endl;
    } else { // Else, unknown mode. Error
        cout << "Unknown mode: " << mode << endl;
        return -1;
    }
    return 0;
}