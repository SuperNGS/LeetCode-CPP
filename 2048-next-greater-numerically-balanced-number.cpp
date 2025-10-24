// Include custom utilities header
#include <utilities.h>

// Use standard namespace
using namespace std;

class Solution {
private:
    // Generate all balanced numbers with total length <= maxLen (here 7).
    static vector<int> generateBalancedNums(int maxLen = 7) {
        set<int> results;
        // digits 1..9, each digit d if chosen must appear exactly d times.
        // We choose any subset of {1..9} whose sum of d's <= maxLen.
        // For each subset, build the multiset of digits (d repeated d times), permute, convert to int.
        
        // We will use bitmask over digits 1..9 (bits 0..8)
        for (int mask = 1; mask < (1 << 9); ++mask) {
            int totalLen = 0;
            for (int bit = 0; bit < 9; ++bit) {
                if (mask & (1 << bit)) totalLen += (bit + 1);
            }
            if (totalLen == 0 || totalLen > maxLen) continue;
            
            // Build digit vector (as chars) with digit d repeated d times
            string digits;
            digits.reserve(totalLen);
            for (int bit = 0; bit < 9; ++bit) {
                if (mask & (1 << bit)) {
                    char ch = char('0' + (bit + 1));
                    for (int k = 0; k < (bit + 1); ++k) digits.push_back(ch);
                }
            }
            
            // Permute unique arrangements
            sort(digits.begin(), digits.end());
            do {
                // Leading digit won't be '0' because digits are 1..9.
                // Convert to int
                int val = 0;
                for (char c : digits) {
                    val = val * 10 + (c - '0');
                    // Optional early stop if val would exceed 10^7 (we want <= 9,999,999)
                    if (val > 10000000) break;
                }
                if (val <= 10000000) results.insert(val);
            } while (next_permutation(digits.begin(), digits.end()));
        }
        
        // Move to vector, sort, and return
        vector<int> balancedNums(results.begin(), results.end());
        sort(balancedNums.begin(), balancedNums.end());
        return balancedNums;
    }
public:
    int nextBeautifulNumber(int n) {
        // Generate all balanced numbers up to 10^7 once
        static const vector<int> balanced = generateBalancedNums(7);
        // Get an iterator for where n would be inserted in the sorted balanced numbers
        auto it = upper_bound(balanced.begin(), balanced.end(), n);
        // Return either the value at the position of iterator or -1 if insertion not possible
        return (it != balanced.end()) ? *it : -1;
    }
};

int main() {
    printStartBanner("2048. Next Greater Numerically Balanced Numer", "O(1)", "O(1)");

    // Initialize the solution
    Solution s;

    // Get input mode from user
    string mode = selectMode();

    if(isCustomMode(mode)) { // If custom mode, run program with user input
        customModeSelected();

        // Initialize input string and loop
        string input;
        while(true) {
            cout << "Enter integer n to calculate next beautiful number: ";
            getline(cin, input);
            toLowercase(input);

            // If exit or quit entered, exit program
            if(isExitMode(input) || isQuitMode(input)) {
                return quitModeSelected();
            }

            // Attempt to convert input to int n, error and skip if not possible
            int n;
            try {
                n = stoi(input);
            } catch(...) {
                cout << "ERROR: Invalid input '" << input << "'. Please only enter an integer. Skipping..." << endl;
                continue;
            }

            // Calculate and print result
            cout << "The next beautiful number after " << n << " is " << s.nextBeautifulNumber(n) << endl;
        }
    } else if(isDemoMode(mode)) { // If demo mode, run program with demo data
        demoModeSelected();

        // Initialize int vector demoNValues to act as values of n
        vector<int> demoNValues = {1,1000,3000};

        // Loop through each demo n value, print it, then calculate and print the result of nextBeautifulNumber()
        for(const auto& n : demoNValues) {
            cout << "Running program with n value: " << n << endl;
            cout << "Next beautiful number is " << s.nextBeautifulNumber(n) << endl;
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // If exit or quit mode selected, exit program
        return quitModeSelected();
    } else { // Else, unknown mode, error
        return unknownModeSelected(mode);
    }

    // Exit program successfully
    return 0;
}