#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

// Custom utilities header
#include <utilities.h>

// Use standard namespace
using namespace std;

class Solution {
private:
    /**
    Helper method, returns true if character is a vowel and false otherwise
    */
    bool isVowel(char v) {
        return (0x208222>>(v&0x1f))&1;
    }
public:
    string sortVowels(string s) {
        // Initialize a new vector to hold vowels
        vector<char> vowels;

        // Loop over the characters of the string, adding them to vowels if they are a vowel
        for(int i = 0; i < s.length(); i++) {
            if(isVowel(s[i])) {
                vowels.push_back(s[i]);
            }
        }

        // If no vowels, return the initial string
        if(vowels.size() == 0) {
            return s;
        }

        // Sort the vowels
        sort(vowels.begin(), vowels.end());

        // Loop over the string, replacing vowels with the next value from the vowels vector
        int ind = 0;
        for(int i = 0; i < s.length(); i++) {
            if(isVowel(s[i])) {
                s[i] = vowels[ind];
                ind++;
            }
        }

        // Return the string
        return s;
    }
};

int main() {
    printStartBanner("2785. Sort Vowels in a String", "O(n log n)", "O(n)");

    // Initialize the solution
    Solution s;

    // Get the mode to run in from the user
    string mode = selectMode();

    if(isCustomMode(mode)) { // If custom or c selected, run with user input
        customModeSelected();

        // Set variables to hold user input as well as the lowercase version, loop
        string input;
        string lowerInput;
        while(true) {
            // Get word to use from the user
            cout << "Select word to sort vowels or press enter to exit: ";
            getline(cin, input);
            toLowercase(input, lowerInput);

            if(isExitMode(lowerInput)) { // If no input entered or exit mode selected, break loop
                exitModeSelected();
                break;
            } else if(isQuitMode(lowerInput)) { // If quit mode selected, exit program
                return quitModeSelected();
            }

            // Calculate the sorted vowels version of input
            cout << input << " with vowels sorted is " << s.sortVowels(input) << endl;
        }
    } else if(isDemoMode(mode)) { // If demo mode selected, run with demo data
        demoModeSelected();

        // Initialize demo data as a vector of strings
        vector<string> words = {"lEetcOde", "lYmpH", "hElLowOrLd"};
        
        // For each string of demo data, sort the vowels and print
        for(const auto& word : words) {
            cout << word << " with vowels sorted is " << s.sortVowels(word) << endl;
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // If exit or quit selected, exit the program
        return quitModeSelected();
    } else { // If none of the above selected, unknown mode. Error
        return unknownModeSelected(mode);
    }

    return 0;

}