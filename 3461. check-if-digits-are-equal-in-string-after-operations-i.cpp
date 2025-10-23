// Include custom utilities header
#include <utilities.h>

// Use standard namespace
using namespace std;

class Solution {
public:
    bool hasSameDigits(string s) {
        // Initialize a holder for the resulting string
        string result;

        // While s has more than two characters, loop
        while(s.length() > 2) {
            // Reset result string
            result = "";

            // Loop over all characters of s starting from the second character
            for(int i = 1; i < s.length(); i++) {
                // Get the sum of character s[i] + s[i-1] modulo 10, store in result
                result += (s[i] + s[i-1]) % 10;
            }

            // Set s equal to result before looping again
            s = result;
        }

        // Return if the first two characters of result are equal
        return result[0] == result[1];
    }
};

int main() {
    printStartBanner("3461. Check If Digits Are Equal in String After Operations I", "O(N^2)", "O(N)");

    // Initialize the solution
    Solution sol;

    // Get mode to run program in from user
    string mode = selectMode();

    if(isCustomMode(mode)) { // If custom mode, run with user input
        customModeSelected();

        // Initialize input string and loop
        string input;
        while(true) {
            cout << "Enter numeric string to act as s value: ";
            getline(cin, input);
            toLowercase(input);

            // If exit or quit entered, exit program
            if(isExitMode(input) || isQuitMode(input)) {
                return quitModeSelected();
            }

            // If all characters in input aren't digits, error and skip
            if(!isNumericString(input)) {
                cout << "ERROR: Invalid input '" << input << "'. Please enter a numeric string. Skipping..." << endl;
                continue;
            }

            // Calculate and print the result
            cout << "String " << input << " contains the same digits: " << (sol.hasSameDigits(input) ? "yes" : "no") << endl;
        }
    } else if(isDemoMode(mode)) { // If demo mode, run with demo data
        demoModeSelected();

        // Initialize string vector of demoSValues, numeric strings to run demo with
        vector<string> demoSValues = {"3902", "34789", "242"};

        // Loop through each string in demoSValues, print them, then calculate and print the result of hasSameDigits()
        for(const auto& s : demoSValues) {
            // Print s value
            cout << "Running program with s value: " << s << endl;

            // Calculate and print result of hasSameDigits()
            cout << "String has same digits: " << (sol.hasSameDigits(s) ? "yes" : "no") << endl;
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // If exit or quit mode, exit program
        return quitModeSelected();
    } else { // Else, unknown mode, error
        return unknownModeSelected(mode);
    }

    // Exit program successfully
    return 0;
}