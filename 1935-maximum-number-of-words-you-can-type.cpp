#include <cstdlib>
#include <string>
#include <vector>
#include <unordered_set>
#include <sstream>
#include <algorithm>

// Custom utilities header
#include <utilities.h>

// Use std namespace
using namespace std;

class Solution {
private:
    vector<string> splitString(const string& input) {
        // Initialize vector and stringstream to split input by spaces
        vector<string> words;
        stringstream ss(input);
        string word;

        // Continue splitting input until no tokens left
        while(ss >> word) {
            words.push_back(word);
        }

        // Return the string vector of words parsed out from input
        return words;
    }
public:
    int canBeTypedWords(string text, string brokenLetters) {
        // Convert text string into a vector of strings (one per word)
        vector<string> words = splitString(text);
        // Convert brokenLetters string into an unordered set of characters (one per letter)
        unordered_set<char> letters(brokenLetters.begin(), brokenLetters.end());
        
        int count = 0;

        // Loop through each word, scan for broken letters
        for(const auto& word : words) {
            // Initialize flag to false (word doesn't contain broken letters)
            bool brokenLetterFound = false;
            // Loop through each character of the word and check against broken letters
            for(const auto& character : word) {
                // If broken letter found, set flag to true and break
                if(letters.count(character)) {
                    brokenLetterFound = true;
                    break;
                }
            }
            // If no broken letters found, increment count
            if(!brokenLetterFound) {
                count++;
            }
        }

        // Return the number of words that can be types
        return count;
    }
};

int main() {
    printStartBanner("1935. Maximum Number of Words You Can Type", "O(n)", "O(n+m)");

    // Initialize solution
    Solution s;

    // Prompt user to select mode
    string mode = selectMode();

    if(isCustomMode(mode)) { // Custom mode selected, run with user input
        customModeSelected();

        // Initialize input string + lowercase copy and begin loop
        string input;
        string lowerInput;
        while(true) {
            // Get the list of words to check from the user
            cout << "Enter words to check: ";
            getline(cin, input);
            toLowercase(input, lowerInput);

            if(isExitMode(lowerInput)) { // Exit mode selected, break loop
                exitModeSelected();
                break;
            } else if(isQuitMode(lowerInput)) { // Quit mode selected, exit program
                return quitModeSelected();
            }

            string words = input;

            // Get the broken letters to check against from the user
            cout << "Enter broken letters: ";
            getline(cin, input);
            toLowercase(input, lowerInput);

            if(isExitMode(lowerInput)) { // Exit mode selected, break loop
                exitModeSelected();
                break;
            } else if(isQuitMode(lowerInput)) { // Quit mode selected, exit program
                return quitModeSelected();
            }

            string brokenLetters = input;

            // Calculate and print out the number of words that can be typed
            cout << "Number of words that can be typed: " << s.canBeTypedWords(words, brokenLetters) << endl;
        }
    } else if(isDemoMode(mode)) { // Demo mode selected, run with demo data
        demoModeSelected();

        // Create a vector of pairs (word, brokenLetters) to run demo with
        vector<pair<string, string>> demoData = {
            {"hello world", "ad"},
            {"leet code", "lt"},
            {"leet code", "e"}
        };

        // Loop through the pairs of demo data, print them, then calculate and print the result of canBeTypedWords()
        for(const auto& data : demoData) {
            cout << "Running words: " << data.first << endl;
            cout << "With broken letters: " << data.second << endl;
            cout << "Number of words that can be typed = " << s.canBeTypedWords(data.first, data.second) << endl;
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // Exit or quit mode selected, exit program
        return quitModeSelected();
    } else { // Else, unknown mode selected, error
        return unknownModeSelected(mode);
    }

    // Exit program successfully
    return 0;
}