#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <set>
#include <sstream>

// Custom utilities header
#include <utilities.h>

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
    printStartBanner("2197 Replace Non Coprime Numbers in Array", "O(n log(max(nums)))", "O(n)");

    // Get the mode (custom, demo, or quit) from user input
    string mode = selectMode();

    // Initialize solution
    Solution s;

    if(isCustomMode(mode)) { // Custom mode selected, run with user input
        customModeSelected();

        // Initialize input string
        string input;
        while(true) {
            cout << "Enter values as a comma-seperated string or press enter to exit: ";
            getline(cin, input);
            toLowercase(input);

            if(input.empty() || isExitMode(input)) { // If user entered exit, break loop
                exitModeSelected();
                break;
            } else if(quitMode.find(input) != quitMode.end()) { // If user entered quit, exit program
                cout << "Quitting..." << endl;
            }

            // Create an int vector values and tokenize input into it
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

            // Print input values
            cout << "Running with values: ";
            for(const auto& value : values) {
                cout << value << " ";
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
    } else if(isDemoMode(mode)) { // Demo mode selected, run with demo data
        demoModeSelected();

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
    } else if(isExitMode(mode) || isQuitMode(mode)) { // Quit or exit mode selected, exit program
        return quitModeSelected();
    } else { // Else, unknown mode. Error
        return unknownModeSelected(mode);
    }

    // Exit program
    return 0;
}