// Include custom utilities header
#include <utilities.h>

// Use standard namespace
using namespace std;

class Solution {
public:
    int maxPartitionsAfterOperations(string s, int k) {
        int n = s.length();

        // If k = 26, the entire string always has <= 26 distinct characters,
        // so it will always form only 1 partition (no matter what change we do).
        if (k == 26) return 1;

        // Prefix and suffix tracking:
        // p1[i] = number of partitions in prefix ending at index i
        // m1[i] = distinct-character bitmask for the current prefix segment at i
        // p2[i] = number of partitions in suffix starting from index i
        // m2[i] = distinct-character bitmask for the current suffix segment at i
        vector<int> p1(n), m1(n), p2(n), m2(n);

        // Simulate partitions from LEFT to RIGHT

        // Initialize partitions (current partition count) and mask (bitmask for distinct characters in current segment)
        int partitions = 1;
        int mask = 0;

        // Loop over all characters in string s from start to end
        for (int i = 0; i < n; ++i) {
            // Convert character to bitmask
            int charMask = 1 << (s[i] - 'a');

            // If adding this character exceeds k distinct letters, start a new partition
            // Else, continue current partition
            if (__builtin_popcount(mask | charMask) > k) {
                partitions++;
                mask = charMask;
            } else {
                mask |= charMask;
            }

            // Track the partitions and mask for index i
            p1[i] = partitions;
            m1[i] = mask;
        }

        // Simulate partitions from RIGHT to LEFT
        partitions = 1;
        mask = 0;

        // Loop over all characters in string s from end to beginning
        for (int i = n - 1; i >= 0; --i) {

            // Convert character to bitmask
            int charMask = 1 << (s[i] - 'a');

            // If adding this character exceeds k distinct letters, start a new partition
            // Else, continue current partition
            if (__builtin_popcount(mask | charMask) > k) {
                partitions++;
                mask = charMask;
            } else {
                mask |= charMask;
            }

            // Track the partitions and mask for index i
            p2[i] = partitions;
            m2[i] = mask;
        }

        // Initial answer: no modification, full suffix partitions from 0
        int ans = p2[0];

        // Try changing each character s[i] to ALL possible 26 letters
        for (int i = 0; i < n; ++i) {
            for (int letter = 0; letter < 26; ++letter) {
                int newCharMask = 1 << letter;

                // Get prefix partitions and mask before index i
                int prefixPartitions = (i > 0) ? p1[i - 1] : 0;
                int prefixMask = (i > 0) ? m1[i - 1] : 0;

                // Get suffix partitions and mask after index i
                int suffixPartitions = (i + 1 < n) ? p2[i + 1] : 0;
                int suffixMask = (i + 1 < n) ? m2[i + 1] : 0;

                // Compute new prefix including the modified character
                int newPrefixCount, newPrefixMask;
                
                // If first character, start a new partition
                // Else, decide what to do next
                if (i == 0) {
                    newPrefixCount = 1;
                    newPrefixMask = newCharMask;
                } else {
                    // If mask exceeds k, must split here
                    // else, continue prefix
                    if (__builtin_popcount(prefixMask | newCharMask) > k) {
                        newPrefixCount = prefixPartitions + 1;
                        newPrefixMask = newCharMask;
                    } else {
                        newPrefixCount = prefixPartitions;
                        newPrefixMask = prefixMask | newCharMask;
                    }
                }

                // Combine prefix & suffix
                int total = newPrefixCount + suffixPartitions;

                // If suffix exists and merging doesn't exceed k distinct,
                // we overcounted by 1, so subtract one.
                if (suffixPartitions > 0 &&
                    __builtin_popcount(newPrefixMask | suffixMask) <= k) {
                    total--;
                }

                // Update max partitions possible
                ans = max(ans, total);
            }
        }

        // Return answer
        return ans;
    }
};

int main() {
    printStartBanner("3003. Maximize the Number of Partitions After Operations", "O(n)", "O(n)");

    // Initialize solution
    Solution sol;

    // Get input mode from user
    string mode = selectMode();

    if(isCustomMode(mode)) { // If custom mode, run with user input
        customModeSelected();

        // Initialize input string and loop
        string input;
        while(true) {
            cout << "Enter the string s to use: ";
            getline(cin, input);
            toLowercase(input);

            // If exit or quit inputted, exit program
            if(isExitMode(input) || isQuitMode(input)) {
                return quitModeSelected();
            }

            // Assign input to string s
            string s = input;

            cout << "Enter the integer k to use: ";
            getline(cin, input);
            toLowercase(input);

            // If exit or quit inputted, exit program
            if(isExitMode(input) || isQuitMode(input)) {
                return quitModeSelected();
            }

            // Attempt to convert input to an int and assign to k
            int k;
            try { // Try to convert input to an int
                k = stoi(input);
            } catch(...) { // Catch unconvertable type, error and skip
                cout << "ERROR: Invalid input '" << input << "'. Please only enter an integer. Skipping..." << endl;
                continue;
            }

            // Calculate and print the result
            cout << "Maximum number of partitions for string " << s << " and k value " << k << " are " << sol.maxPartitionsAfterOperations(s, k) << endl;

        }
    } else if(isDemoMode(mode)) { // If demo mode selected, run with demo data
        demoModeSelected();

        // Initialize string vector demoSValues
        vector<string> demoSValues = {"accca", "aabaab", "xxyz"};
        // Initialize int vector demoKValues
        vector<int> demoKValues = {2, 3, 1};

        // Loop over the sets of demo data, print, then calculate result and print
        for(int i = 0; i < demoSValues.size(); i++) {
            cout << "Running program with string: " << demoSValues[i] << endl;
            cout << "Running program with k value: " << demoKValues[i] << endl;
            cout << "Maximum number of partitions for string " << demoSValues[i] << " and k value " << demoKValues[i] << " are " << sol.maxPartitionsAfterOperations(demoSValues[i], demoKValues[i]) << endl;
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // If exit or quit mode selected, exit program
        return quitModeSelected();
    } else { // Else, unknown mode selected, error
        return unknownModeSelected(mode);
    }

    // Exit program successfully
    return 0;
}