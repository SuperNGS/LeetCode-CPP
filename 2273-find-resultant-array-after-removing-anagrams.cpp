#include <bits/stdc++.h>
#include <sstream>

// Include custom utilities header
#include <utilities.h>

// Use standard namespace
using namespace std;

class Solution {
private: 
    bool isAnagram(string a, string b) {
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        return a == b;
    }
public:
    vector<string> removeAnagrams(vector<string>& words) {
        // Create a vector to store the answer
        vector<string> answer;

        // Loop through each word provided
        for(const auto& word : words) {

            // If answer is not empty, check for anagram
            if(!answer.empty()) {
                // Get the last word in answer and the current word as a and b
                string a = answer.back(), b = word;
                
                // If a and b are an anagram, skip
                if(isAnagram(a, b)) {
                    continue;
                }
            }

            // Push the word back on answer (either first word or not an anagram of last word)
            answer.push_back(word);
        }

        // Return the answer
        return answer;
    }
};

int main() {
    printStartBanner("2273. Find Resultant Array After Removing Anagrams", "O(N * Klogk)", "O(N)");

    // Initialize the solution
    Solution s;

    // Get the mode to run in from the user
    string mode = selectMode();

    if(isCustomMode(mode)) { // If custom mode selected, run with user input
        customModeSelected();

        // Initialize an input string and loop
        string input;
        while(true) {
            cout << "Enter vector of words as a comma-separated string: ";
            getline(cin, input);
            toLowercase(input);

            if(isExitMode(input)) { // If exit entered, exit loop
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) { // If quit mode entered, exit program
                return quitModeSelected();
            }

            // Tokenize the string into string vector words
            vector<string> words;
            stringstream ss(input);
            string token;
            while(getline(ss, token, ',')) {
                words.push_back(token);
            }

            // If no words entered, skip
            if(words.empty()) {
                cout << "INFO: No words entered. Skipping..." << endl;
            }

            // Calculate the result
            vector<string> result = s.removeAnagrams(words);

            // Print the result
            cout << "Result: ";
            for(const auto& res : result) {
                cout << res << " ";
            }
            cout << endl;
        }
    } else if(isDemoMode(mode)) { // If demo mode selected, run with demo data
        demoModeSelected();

        // Set up 2D vector of sets of demo words to use
        vector<vector<string>> demoWords = {
            {"abba","baba","bbaa","cd","cd"},
            {"a","b","c","d","e"}
        };

        // Loop through the sets of words, print the set, then calculate and print the resulting array
        for(vector<string> words : demoWords) {
            // Print the set of words
            cout << "Running program with words: ";
            for(const auto& word : words) {
                cout << word << " ";
            }
            cout << endl;

            // Calculate the result
            vector<string> result = s.removeAnagrams(words);

            // Print the result
            cout << "Result: ";
            for(const auto& res : result) {
                cout << res << " ";
            }
            cout << endl;

        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // If exit or quit mode selected, exit program
        return quitModeSelected();
    } else { // Else, unknown mode, error
        return unknownModeSelected(mode);
    }

    // Exit program successfully
    return 0;
}