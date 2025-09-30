#include <cstdlib>
#include <unordered_map>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

// Custom utilities header
#include <utilities.h>

// Use standard namespace
using namespace std;

class Solution {
    /**
    Helper method, returns true if character is a vowel and false otherwise
    */
    bool isVowel(char v) {
        return (0x208222>>(v&0x1f))&1;
    }
public:
    int maxFreqSum(string s) {
        // Initialize hash maps for vowels and consonants
        unordered_map<char, int> vowels;
        unordered_map<char, int> consonants;
        
        // Loop through characters in string, sort into vowels and consonants 
        // while tracking how frequently they appear
        for(int i = 0; i < s.length(); i++) {
            if( isVowel(s[i]) ) {
                vowels[s[i]]++;
            } else {
                consonants[s[i]]++;
            }
        }

        // Loop through the vowels map, tracking the most frequent vowel
        int maxVowel = 0;
        for (const auto& vowel : vowels) {
            if (vowel.second > maxVowel) {
                maxVowel = vowel.second;
            }
        }

        // Loop through the consonant map, tracking the most frequent consonant
        int maxConsonant = 0;
        for(const auto& consonant : consonants) {
            if(consonant.second > maxConsonant) {
                maxConsonant = consonant.second;
            }
        }

        // Return the sum of the most frequent vowel and consonant appearances
        return maxVowel + maxConsonant;

    }
};

int main() {
    printStartBanner("3541 Find Most Frequent Vowel and Consonant", "O(n)", "O(1)");
    
    // Initialize solution
    Solution s;

    // Get the mode to run the program in (custom, demo, or quit) from the user
    string mode = selectMode();

    if(isCustomMode(mode)) { // If mode is custom, run with user-provided data
        customModeSelected();

        // Create holder variables for input and a lowercase version of inpiut
        string input;
        string lowerInput;

        // Loop until user enters blank input, quit, or exit
        while(true) {
            // Get the word to calculate max frequency sum from user
            cout << "Select word to calculate max frequency sum or press enter to exit: ";
            getline(cin, input);

            // Get lowercase version of input
            toLowercase(input, lowerInput);

            if(isExitMode(input)) { // If no input entered or exit mode selected, break loop
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) { // If quit mode selected, exit program
                return quitModeSelected();
            }

            // Calculate max frequency sum and print
            cout << "Max frequency sum of " << input << " is " << s.maxFreqSum(input) << endl;
        }
    } else if(isDemoMode(mode)) { // If mode is demo, run with demo data
        demoModeSelected();

        // Initialize string vector of demo words to use
        vector<string> words = {"successes", "aeiaeia", "tnkdlyyhzhpfdhlatnnuxetutiuxf"};

        // Loop through each word of demo data, calculate max frequency sum, and print
        for(const auto& word : words) {
            cout << "Word: " << word << endl;
            cout << "Max frequency Sum: " << s.maxFreqSum(word) << endl;
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // If mode is exit or quit, exit program
        return quitModeSelected();
    } else { // Else, unknown mode, error
        return unknownModeSelected(mode);
    }

    // Exit program
    return 0;
}