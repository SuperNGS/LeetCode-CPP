#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <unordered_map>

// Custom utilities header
#include <utilities.h>


// Use std namespace
using namespace std;
class Solution {
private:
    /**
     * Helper method, returns a lowercase copy of a given string s
     */
    string lowercase(string s) {
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        return s;
    };
    /**
     * Helper method, replaces vowels in a given string with *
     */
    string devowel(string s) {
        string res = lowercase(s);
        for(auto& c : res) {
            if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                c = '*';
            }
        }
        return res;
    }
public:
    vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries) {
        // Initialize the answer vector to hold results of spellchecker
        vector<string> answer;

        // Create hash set for exact matches
        unordered_set<string> exact_match(wordlist.begin(), wordlist.end());
        // Create hash maps for case and vowel matches
        unordered_map<string, string> case_map;
        unordered_map<string, string> vowel_map;

        // Loop through each word in the wordlist, add to maps
        for(const auto& word : wordlist) {
            // Create lowercase and devoweled versions of the word
            string lower_word = lowercase(word);
            string devoweled_word = devowel(word);

            // If lower_word is not already in case_map, add it
            if(case_map.find(lower_word) == case_map.end()) {
                case_map[lower_word] = word;
            }
            // If devoweled_word is not already in vowel_map, add it
            if(vowel_map.find(devoweled_word) == vowel_map.end()) {
                vowel_map[devoweled_word] = word;
            }
        }
        
        // Loop through each query
        for(const auto& query : queries) {
            if(exact_match.count(query)) { // If exact match, set answer[i] to query
                answer.push_back(query);
                continue;
            } else if(case_map.count(lowercase(query))) { // Else if case match, set answer[i] to case_map[lowercase(query)]
                answer.push_back(case_map[lowercase(query)]);
                continue;
            } else if(vowel_map.count(devowel(query))) { // Else if vowel match, set answer[i] to vowel_map[devowel(query)]
                answer.push_back(vowel_map[devowel(query)]);
                continue;
            } else { // Else no match, set answer[i] to ""
                answer.push_back("");
            }
        }

        // Return the answer vector
        return answer;
    }
};

int main() {
    printStartBanner("966. Vowel Spellchecker", "O(nL+qL)", "O(nL+qL)");

    // Initialize the solution
    Solution s;

    // Prompt user for mode to run in ([c]ustom, [d]emo, or [q]uit)
    string mode = selectMode();

    if(isCustomMode(mode)) { // If custom mode, run with user input
        customModeSelected();

        // Set holders for input and a lowercase version of input
        string input;
        string lowerInput;

        // Loop until user enters 'quit', 'q', or '[q]uit'
        while(true) {
            customModeSelected();
            
            // Get the wordlist comma-separated string from user input
            cout << "Input wordlist as a comma-separated string or press enter to exit: ";
            getline(cin, input);

            // Get a lowercase version of input
            toLowercase(input, lowerInput);

            if(input.empty() || isExitMode(lowerInput)) { // If input is exit, break loop
                exitModeSelected();
                break;
            } else if(isQuitMode(lowerInput)) {  // If input is quit, exit program
                return quitModeSelected();
            }

            // Break the user input into the wordlist vector
            vector<string> wordlist;
            stringstream ssw(input);
            string word;
            cout << "Initializing with wordlist: ";
            while(getline(ssw, word, ',')) {
                cout << word << " ";
                wordlist.push_back(word);
            }
            cout << endl;

            // Get the querylist comma-separated string from user
            cout << "Input querylist as a comma-separated string: ";
            getline(cin, input);

            // Get a lowercase version of input
            toLowercase(input, lowerInput);

            if(input.empty() || isExitMode(lowerInput)) { // If input is exit, break loop
                exitModeSelected();
                break;
            } else if(isQuitMode(lowerInput)) {  // If input is quit, exit program
                return quitModeSelected();
            }

            // Break the input string into the querylist vector
            vector<string> querylist;
            stringstream ssq(input);
            string query;
            cout << "Initializing with querylist: ";
            while(getline(ssq, query, ',')) {
                cout << query << " ";
                querylist.push_back(query);
            }
            cout << endl;

            // Run the program with the user-provided wordlist and querylist
            vector<string> results = s.spellchecker(wordlist, querylist);

            // Print the results of running the program
            cout << "Results: ";
            for(const auto& res : results) {
                if(res.empty()) {
                    cout << "NO-MATCH ";
                } else {
                    cout << res << " ";
                }
            }
            cout << endl;
        }
    } else if(isDemoMode(mode)) { // If demo mode, run with demo data
        demoModeSelected();

        // Set a 2D vector of wordlists to use
        vector<vector<string>> wordLists = 
                                        {
                                            {"yellow"},
                                            {"zeo","Zuo"},
                                            {"KiTe","kite","hare","Hare"}
                                        };

        // Set a 2D vector of querylists to use
        vector<vector<string>> queryLists = 
                                        {
                                            {"YellOw"},
                                            {"zuo"},
                                            {"kite","Kite","KiTe","Hare","HARE","Hear","hear","keti","keet","keto"}
                                        };

        // Loop over all wordlists and querylists
        for(int i = 0; i < wordLists.size(); i++) {
            // Print the wordlist
            cout << "Wordlist: ";
            for(const auto& word : wordLists[i]) {
                cout << word << " ";
            }
            cout << endl;

            // Print the queries
            cout << "Queries: ";
            for(const auto& query : queryLists[i]) {
                cout << query << " ";
            }
            cout << endl;

            // Calculate the result of calling spellChecker() with demo data
            vector<string> results = s.spellchecker(wordLists[i], queryLists[i]);

            // Print the results
            cout << "Results: ";
            for(const auto& res : results) {
                if(res.empty()) {
                    cout << "NO-MATCH ";
                } else {
                    cout << res << " ";
                }
            }
            cout << endl;
        }

    } else if(isExitMode(mode) || isQuitMode(mode)) { // If quit or exit mode, exit the program
        return quitModeSelected();
    } else { // Else mode is unknown, error
        return unknownModeSelected(mode);
    }

    // Exit the program
    return 0;
}