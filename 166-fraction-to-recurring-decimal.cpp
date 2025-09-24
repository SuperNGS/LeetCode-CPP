#include <cstdlib>
#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {

        // Create a string to store result
        string result;

        if(numerator == 0) return "0"; // If dividing zero, return zero
        if((numerator < 0) ^ (denominator < 0)) result += "-"; // If numerator xor denominator are negative, result starts with the negative (-) sign

        // Get the absolute value of numerator and denominator
        long long num = abs(1LL*numerator);
        long long denom = abs(1LL*denominator);

        // Get the integer part for numerator / denominator, recalculate numerator as the remainder
        result += to_string(num/denom);
        num %= denom;

        // If remainder is 0, return the integer part of division
        if(num == 0) return result;

        // Add the decimal to result
        result += ".";

        // Create a map to hold parts of the remainder
        map<int,int> remainder;

        // While there is still more remainder to process and remainder has not repeated, loop
        while(num != 0 && remainder.find(num) == remainder.end()) {
            remainder[num] = result.length();
            num *= 10;
            result += to_string(num / denom);
            num %= denom;
        }

        // If remainder remains (repeat detected), add it to the string
        if(num != 0) {
            int repeating = remainder[num];
            result.insert(repeating, "(");
            result += ")";
        }

        // Return the resulting string
        return result;
    }
};

int main() {
    cout << "Fraction to Recurring Decimal Demo" << endl << endl;

    string mode;
    cout << "Select mode (custom or demo): ";
    cin >> mode;
    transform(mode.begin(), mode.end(), mode.begin(), ::tolower);

    Solution s = Solution();

    if(mode == "custom" || mode == "c") {
        cout << "Custom mode selected" << endl;

        string numerator;
        string denominator;
        while(numerator != "quit" && numerator != "q" && denominator != "quit" && denominator != "q") {
            cout << "Select numerator: ";
            cin >> numerator;
            if( numerator == "quit" || numerator == "q" ) {
                break;
            }
            cout << "Select denominator: ";
            cin >> denominator;
            if( denominator == "quit" || denominator == "q" ) {
                break;
            }

            cout << numerator << " / " << denominator << " = " << s.fractionToDecimal(stoi(numerator), stoi(denominator)) << endl;
        }
    } else if(mode == "demo" || mode == "d") {
        cout << "Demo mode selected" << endl;

        vector<pair<int, int>> divisions = {{1,4}, {-2,7}, {-1,-3}, {0,20}};
        for(const auto& division : divisions) {
            cout << division.first << " / " << division.second << " = " << s.fractionToDecimal(division.first, division.second) << endl;
        }
    } else {
        cout << "Unknown mode: " << mode << endl;
        return -1;
    }
    return 0;
}