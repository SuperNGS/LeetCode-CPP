#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
private:
    // Helper method, returns true if number does not contain a 0. False otherwise
    bool isNoZero(int n) {
        // Convert to string
        string s = to_string(n);
        // Check that there is no 0 character
        return s.find('0') == string::npos;
    }
public:
    vector<int> getNoZeroIntegers(int n) {
        
        for(int i = 1; i < n; i++) {
            // If i contains a 0, skip
            if(!isNoZero(i)) {
                continue;
            }

            // Calculate a and b such that b is the complement of a, both summing to n
            int a = i;
            int b = n - i;

            // If b is a No-Zero Integer, return a and b
            if( isNoZero(b) ) {
                return {a, b};
            }
        }

        // If no result found, return [0, 0]
        return {0, 0};
    }
};

int main() {
    cout << "Convert Integer to the Sum of Two No-Zero Integers Demo" << endl << endl;
    
    Solution s = Solution();

    cout << "Select mode (custom or demo): ";
    string mode;
    cin >> mode;
    transform(mode.begin(), mode.end(), mode.begin(), ::tolower);

    if(mode == "custom" || mode == "c") {
        int n;
        cout << "Choose a value n: ";
        cin >> n;
        vector<int> value = s.getNoZeroIntegers(n);

        if(value != vector<int>{0, 0}) {
            cout << "Value " << n << " decomposes into integers " << value[0] << " and " << value[1] << endl;
        } else {
            cout << "Value " << n << " can't be decomposed into two no-zero integers" << endl;
        }
    } else if(mode == "demo" || mode == "d") {
        int n = 5;
        cout << "Using n = " << n << endl;
        vector<int> value = s.getNoZeroIntegers(n);

        if(value != vector<int>{0, 0}) {
            cout << "Value " << n << " decomposes into integers " << value[0] << " and " << value[1] << endl;
        } else {
            cout << "Value " << n << " can't be decomposed into two no-zero integers" << endl;
        }

        n = 31;
        cout << "Using n = " << n << endl;
        value = s.getNoZeroIntegers(n);

        if(value != vector<int>{0, 0}) {
            cout << "Value " << n << " decomposes into integers " << value[0] << " and " << value[1] << endl;
        } else {
            cout << "Value " << n << " can't be decomposed into two no-zero integers" << endl;
        }

        n = 100;
        cout << "Using n = " << n << endl;
        value = s.getNoZeroIntegers(n);

        if(value != vector<int>{0, 0}) {
            cout << "Value " << n << " decomposes into integers " << value[0] << " and " << value[1] << endl;
        } else {
            cout << "Value " << n << " can't be decomposed into two no-zero integers" << endl;
        }
    } else {
        cout << "Invalid mode: " << mode;
    }
    return 0;
}