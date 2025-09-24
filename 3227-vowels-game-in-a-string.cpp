#include <cstdlib>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

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
    cout << "Vowels Game in a String Demo" << endl << endl;

    string mode;
    cout << "Select mode (custom or demo): ";
    cin >> mode;
    transform(mode.begin(), mode.end(), mode.begin(), ::tolower);

    Solution s = Solution();

    if(mode == "custom" || mode == "c") {
        string input;
        string lowerInput;

        while(true) {
            cout << "Enter word to use: ";
            cin >> input;
            lowerInput.resize(input.size());
            transform(input.begin(), input.end(), lowerInput.begin(), ::tolower);

            if(lowerInput == "quit" || lowerInput == "q") {
                break;
            }

            cout << "Winner of vowel game with word = " << input << ": " << (s.doesAliceWin(input) ? "Alice" : "Bob") << endl;
        }
    } else if(mode == "demo" || mode == "d") {
        vector<string> words = {"leetcoder", "bbcd", "helloworld"};

        for(const auto& word : words) {
            cout << "Winner of vowel game with word = " << word << ": " << (s.doesAliceWin(word) ? "Alice" : "Bob") << endl;
        }
    } else if(mode == "quit" || mode == "q") {
        cout << "Quitting..." << endl;
        return 0;
    } else {
        cout << "Invalid mode: " << mode << endl;
        return -1;
    }

    return 0;
}