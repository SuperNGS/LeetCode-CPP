#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>

using namespace std;
class Solution {
private:
    // Helper global, all vowels allowed
    vector<char> vowels = {'a', 'e', 'i', 'o', 'u'};
    /**
     * Helper method, returns a lowercase copy of a given string s
     */
    string lowercase(string s) {
        std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return tolower(c); });
        return s;
    };
    /**
     * Helper method, returns true if c is in vowels and false otherwise
     */
    bool isVowel(char c) {
        return find(vowels.begin(), vowels.end(), c) != vowels.end();
    };
    /**
     * Helper method, checks if vowel replacements cause string a to match string b
     */
    bool vowelMatch(string a, string b) {
        string copy = b;
        for(int i = 0; i < b.length(); i++) {
            if(isVowel(b[i])) {
                for(const auto& vowel : vowels) {
                    copy[i] = vowel;
                    if(a == copy) {
                        return true;
                    }
                    if(copy[i] == a[i]) { 
                        break;
                    }
                }
            }
        }
        return copy == a;
    };
public:
    vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries) {
        // Creates an initial vector of size queries, filling with ""
        vector<string> answer(queries.size(), "");

        // Loop through each query
        for(int i = 0; i < queries.size(); i++) {
            // Set holder variables for exact, case, and vowel match
            string exact_match;
            string case_match;
            string vowel_match;

            // Loop through each word in the wordlist, check if it's an exact, case, or vowel match
            for(const auto& word : wordlist) {
                if(exact_match == "" && word == queries[i]) {
                    exact_match = word;
                    break;
                }
                if(case_match == "" && lowercase(word) == lowercase(queries[i]) ) {
                    case_match = word;
                }
                if(vowel_match == "" && vowelMatch(lowercase(word), lowercase(queries[i]))) {
                    vowel_match = word;
                }
            }

            // Set answer[i] in order of exact, case, or vowel match
            if(exact_match != ""){
                answer[i] = exact_match;
            } else if(case_match != "") {
                answer[i] = case_match;
            } else if(vowel_match != "") {
                answer[i] = vowel_match;
            }
        }

        // Return the answer vector
        return answer;
    }
};

int main() {
    cout << "Vowel Spellchecker Demo" << endl << endl;

    // Initialize the solution
    Solution s = Solution();

    // Prompt user for mode to run in ([c]ustom, [d]emo, or [q]uit)
    string mode;
    cout << "Select mode ([c]ustom, [d]emo, or [q]uit): ";
    cin >> mode;
    transform(mode.begin(), mode.end(), mode.begin(), ::tolower);

    if(mode == "c" || mode == "custom" || mode == "[c]ustom") { // If custom mode, run with user input
        cout << "Custom mode selected" << endl;

        // Set holders for input and a lowercase version of input
        string input;
        string lowerInput;

        // Loop until user enters 'quit', 'q', or '[q]uit'
        while(true) {
            // Get the wordlist comma-separated string from user input
            cout << "Input wordlist as a comma-separated string: ";
            cin >> input;

            // Get a lowercase version of input
            lowerInput.resize(input.size());
            transform(input.begin(), input.end(), lowerInput.begin(), ::tolower);

            // If lowercased input is 'quit', 'q', or '[q]uit', exit program
            if(lowerInput == "quit" || lowerInput == "q" || lowerInput == "[q]uit") {
                break;
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
            cin >> input;

            // Get a lowercase version of input
            lowerInput.resize(input.size());
            transform(input.begin(), input.end(), lowerInput.begin(), ::tolower);

            // If lowercased input is 'quit', 'q', or '[q]uit', exit program
            if(lowerInput == "quit" || lowerInput == "q" || lowerInput == "[q]uit") {
                break;
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
                    cout << "NO-MATCH";
                } else {
                    cout << res << " ";
                }
            }
            cout << endl;
        }
    } else if(mode == "d" || mode == "demo" || mode == "[d]emo") { // If demo mode, run with demo data
        cout << "Demo mode selected" << endl;

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
                    cout << "NO-MATCH";
                } else {
                    cout << res << " ";
                }
            }
            cout << endl;
        }

    } else if(mode == "q" || mode == "quit" || mode == "[q]uit") { // If quit mode, exit the program
        cout << "Quitting..." << endl;
        return 0;
    } else { // Else mode is unknown, error
        cout << "Invalid mode: " << mode << endl;
        return -1;
    }
    // Exit the program
    return 0;
}