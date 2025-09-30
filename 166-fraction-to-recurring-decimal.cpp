#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

// Custom utilities header
#include <utilities.h> 

// Use std namespace
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
        unordered_map<int,int> remainder;

        // While there is still more remainder to process
        while(num != 0) {

            // If remainder has already been encountered, we have a repeat
            if(remainder.count(num)) {
                result.insert(remainder[num], "(");
                result += ")";
                break;
            }

            // Store first occurrence of remainder
            remainder[num] = result.length();


            // Calculate remaining remainder
            num *= 10;
            result += to_string(num / denom);
            num %= denom;
        }

        // Return the resulting string
        return result;
    }
};

int main() {
    printStartBanner("166. Fraction to Recurring Decimal", "O(d)", "O(d)");

    // Get the mode to run in from the user
    string mode = selectMode();

    // Initialize the solution
    Solution s;

    if(isCustomMode(mode)) { // If custom mode selected, run with user input
        customModeSelected();

        // Create holders for numerator and denominator input from user
        string numerator;
        string denominator;
        
        // Loop until user enters quit or exit commands
        while(numerator != "quit" && numerator != "q" && denominator != "quit" && denominator != "q") {
            cout << "Select numerator or press enter to exit: ";
            getline(cin, numerator);


            if(isQuitMode(numerator)) { // User enterd quit, exit program
                return quitModeSelected();
            } else if(isExitMode(numerator)) { // User entered exit or blank string, exit loop
                exitModeSelected();
                break;
            }

            // Get the denominator from user input
            cout << "Select denominator or press enter to exit: ";
            getline(cin, denominator);

            if(isQuitMode(denominator)) { // User enterd quit, exit program
                return quitModeSelected();
            } else if(isExitMode(denominator)) { // User entered exit or blank string, exit loop
                exitModeSelected();
                break;
            }

            // Print the numerator and denominator as well as the result of fractionToDecimal()
            cout << numerator << " / " << denominator << " = " << s.fractionToDecimal(stoi(numerator), stoi(denominator)) << endl;
        }
    } else if(isDemoMode(mode)) { // Demo mode selected, run with demo data
        cout << "Demo mode selected" << endl;

        // Initialize 2D vector of demo fractions
        vector<pair<int, int>> demoData = {{1,4}, {-2,7}, {-1,-3}, {0,20}};

        // Loop over demo data, calculate the repeating decimal result, and print
        for(const auto& division : demoData) {
            cout << division.first << " / " << division.second << " = " << s.fractionToDecimal(division.first, division.second) << endl;
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // Quit or exit mode selected, exit program
        return quitModeSelected();
    } else { // Else, unknown mode. Error
        return unknownModeSelected(mode);
    }

    // Exit program
    return 0;
}