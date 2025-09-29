#include <cstdlib>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>

// Custom utilities header
#include <utilities.h>

// Use standard namespace
using namespace std;

class Solution {
private:
   /**
    Helper method, returns true if character is a value and false otherwise
    */
    bool isVowel(char v) {
        return (0x208222>>(v&0x1f))&1;
    }
public:
    bool doesAliceWin(std::string s) {
        // Set initial turn to alice
        string turn = "alice";

        // While the string is not empty, loop
        while(s.length() > 0) {
            // Set trackers for number of vowels in string as well as index of the last and second to last vowel
            int vowels = 0;
            int lastVowelIndex = 0;
            int secondLastVowelIndex = 0;

            // Loop over the string, counting vowels and tracking indexes of last vowel + second to last vowel
            for(int i = 0; i < s.length(); i++) {
                if(isVowel(s[i])) {
                    vowels++;
                    secondLastVowelIndex = lastVowelIndex;
                    lastVowelIndex = i;
                }
            }

            if(vowels == 0) { // If no vowels remain, current player loses
                return turn == "alice" ? false : true;
            } else if( vowels % 2 != 0 ) { // If vowels are odd, alice wins
                return turn == "alice" ? true : false;
            } else if( ((vowels - 1) % 2) > 0 ) { // If vowels are even and greater than 2, split the string based on player move
                if( turn == "alice" ) {
                    s = s.substr(0, secondLastVowelIndex);
                    turn = "bob";
                } else {
                    s = s.substr(0, lastVowelIndex);
                    turn = "alice";
                }
            } else { // Else, alice loses
                return turn == "alice" ? false : true;
            }
        }
        // If alice's turn, she loses. Else, she wins
        return turn == "alice" ? false : true;
    }
};

int main() {
    printStartBanner("3227. Vowels Game in a String", "O(n^2)", "O(n)");

    // Initialize solution
    Solution s;

    // Get mode to run in from user (custom, demo, or quit)
    string mode = selectMode();

    if(isCustomMode(mode)) { // If mode is custom, run with user-provided data
        customModeSelected();

        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Initialize input string + lowercase copy and start loop
        string input;
        string lowerInput;
        while(true) {
            cout << "Enter word to use or press enter to exit: ";
            getline(cin, input);
            toLowercase(input, lowerInput);

            if(isExitMode(lowerInput)) { // If no input entered or exit mode selected, break loop
                exitModeSelected();
                break;
            } else if(isQuitMode(lowerInput)) { // If quit mode selected, exit program
                return quitModeSelected();
            }

            // Print the winner of the vowel game with the provided word
            cout << "Winner of vowel game with word = " << input << ": " << (s.doesAliceWin(input) ? "Alice" : "Bob") << endl;
        }
    } else if(isDemoMode(mode)) { // If mode is demo, run with demo data
        demoModeSelected();

        // Initialize demo data as a vector of words
        vector<string> words = {"leetcoder", "bbcd", "helloworld"};

        // Loop through each word of demo data and print the winner of the vowel game
        for(const auto& word : words) {
            cout << "Winner of vowel game with word = " << word << ": " << (s.doesAliceWin(word) ? "Alice" : "Bob") << endl;
        }
    } else if(isQuitMode(mode)) { // If mode is quit, exit program
        return quitModeSelected();
    } else { // Else, unknown mode, error
        return unknownModeSelected(mode);
    }

    // Exit program
    return 0;
}