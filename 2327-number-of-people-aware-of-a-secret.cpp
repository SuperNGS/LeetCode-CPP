// Include custom utilities header
#include <utilities.h>

// Use standard namespace
using namespace std;

class Solution {
private:
    // Set a constant global to hold value of 10^9 + 7 for modulo
    const int mod = 1e9+7;
public:
    int peopleAwareOfSecret(int n, int delay, int forget) {
         // Initialize dp vector, set dp[1] to 1, and initialize a counter
        std::vector<int> dp(n+1);
        dp[1] = 1;
        int total = 0;

        // For i days starting from 2 to n, calculate how many people know the secret
        for(int i=2; i <= n; i++){
            // If passed the delay, calculate how many people share the secret (+1 each)
            if(i - delay >= 1) {
                total = (total + dp[i-delay]) % mod;
            }

            // If passed the forget, calculate how many people forget the secret (-1 each)
            if(i - forget >= 1) {
                total = (total - dp[i-forget] + mod) % mod;
            }

            // Set dp[i] to total number of people who know the secret on day i
            dp[i] = total;
        }

        // Set up a tracker to count the total number of people who know the secret on the last day
        int result = 0;
        for(int i = n - forget + 1; i <= n;i++){
            // Increment the result by how many people knew the secret on day  i
            result = (result + dp[i]) % mod;
        }
        // Return the result
        return result;
    }
};

int main() {
    printStartBanner("2327. Number of People Aware of a Secret", "O(n)", "O(n)");

    // Initialize the solution
    Solution s;

    // Get mode to run program in from user
    string mode = selectMode();

    if(isCustomMode(mode)) { // If custom mode selected, run with user input
        customModeSelected();

        // Initialize input string and loop
        string input;
        while(true) {
            // Get the n value from user
            cout << "Enter a positive integer to act as n: ";
            getline(cin, input);
            toLowercase(input);

            // If exit or quit entered, exit program
            if(isExitMode(input) || isQuitMode(input)) {
                return quitModeSelected();
            }

            // Try to convert input to int n, error and skip if invalid
            int n;
            try {
                n = stoi(input);
            } catch(...) {
                cout << "ERROR: Invalid input '" << input << "'. Please only enter an integer. Skipping..." << endl;
                continue;
            }

            // If n is negative, error and skip
            if(n < 0) {
                cout << "ERROR: Value of n must be positive (" << n << " entered). Skipping..." << endl;
                continue;
            }

            // Get the n value from user
            cout << "Enter a positive integer to act as delay: ";
            getline(cin, input);
            toLowercase(input);

            // If exit or quit entered, exit program
            if(isExitMode(input) || isQuitMode(input)) {
                return quitModeSelected();
            }

            // Try to convert input to int delay, error and skip if invalid
            int delay;
            try {
                delay = stoi(input);
            } catch(...) {
                cout << "ERROR: Invalid input '" << input << "'. Please only enter an integer. Skipping..." << endl;
                continue;
            }

            // If delay is negative, error and skip
            if(delay < 0) {
                cout << "ERROR: Value of delay must be positive (" << n << " entered). Skipping..." << endl;
                continue;
            }

            // Get the n value from user
            cout << "Enter a positive integer to act as forget: ";
            getline(cin, input);
            toLowercase(input);

            // If exit or quit entered, exit program
            if(isExitMode(input) || isQuitMode(input)) {
                return quitModeSelected();
            }

            // Try to convert input to int forget, error and skip if invalid
            int forget;
            try {
                forget = stoi(input);
            } catch(...) {
                cout << "ERROR: Invalid input '" << input << "'. Please only enter an integer. Skipping..." << endl;
                continue;
            }

            // If forget is negative, error and skip
            if(forget < 0) {
                cout << "ERROR: Value of forget must be positive (" << n << " entered). Skipping..." << endl;
                continue;
            }

            // Calculate and print the number of people aware of secret at end of day n
            cout << "Number of people aware of a secret at end of day n is " << s.peopleAwareOfSecret(n, delay, forget) << endl;
        }
    } else if(isDemoMode(mode)) { // If demo mode selected, run with demo data
        demoModeSelected();

        // Initialize int vector demoNValues to act as n, number of days
        vector<int> demoNValues = {6,4};
        // Initialize int vector demoDelayValues to act as delay before new person learns secret
        vector<int> demoDelayValues = {2,1};
        // Initialize int vector demoForgetValues to act as delay before person forgets value
        vector<int> demoForgetValues = {4,3};

        // Loop through the sets of demo data, print them, then calculate and print number of people aware of secret at the end of day n
        for(int i = 0; i < demoNValues.size(); i++) {
            // Print the demo data values for this run
            cout << "Running program with n: " << demoNValues[i] << endl;
            cout << "Running program with delay: " << demoDelayValues[i] << endl;
            cout << "Running program with forget: " << demoForgetValues[i] << endl;

            // Calculate and print result
            cout << "Number of people aware of a secret at the end of day n: " << s.peopleAwareOfSecret(demoNValues[i], demoDelayValues[i], demoForgetValues[i]) << endl;
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // If exit or quit mode selected, exit program
        return quitModeSelected();
    } else { // Else, unknown mode selected, error
        return unknownModeSelected(mode);
    }

    // Exit program successfully
    return 0;
}