#include <unordered_set>
#include <queue>

// Include custom utilities header
#include <utilities.h>

// Use standard namespace
using namespace std;

class Solution {
public:
    string findLexSmallestString(string s, int a, int b) {
        // Initial smallest string is original string
        string smallest = s;

        // Initialize a visited set and a queue
        unordered_set<string> visited;
        queue<string> bfs;

        // Add initial string to queue and visited set
        bfs.push(s);
        visited.insert(s);

        // Loop until queue empty
        while(!bfs.empty()) {
            // Pop the top elements from queue
            string current = bfs.front();
            bfs.pop();

            // If current string is new record, set smallest
            if(current < smallest) smallest = current;

            // Get added string
            string added = current;
            for(int i = 1; i < added.length(); i += 2) {
                added[i] = ((added[i] - '0' + a) % 10) + '0';
            }

            // If added string not already found, process it
            if(!visited.count(added)) {
                visited.insert(added);
                bfs.push(added);
            }

            // Get the rotated string
            string rotated = current.substr(current.length() - b) + current.substr(0, current.length() - b);

            // If rotated string not already found, process it
            if(!visited.count(rotated)) {
                visited.insert(rotated);
                bfs.push(rotated);
            }
        }

        // Return smallest string
        return smallest;
    }
};

int main() {
    printStartBanner("1625. Lexicographically Smallest String After Applying Operations", "O(N^2)", "O(N)");

    // Initialize solution
    Solution sol;

    // Get mode to run program in from user
    string mode = selectMode();

    if(isCustomMode(mode)) { // If custom mode, run with user input
        customModeSelected();

        // Initialize input string and loop
        string input;
        while(true) {
            // Get the s value from the user
            cout << "Enter a numeric string to act as the s value: ";
            getline(cin, input);
            toLowercase(input);

            // If exit or quit entered, exit program
            if(isExitMode(input) || isQuitMode(input)) { 
                return quitModeSelected();
            }

            // if string s is not numeric, skip
            if(input.find_first_not_of("0123456789") != input.npos) {
                cout << "ERROR: Invalid input '" << input << "'. Please only enter numeric values. Skipping..." << endl;
                continue;
            }

            // Assign input to string s
            string s = input;

            // Get the a value from the user
            cout << "Enter an integer to act as the a value: ";
            getline(cin, input);
            toLowercase(input);

            // If exit or quit entered, exit program
            if(isExitMode(input) || isQuitMode(input)) { 
                return quitModeSelected();
            }

            // Attempt to convert input to int a
            int a;
            try { // Convert input to int
                a = stoi(input);
            } catch(...) { // Catch unconvertable type, error and skip
                cout << "ERROR: Invalid input '" << input << "'. Please only enter an integer. Skipping..." << endl;
                continue;
            }

            // Get the b value from the user
            cout << "Enter an integer to act as the b value: ";
            getline(cin, input);
            toLowercase(input);

            // If exit or quit entered, exit program
            if(isExitMode(input) || isQuitMode(input)) { 
                return quitModeSelected();
            }

            // Attempt to convert input to int b
            int b;
            try { // Convert input to int
                b = stoi(input);
            } catch(...) { // Catch unconvertable type, error and skip
                cout << "ERROR: Invalid input '" << input << "'. Please only enter an integer. Skipping..." << endl;
                continue;
            }

            // Calculate and print the lexicographically smallest string after operations
            cout << "The lexicographically smallest string after operations is " << sol.findLexSmallestString(s, a, b) << endl;
        }
    } else if(isDemoMode(mode)) { // If demo mode, run with demo data
        demoModeSelected();

        // Initialize string vector demoSValues to use as s values
        vector<string> demoSValues = {"5525","74","0011"};
        // Initialize int vectors demoAValues and demoBValues to use as a and b values
        vector<int> demoAValues = {9,5,4};
        vector<int> demoBValues = {2,1,2};

        // Loop through sets of demo data, print them, then calculate the lexicographically smallest string and print it
        for(int i = 0; i < demoSValues.size(); i++) {
            // Print the s, a, and b values
            cout << "Running program with..." << endl;
            cout << "\ts = " << demoSValues[i] << endl;
            cout << "\ta = " << demoAValues[i] << endl;
            cout << "\tb = " << demoBValues[i] << endl;

            // Calculate and print the lexicographically smallest string after operations
            cout << "The lexicographically smallest string after operations is " << sol.findLexSmallestString(demoSValues[i], demoAValues[i], demoBValues[i]) << endl;
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // If exit or quit mode, exit program
        return quitModeSelected();
    } else { // Else, unknown mode, error
        return unknownModeSelected(mode);
    }

    // Exit program successfully
    return 0;
}