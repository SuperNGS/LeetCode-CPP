// Include custom utilities header
#include <utilities.h>

// Use standard namespace
using namespace std;

class Solution {
public:
    int finalValueAfterOperations(vector<string>& operations) {
        // Initialize x to 0
        int x = 0;

        // Loop through all operations
        for(const auto& op : operations) {
            if(op.find('+') != string::npos) { // Increment op selected, increment x
                x++;
            } else if(op.find('-') != string::npos) { // Decrement op selected, decrement x
                x--;
            }
        }

        // Return the x value
        return x;
    }
};

int main() {
    printStartBanner("2011. Final Value of Variable After Performing Operations", "O(n)", "O(1)");

    // Initialize the solution
    Solution s;

    // Get mode to run in from user
    string mode = selectMode();

    if(isCustomMode(mode)) { // If custom mode selected, run with user input
        customModeSelected();

        // Initialize input string and loop
        string input;
        while(true) {
            cout << "Enter operations (X++, ++X, X--, --X) as a comma-separated string: ";
            getline(cin, input);
            toLowercase(input);

            // If exit or quit entered, exit program
            if(isExitMode(input) || isQuitMode(input)) {
                return quitModeSelected();
            }

            // Convert operation back to uppercase
            toUppercase(input);

            // Tokenize input string into operations string vector, skipping invalid tokens
            vector<string> operations;
            stringstream ss(input);
            string token;
            while(getline(ss, token, ',')) {
                if(token == "X++" || token == "++X" || token == "X--" || token == "--X") { // If token is valid, add it to operations vector
                    operations.push_back(token);
                } else { // Else, invalid token, error and skip
                    cout << "ERROR: Invalid input '" << input << "'. Please only enter valid operations (X++, ++X, X--, --X). Skipping..." << endl;
                    continue;
                }
            }

            // Print the operations
            cout << "Running program with operations: ";
            for(const auto& op : operations) {
                cout << op << " ";
            }
            cout << endl;

            // Calculate and print the value of X after operations
            cout << "The value of X after operations is " << s.finalValueAfterOperations(operations) << endl;
        }
    } else if(isDemoMode(mode)) { // If demo mode selected, run with demo data
        demoModeSelected();

        // Initialize 2D string vector DemoOps to act as sets of operations to be performed on x
        vector<vector<string>> demoOps = {
            {"--X","X++","X++"},
            {"++X","++X","X++"},
            {"X++","++X","--X","X--"}
        };

        // Loop through the sets of operations, print them, and calculate and print the resulting X value
        for(vector<string>& operations : demoOps) {
            // Print the operations
            cout << "Running program with operations: ";
            for(const auto& op : operations) {
                cout << op << " ";
            }
            cout << endl;

            // Calculate and print x
            cout << "Value of x after operations is " << s.finalValueAfterOperations(operations) << endl;
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // If exit or quit mode selected, exit program
        return quitModeSelected();
    } else { // Else, unknown mode selected, error
        return unknownModeSelected(mode);
    }

    // Exit program successfully
    return 0;
}