#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>

using namespace std;

class Solution {
public:
    int compareVersion(string version1, string version2) {
        // Create a string stream for each version string, also create two strings to hold tokens
        stringstream ss1(version1), ss2(version2);
        string token1, token2;
        
        // Loop until a value is returned
        while (true) {

            // Extract the next element from both stringstreams
            getline(ss1, token1, '.');
            getline(ss2, token2, '.');

            // If both stringstreams are empty, return 0 (Versions are equal)
            if(token1.empty() && token2.empty()) {
                return 0;
            }

            // Assign val1 and val2 to 0 if no token available or token values as ints if available
            int val1 = token1.empty() ? 0 : stoi(token1);
            int val2 = token2.empty() ? 0 : stoi(token2);

            if (val1 < val2) { // If version 1 has fewer revisions, return -1
                return -1;
            } else if (val1 > val2) { // If version 2 has fewer revisions, return 1
                return 1;
            } else { // Else, clear tokens and loop again
                token1.clear(); token2.clear();
            }
        }
    }
};

int main() {
    cout << "Compare Version Numbers Demo" << endl << endl;
    
    Solution s = Solution();

    cout << "Select mode (custom or demo): ";
    string mode;
    cin >> mode;
    transform(mode.begin(), mode.end(), mode.begin(), ::tolower);

    if(mode == "custom") {
        cout << "Custom mode selected" << endl << endl;

        string version1;
        string version2;

        while(true) {
            cout << "Please enter version 1 as a period-separated string: ";
            cin >> version1;
            if(version1 == "quit" || version1 == "q") {
                break;
            }
            cout << "Please enter version 2 as a period-separated string: ";
            cin >> version2;
            if(version2 == "quit" || version2 == "q") {
                break;
            }

            int result = s.compareVersion(version1, version2);

            if(result == -1) {
                cout << "Version " << version1 << " has fewer revisions" << endl;
            } else if (result == 0) {
                cout << "Version " << version1 << " and version " << version2 << " are equal" << endl;
            } else {
                cout << "Version " << version2 << " has fewer revisions" << endl;
            }
        }

    } else if(mode == "demo") {
        cout << "Demo mode selected" << endl << endl;

        vector<pair<string, string>> versionsToCompare = {{"1.2", "1.10"}, {"1.01", "1.001"}, {"1.0", "1.0.0.0"}};
        for(const auto& versions : versionsToCompare) {
            cout << "Comparing version " << versions.first << " with version " << versions.second << endl;

            int result = s.compareVersion(versions.first, versions.second);

            if(result == -1) {
                cout << "Version " << versions.first << " has fewer revisions" << endl;
            } else if (result == 0) {
                cout << "Version " << versions.first << " and version " << versions.second << " are equal" << endl;
            } else {
                cout << "Version " << versions.second << " has fewer revisions" << endl;
            }
        }
    } else {
        cout << "Invalid mode: " << mode;
    }
}