#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

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
    cout << "Sort Vowels in a String Demo" << endl << endl;

    // Get the mode to run in from the user
    string mode;
    cout << "Select mode (custom or demo): ";
    cin >> mode;
    transform(mode.begin(), mode.end(), mode.begin(), ::tolower);

    // Initialize the solution
    Solution s = Solution();

    if(mode == "custom" || mode == "c") { // If custom or c selected, run with user input
        // Set variables to hold user input as well as the lowercase version
        string input;
        string lowerInput;

        // Loop until user inputs "quit" or "q"
        while(input != "quit" && input != "q") {
            // Get word to use from the user
            cout << "Select word to sort vowels: ";
            cin >> input;

            // Get the lowercase version of input to check for quit command
            lowerInput.resize(input.size());
            transform(input.begin(), input.end(), lowerInput.begin(), ::tolower);


            // If lowercase input is "quit" or "q", exit the loop
            if(lowerInput == "quit" || lowerInput == "q") {
                break;
            }

            // Calculate the sorted vowels version of input
            cout << input << " with vowels sorted is " << s.sortVowels(input) << endl;
        }
    } else if(mode == "demo" || mode == "d") { // If demo or d selected, run with demo data
        // Initialize demo data as a vector of strings
        vector<string> words = {"lEetcOde", "lYmpH", "hElLowOrLd"};
        
        // For each string of demo data, sort the vowels and print
        for(const auto& word : words) {
            cout << word << " with vowels sorted is " << s.sortVowels(word) << endl;
        }
    } else if(mode == "quit" || mode == "q") { // If quit or q selected, exit the program
        cout << "Quitting..." << endl;
        return 0;
    } else { // If none of the above selected, unknown mode. Error
        cout << "Invalid mode: " << mode << endl;
        return -1;
    }

    return 0;

}