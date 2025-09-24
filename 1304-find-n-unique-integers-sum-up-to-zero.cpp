#include <cstdlib>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    std::vector<int> sumZero(int n) {
        // Initialize an empty vector to store the results
        std::vector<int> values;

        // If n is odd, add 0 to the vector and decrement n
        if( n % 2 != 0) {
            values.push_back(0);
            n--;
        }

        // Calculate how many pairs of values are needed in the vector
        int pairs = n / 2;

        // For each pair, push a pair of values that sum to 0
        for(int i = 1; i <= pairs; i++) {
            values.push_back(i);
            values.push_back(-i);
        }

        // Return the vector
        return values;
    }
};

int main() {
    cout << "Find N Unique Integers Sum up to Zero Demo" << endl << endl;

    // Initialize the solution
    Solution s = Solution();

    // Get the mode to run in from user
    string mode;
    cout << "Select mode (custom or demo): ";
    cin >> mode;
    transform(mode.begin(), mode.end(), mode.begin(), ::tolower);

    if(mode == "custom" || mode == "c") { // If custom or c selected, run solution with user input
        cout << "Custom mode selected" << endl;

        // Create holder for input and loop
        string input;
        while(true) {
            // Get n value from user input
            cout << "Select n value: ";
            cin >> input;
            transform(input.begin(), input.end(), input.begin(), ::tolower);

            // If input is quit or q, exit loop
            if(input == "quit" || input == "q") {
                break;
            }

            // Calculate the N unique integers summing up to zero, store in vector
            vector<int> values = s.sumZero(stoi(input));

            // Loop over vector and print
            cout << "The " << input << " values summing to 0 are: ";
            for(const auto& value : values) {
                cout << value << " ";
            }
            cout << endl;

        }
    } else if(mode == "demo" || mode == "d") { // if demo or d selected, run solution with demo data
        cout << "Demo mode selected" << endl;

        // Create a vector<int> of demo n values to use
        vector<int> nValues = {3, 5, 10, 15};

        // Loop over each n value in demo data and compute
        for(const auto& n : nValues) {
            vector<int> values = s.sumZero(n);

            cout << "The " << n << " values summing to 0 are: ";
            for(const auto& value : values) {
                cout << value << " ";
            }
            cout << endl;
        }
    } else if(mode == "quit" || mode == "q") { // If quit or q selected, exist program
        cout << "Quitting..." << endl;
        return 0;
    } else { // Else unknown mode selected, error
        cout << "Invalid mode: " << mode << endl;
        return -1;
    }

    return 0;
}