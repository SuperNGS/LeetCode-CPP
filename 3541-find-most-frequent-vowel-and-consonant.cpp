#include <cstdlib>
#include <unordered_map>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

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
    cout << "Find Most Frequent Vowel and Consonant Demo" << endl << endl;
    
    // Initialize solution
    Solution s = Solution();

    // Get the mode to run the program in (custom, demo, or quit) from the user
    string mode;
    cout << "Select mode ([c]ustom, [d]emo, or [q]uit): ";
    cin >> mode;
    transform(mode.begin(), mode.end(), mode.begin(), ::tolower);

    if(mode == "custom" || mode == "c" || mode == "[c]ustom") { // If mode is custom, run with user-provided data
        cout << "Custom mode selected" << endl;

        // Create holder variables for input and a lowercase version of inpiut
        string input;
        string lowerInput;

        // Loop until user enters 'quit', 'q', or '[q]uit'
        while(true) {
            // Get the word to calculate max frequency sum from user
            cout << "Select word to calculate max frequency sum: ";
            cin >> input;

            // Get lowercase version of input
            lowerInput.resize(input.size());
            transform(input.begin(), input.end(), lowerInput.begin(), ::tolower);

            // If lower input is 'quit', 'q', or '[q]uit', exit
            if(lowerInput == "quit" || lowerInput == "q" || lowerInput == "[q]uit") {
                break;
            }

            // Calculate max frequency sum and print
            cout << "Max frequency sum of " << input << " is " << s.maxFreqSum(input) << endl;
        }
    } else if(mode == "demo" || mode == "d" || mode == "[d]emo") { // If mode is demo, run with demo data
        cout << "Demo mode selected" << endl;

        // Initialize string vector of demo words to use
        vector<string> words = {"successes", "aeiaeia", "tnkdlyyhzhpfdhlatnnuxetutiuxf"};

        // Loop through each word of demo data, calculate max frequency sum, and print
        for(const auto& word : words) {
            cout << "Word: " << word << endl;
            cout << "Max frequency Sum: " << s.maxFreqSum(word) << endl;
        }
    } else if(mode == "quit" || mode == "q" || mode == "[q]uit") { // If mode is quit, exit program
        cout << "Quitting..." << endl;
        return 0;
    } else { // Else, unknown mode, error
        cout << "Invalid mode: " << mode << endl;
        return -1;
    }

    // Exit program
    return 0;
}