#include <unordered_map>

// Include custom utilities header
#include <utilities.h>

// Use standard namespace
using namespace std;

class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        int n = nums.size();
        if (n == 0) return 0;

        // Build intervals [nums[i]-k, nums[i]+k]
        vector<long long> starts(n), ends(n);
        for (int i = 0; i < n; ++i) {
            starts[i] = (long long)nums[i] - (long long)k;
            ends[i]   = (long long)nums[i] + (long long)k;
        }
        sort(starts.begin(), starts.end());
        sort(ends.begin(), ends.end());

        // Compute maximum coverage anywhere (use sweep events)
        vector<pair<long long,int>> events;
        events.reserve(2*n);
        for (int i = 0; i < n; ++i) {
            events.emplace_back(starts[i], +1);
            // Use end + 1 for inclusive intervals
            events.emplace_back(ends[i] + 1LL, -1);
        }
        sort(events.begin(), events.end());

        int cur = 0;
        int max_cover_overall = 0;
        for (size_t i = 0; i < events.size(); ) {
            long long x = events[i].first;
            // apply all events at the same coordinate
            while (i < events.size() && events[i].first == x) {
                cur += events[i].second;
                ++i;
            }
            max_cover_overall = max(max_cover_overall, cur);
        }

        // Frequency map for values that actually appear in nums
        unordered_map<long long,int> freq;
        freq.reserve(n*2);
        for (int v : nums) ++freq[v];

        int answer = 0;
        // For each distinct value v in the array compute:
        // cover_v = number of intervals that cover v
        // candidate = min(cover_v, freq[v] + numOperations)
        for (auto &p : freq) {
            long long v = p.first;
            int f = p.second;
            // count starts <= v
            int cntStarts = int(upper_bound(starts.begin(), starts.end(), v) - starts.begin());
            // count ends < v  -> lower_bound on ends
            int cntEndsBefore = int(lower_bound(ends.begin(), ends.end(), v) - ends.begin());
            int cover = cntStarts - cntEndsBefore;
            int candidate = min(cover, f + numOperations);
            answer = max(answer, candidate);
        }

        // Also consider choosing a target x that's not in nums: best we can do is
        // min(max_cover_overall, numOperations) (since B(x)=0).
        answer = max(answer, min(max_cover_overall, numOperations));

        // At least 1 (array non-empty), but function logic already ensures that.
        return answer;
    }
};

int main() {
    printStartBanner("3347. Maximum Frequency of an Element After Performing Operations II", "O(n log n)", "O(n)");

    // Initialize the solution
    Solution s;

    // Get the mode to run program in from user
    string mode = selectMode();

    if(isCustomMode(mode)) { // If custom mode, run with user input
        customModeSelected();

        // Initialize input string and loop
        string input;
        while(true) {
            // Get nums input from user
            cout << "Enter nums as a comma-separated string of integers: ";
            getline(cin, input);
            toLowercase(input);

            // If exit or quit inputted, exit program
            if(isExitMode(input)) {
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) {
                return quitModeSelected();
            }

            // Parse nums input into nums vector
            vector<int> nums = stringToIntVector(input);

            // If no nums entered, skip
            if(nums.empty()) {
                cout << "INFO: No nums entered. Please try again. Skipping..." << endl;
                continue;
            }

            // Get k input from user
            cout << "Enter k as an integer: ";
            getline(cin, input);
            toLowercase(input);

            // If exit or quit inputted, exit program
            if(isExitMode(input)) {
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) {
                return quitModeSelected();
            }

            // Parse k input into integer
            int k;
            try {
                k = stoi(input);
            } catch(...) {
                cout << "ERROR: Invalid input '" << input << "'. Please enter k as an integer. Skipping..." << endl;
                continue;
            }

            // Get numOperations value from user
            cout << "Enter numOperations as an integer: ";
            getline(cin, input);
            toLowercase(input);

            // If exit or quit inputted, exit program
            if(isExitMode(input)) {
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) {
                return quitModeSelected();
            }

            // Parse numOperations input into integer
            int numOperations;
            try {
                numOperations = stoi(input);
            } catch(...) {
                cout << "ERROR: Invalid input '" << input << "'. Please enter numOperations as an integer. Skipping..." << endl;
                continue;
            }

            // Calculate and print maximum frequency of an element after performing operations
            int result = s.maxFrequency(nums, k, numOperations);
            cout << "Maximum frequency of an element after performing operations: " << result << endl;
            cout << "----------------------------------------" << endl;
        }
    } else if(isDemoMode(mode)) { // If demo mode, run with demo data
        demoModeSelected();

        // Initialize 2D int vector demoNums
        vector<vector<int>> demoNums = {
            {1,4,5},
            {5,11,20,20}
        };
        // Initialize int vector demoKValues
        vector<int> demoKValues = {1,5};
        // Initialize int vector demoNumOperations
        vector<int> demoNumOperations = {2,1};

        // Loop over sets of demo data, print them, then calculate maximum frequency of an element after performing operations
        for(int i = 0; i < demoNums.size(); i++) {
            // Print demo nums and demo k value
            cout << "Demo nums: [";
            for(int j = 0; j < demoNums[i].size(); j++) {
                cout << demoNums[i][j];
                if(j < demoNums[i].size() - 1) {
                    cout << ", ";
                }
            }
            cout << "], k: " << demoKValues[i] << ", numOperations: " << demoNumOperations[i] << endl;

            // Calculate and print maximum frequency of an element after performing operations
            int result = s.maxFrequency(demoNums[i], demoKValues[i], demoNumOperations[i]);
            cout << "Maximum frequency of an element after performing operations: " << result << endl;
            cout << "----------------------------------------" << endl;
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // If exit or quit mode, exit program
        return quitModeSelected();
    } else { // Else, unknown mode, error
        return unknownModeSelected(mode);
    }

    // Exit program successfully
    return 0;
}