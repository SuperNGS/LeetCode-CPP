#include <bits/stdc++.h>

// Include custom utiliites header
#include <utilities.h>

// Use standard namespace
using namespace std;

class Solution {
private:
    // Modulo constant for avoiding overflow in multiplication and addition
    const int MOD = 1e9 + 7;
public:
    int magicalSum(int m, int k, vector<int>& nums) {
        // Number of elements in nums
        int n = nums.size();

        // Precompute powers: powNum[i][j] = nums[i]^j (mod MOD)
        // powNum[i][0] = 1 (anything to the power 0 is 1)
        vector<vector<long long>> powNum(n, vector<long long>(m + 1, 1));

        // Fill in the power table using dynamic multiplication
        for (int i = 0; i < n; i++) {
            for (int j = 1; j <= m; j++) {
                // nums[i]^j = (nums[i]^(j-1) * nums[i]) % MOD
                powNum[i][j] = (powNum[i][j - 1] * nums[i]) % MOD;
            }
        }

        // Precompute combinations (nCk) using Pascal's triangle
        vector<vector<long long>> C(m + 1, vector<long long>(m + 1, 0));
        for (int i = 0; i <= m; i++) {
            // nC0 = nCn = 1
            C[i][0] = C[i][i] = 1;
            for (int j = 1; j < i; j++)
                // nCk = (n-1)C(k-1) + (n-1)Ck
                C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
        }

        // dp[pos][carry][used][ones] memoization state:
        // pos   = current index in nums
        // carry = carry-over bits in binary sum
        // used  = total number of picks made so far (sum of all cnt)
        // ones  = total '1' bits formed in binary positions so far
        static long long dp[55][35][35][35];
        static bool vis[55][35][35][35];
        memset(vis, 0, sizeof(vis)); // Reset visited states

        // Recursive DFS with memoization
        function<long long(int,int,int,int)> dfs = [&](int pos, int carry, int used, int ones) -> long long {
            // Base case: processed all numbers
            if (pos == n) {
                // Count remaining bits from leftover carry
                int extra = 0;
                int c = carry;
                while (c) {
                    if (c & 1) extra++; // Add a '1' if LSB is set
                    c >>= 1;           // Shift to next bit
                }
                // Valid configuration if exactly m elements used AND total ones match k
                return (used == m && ones + extra == k) ? 1 : 0;
            }

            // Return memoized result if state already computed
            if (vis[pos][carry][used][ones]) return dp[pos][carry][used][ones];
            vis[pos][carry][used][ones] = 1; // Mark state as visited

            long long ans = 0;

            // Try choosing cnt occurrences of nums[pos], where cnt ranges so that total used <= m
            for (int cnt = 0; cnt + used <= m; cnt++) {
                // Total for this bit position = carry + cnt additions
                int total = carry + cnt;
                int bit = total & 1;       // The resulting bit at this position (0 or 1)
                int ncarry = total >> 1;   // New carry for the next bit position
                int nones = ones + bit;    // Increment ones count if bit = 1

                // Recurse to next index with updated states
                long long sub = dfs(pos + 1, ncarry, used + cnt, nones);
                if (!sub) continue; // Skip if no valid combinations down this path

                // Number of ways to choose cnt occurrences out of remaining (m - used) slots
                long long ways = C[m - used][cnt];

                // Multiply by nums[pos]^cnt contribution
                long long prod = powNum[pos][cnt];

                // Update answer with contributions from this branching
                ans = (ans + sub * ways % MOD * prod) % MOD;
            }
            // Store in DP table and return
            return dp[pos][carry][used][ones] = ans;
        };

        // Start DFS from pos 0, carry 0, used 0, ones 0
        return (int)dfs(0, 0, 0, 0);
    }
};

int main() {
    printStartBanner("3539. Find Sum of Array Product of Magical Sequences", "O(n*m^4)", "O(n*m^3)");

    // Initialize solution
    Solution s;

    // Get input mode from user
    string mode = selectMode();

    if(isCustomMode(mode)) { // If custom mode selected, run with user input
        customModeSelected();

        // Initialize input string and loop
        string input;
        while(true) {
            // Get the m value from the user
            cout << "Enter m value: ";
            getline(cin, input);
            toLowercase(input);

            if(isExitMode(input)) { // If exit mode selected, break loop
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) { // If quit mode selected, exit program
                return quitModeSelected();
            }

            // Attempt to convert input to int m
            int m;
            try { // Attempt the conversion
                m = stoi(input);
            } catch(...) { // Catch unconvertable type, error and skip
                cout << "ERROR: Invalid input '" << input << "'. Please only enter an integer. Skipping..." << endl;
                continue;
            }

            // Get the k value from the user
            cout << "Enter a k value: ";
            getline(cin, input);
            toLowercase(input);

            if(isExitMode(input)) { // If exit mode selected, break loop
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) { // If quit mode selected, exit program
                return quitModeSelected();
            }

            // Attempt to convert input to int k
            int k;
            try { // Attempt the conversion
                k = stoi(input);
            } catch(...) { // Catch unconvertable type, error and skip
                cout << "ERROR: Invalid input '" << input << "'. Please only enter an integer. Skipping..." << endl;
                continue;
            }

            // Get the nums vector as a comma-separated string from the user
            cout << "Enter nums as a comma-separated string: ";
            getline(cin, input);
            toLowercase(input);

            if(isExitMode(input)) { // If exit mode selected, break loop
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) { // If quit mode selected, exit program
                return quitModeSelected();
            }

            // Tokenize the string and push back onto nums
            vector<int> nums;
            stringstream ss(input);
            string token;
            while(getline(ss, token, ',')) {
                try { // Attempt to convert token to an int and push back onto nums
                    nums.push_back(stoi(token));
                } catch(...) { // Catch unconvertable type, error and skip
                    cout << "ERROR: Invalid input '" << input << "'. Please only enter integers. Skipping..." << endl;
                    continue;
                }
            }

            // If no nums, skip
            if(nums.empty()) {
                cout << "INFO: No nums entered. Skipping..." << endl;
                continue;
            }

            // Calculate and print result
            cout << "Sum of Array Product of Magical Sequences: " << s.magicalSum(m, k, nums) << endl;
        }
    } else if(isDemoMode(mode)) { // If demo mode selected, run with demo data
        demoModeSelected();

        // Create a vector of demo m values
        vector<int> demoMValues = {5, 2, 1};
        // Create a vector of demo k values
        vector<int> demoKValues = {5, 2, 1};
        // Create a 2D vector of sets of demoNums
        vector<vector<int>> demoNums = {
            {1, 10, 100, 10000, 1000000},
            {5, 4, 3, 2, 1},
            {28}
        };

        // Loop through all sets of demo data and calculate result
        for(int i = 0; i < demoMValues.size(); i++) {
            // print the values
            cout << "Running program with m value: " << demoMValues[i] << endl;
            cout << "Running program with k value: " << demoKValues[i] << endl;
            cout << "Running program with nums: ";
            for(const auto& val : demoNums[i]) {
                cout << val << " ";
            }
            cout << endl;

            // Calculate and print the result
            cout << "Sum or Array Products of the Magical Sequence: " << s.magicalSum(demoMValues[i], demoKValues[i], demoNums[i]) << endl;
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // If exit or quit mode selected, exit program
        return quitModeSelected();
    } else { // Else, unknown mode, error
        return unknownModeSelected(mode);
    }

    // Exit program successfully
    return 0;
}