#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <limits>

// Custom utilities header
#include <utilities.h>

// Use std namespace
using namespace std;

class Solution {
public:
    int compareVersion(string version1, string version2) {
        // Initialize indexes i and j
        int i = 0, j = 0;
        // Initialize upper bounds of string n and m
        int n = version1.size(), m = version2.size();

        // Loop until both i crosses upper bounds n and j crosses upper bounds m
        while(i < n || j < m) {

            // Initialize counters for version1 and version2
            long val1 = 0, val2 = 0;

            // Parse the next value in version 1
            while(i < n && version1[i] != '.') {
                val1 = val1 * 10 + (version1[i] - '0');
                i++;
            }

            // Parse the next value in version 2
            while(j < m && version2[j] != '.') {
                val2 = val2 * 10 + (version2[j] - '0');
                j++;
            }

            // Compare current parsed versions
            if(val1 < val2) return -1; // Version 1 has fewer revisions
            if(val1 > val2) return 1; // Version 2 has more revisions

            // Increment i and j to skip period
            i++;
            j++;
        }

        // Versions are equal
        return 0;
    }
};

int main() {
    // Print start banner
    printStartBanner("165. Compare Version Numbers", "O(n+m)", "O(1)");

    // Initialize solution
    Solution s;

    // Prompt user to select mode
    string mode = selectMode();

    if(isCustomMode(mode)) { // Custom mode selected, run with user input
        customModeSelected();

        // Initialize holders for versions entered by user
        string version1;
        string version2;

        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Loop until user quits or exits
        while(true) {
            // Get the first version or quit/exit commands
            cout << "Please enter version 1 as a period-separated string or press enter to exit: ";
            getline(cin, version1);

            if(isQuitMode(version1)) { // If user entered quit, exit program
                return quitModeSelected();
            } else if(version1.empty() || isExitMode(version1)) { // If user entered blank string or exit, exit loop
                exitModeSelected();
                break;
            }

            // Get the second version or quit/exit commands from user
            cout << "Please enter version 2 as a period-separated string: ";
            getline(cin, version2);


            if(isQuitMode(version2)) { // If user entered quit, exit program
                quitModeSelected();
            } else if(isExitMode(version2) || version2.empty()) { // If user entered blank string or exit, exit loop
                exitModeSelected();
                break;
            }

            // Run compareVersion() with the user entered versions and store the result
            int result = s.compareVersion(version1, version2);

            if(result == -1) { // If result is -1, version one has fewer revisions
                cout << "Version " << version1 << " has fewer revisions" << endl;
            } else if (result == 0) { // If result is 0, versions have equal number of revisions
                cout << "Version " << version1 << " and version " << version2 << " are equal" << endl;
            } else { // Else, result is 1, version two has fewer revisions
                cout << "Version " << version2 << " has fewer revisions" << endl;
            }
        }

    } else if(isDemoMode(mode)) { // Demo mode selected, run program with demo data
        demoModeSelected();

        // Initialize vector of int pairs demo data to run test cases
        vector<pair<string, string>> demoData = {
                                                            {"1.2", "1.10"},
                                                            {"1.01", "1.001"},
                                                            {"1.0", "1.0.0.0"},
                                                            {"1.999999999999999", "1.100"},
                                                            {"0", "0.0.0.0"}
                                                        };

        // For version pairs in demodata, compare them and print results
        for(const auto& versions : demoData) {
            cout << "Comparing version " << versions.first << " with version " << versions.second << endl;

            // Get the result of comparing the two versions
            int result = s.compareVersion(versions.first, versions.second);

            if(result == -1) { // If result is -1, version 1 has fewer revisions
                cout << "Version " << versions.first << " has fewer revisions" << endl;
            } else if (result == 0) { // If result is 0, versions are equal
                cout << "Version " << versions.first << " and version " << versions.second << " are equal" << endl;
            } else { // Else result is 1, version 2 has fewer revisions
                cout << "Version " << versions.second << " has fewer revisions" << endl;
            }
        }
    } else if(isQuitMode(mode)) { // Quit mode selected, exit program
        quitModeSelected();
    } else { // Else, unknown mode selected, error
        unknownModeSelected(mode);
    }

    // Exit program
    return 0;
}