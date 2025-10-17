// Include custom utilities header
#include <utilities.h>

// Use standard namespace
using namespace std;

class Solution {
private:
    /**
    Helper function, determines if two vectors don't share any common value
    */
    bool noValuesMatch(const vector<int>& vec1, const vector<int>& vec2) {
        // If any element in vec1 is found in vec2, then there's a match.
        // We want to return true if *no* values match, so we negate the result of any_of.
        return !any_of(vec1.begin(), vec1.end(), [&](int val) {
            return find(vec2.begin(), vec2.end(), val) != vec2.end();
        });
    }
public:
    int minimumTeachings(int n, vector<vector<int>>& languages, vector<vector<int>>& friendships) {

        // Track friendships where a common language isn't shared
        vector<vector<int>> unmatchedFriendships;

        // Loop over each friendship
        for (const auto& friendship : friendships) {

            // Get the users in friendship, u and v
            int u = friendship[0];
            int v = friendship[1];

            // Get the languages that users u and v respectively know
            vector<int> uLanguages = languages[u - 1];
            vector<int> vLanguages = languages[v - 1];


            // If u and v don't share a common language, add them to the unmatchedFriendships vector
            if(noValuesMatch(uLanguages, vLanguages)) {
                unmatchedFriendships.push_back(friendship);
            }
        }

        // If all friendships are matched, return 0
        if(unmatchedFriendships.size() == 0) {
            return 0;
        }

        // Create a set containing all unique unmatched users
        set<int> unmatchedUsersSet;
        for (const auto& row : unmatchedFriendships) {
            for (int element : row) {
                unmatchedUsersSet.insert(element);
            }
        }

        // Convert the set to a vector
        vector<int> unmatchedUsers(unmatchedUsersSet.begin(), unmatchedUsersSet.end());

        // For each unmatched user, track which languages they know
        vector<int> knownLanguage(n+1, 0);
        for(const auto& unmatched : unmatchedUsers) {
                for(const auto& language : languages[unmatched - 1]) {
                    knownLanguage[language] += 1;
                }
        }

        // Retrieve how many users know the most well known language 
        vector<int>::iterator max = max_element(knownLanguage.begin(), knownLanguage.end());
        int max_value = *max;

        // Return the amount of users who need to be taught the common language
        return unmatchedUsers.size() - max_value;
    }
};

int main() {
    printStartBanner("1733. Minimum Number of People to Teach", "O(F∗L+M∗L+N)", "O(F+N)");

    // Initialize the solution
    Solution s;

    // Get mode to run program in from the user
    string mode = selectMode();

    if(isCustomMode(mode)) { // If custom mode, run with user input
        customModeSelected();

        // Initialize input string and loop
        string input;
        while(true) {
            cout << "Enter number of languages n: ";
            getline(cin, input);
            toLowercase(input);

            // If exit or quit entered, exit program
            if(isExitMode(input) || isQuitMode(input)) {
                return quitModeSelected();
            }

            // Attempt to convert input to integer n
            int n;
            try { // Try to convert the input to an int
                n = stoi(input);
            } catch(...) { // Catch unconvertable type, error and skip
                cout << "ERROR: Invalid input '" << input << "'. Please only enter an integer. Skipping..." << endl;
                continue;
            }

            // Initialize 2D languages vector, counter for current user, and loop to get languages users know
            vector<vector<int>> languages;
            int user = 1;
            while(true) {
                cout << "Enter the languages that user " << user << " knows as a comma-separated string or press enter to exit: ";
                getline(cin, input);
                toLowercase(input);

                if(isExitMode(input)) { // Exit selected, break loop
                    exitModeSelected();
                    break;
                } else if(isQuitMode(input)) { // Quit selected, exit program
                    return quitModeSelected();
                }

                // Attempt to convert input to int vector langs
                vector<int> langs = stringToIntVector(input);

                // Loop through all entered languages, if invalid language entered, erase it
                for(int i = 0; i < langs.size(); i++) {
                    if(langs[i] < 1 || langs[i] > n) {
                        cout << "ERROR: Language " << langs[i] << " is invalid (either less than 1 or greater than n). Erasing..." << endl;
                        langs.erase(langs.begin() + i);
                    }
                }

                // If langs empty, skip
                if(langs.empty()) {
                    cout << "INFO: No languages entered. Please enter at least one language. Skipping..." << endl;
                    continue;
                }

                // Push langs back onto languages
                languages.push_back(langs);

                // Increment user
                user++;
            }

            // Initialize 2D friendships vector and loop to get frienships between users
            vector<vector<int>> frienships;
            while(true) {
                cout << "Enter a friendship between two users as a comma-separated string or press enter to exit: ";
                getline(cin, input);
                toLowercase(input);

                if(isExitMode(input)) { // Exit selected, break loop
                    exitModeSelected();
                    break;
                } else if(isQuitMode(input)) { // Quit selected, exit program
                    return quitModeSelected();
                }

                // Attempt to convert input to int vector langs
                vector<int> friends = stringToIntVector(input);
                

                // If no values entered, skip
                if(friends.empty()) {
                    cout << "INFO: No friendship entered. Skipping..." << endl;
                    continue;
                }

                // If friends vector doesn't contain two elements, skip
                if(friends.size() != 2) {
                    cout << "ERROR: Friendship must contain two values, but " << friends.size() << " entered. Skipping..." << endl;
                    continue;
                }
                
                // If friends vector contains an invalid user (less than 1 or greater than size of languages), skip
                if(friends[0] < 1 || friends[0] > languages.size()) {
                    cout << "ERROR: Invalid user " << friends[0] << ". Must be 1 or greater and less than size of languages. Skipping..." << endl;
                    continue;
                } else if(friends[1] < 1 || friends[1] > languages.size()) {
                    cout << "ERROR: Invalid user " << friends[1] << ". Must be 1 or greater and less than size of languages. Skipping..." << endl;
                    continue;
                }

                // Push friends back onto friendships
                frienships.push_back(friends);
            }

            // Calculate the result
            cout << "The minimum number of people to teach is " << s.minimumTeachings(n, languages, frienships) << endl;
        }
    } else if(isDemoMode(mode)) { // If demo mode, run with demo data
        demoModeSelected();

        // Initialize int vector demoNValues, number of languages per demo
        vector<int> demoNValues = {2, 3};
        // Initialize 3D int vector demoLanguages, sets of  languages the j'th user knows
        vector<vector<vector<int>>> demoLanguages = {
            {
                {1}, {2}, {1,2}
            },
            {
                {2}, {1,3}, {1,2}, {3}
            }
        };
        // Initialize 3D int vector demoFrienships, sets of Friendships between user uj and vj
        vector<vector<vector<int>>> demoFrienships = {
            {
                {1,2}, {1,3}, {2,3}
            },
            {
                {1,4}, {1,2}, {3,4}, {2,3}
            }
        };

        // Loop through each set of demo data, print it, then calculate the result and print
        for(int i = 0; i < demoNValues.size(); i++) {
            // Print the n value
            cout << "Running program with n value: " << demoNValues[i] << endl;
            
            // Print the languages
            cout << "Running program where..." << endl;
            for(int j = 0; j < demoLanguages[i].size(); j++) {
                cout << "\tUser " << j << " knows language: ";
                for(const auto& lan : demoLanguages[i][j]) {
                    cout << lan << " ";
                }
                cout << endl;
            }

            // Print the friendships
            cout << "Running program where..." << endl;
            for(int j = 0; j < demoFrienships[i].size(); j++) {
                cout << "\tUser " << demoFrienships[i][j][0] << " and " << demoFrienships[i][j][1] << " are friends" << endl;
            }

            // Calculate and print the minimum number of users we have to teach
            cout << "The minimum number of users to teach is " << s.minimumTeachings(demoNValues[i], demoLanguages[i], demoFrienships[i]) << endl;
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // If exit or quit mode, exit program
        return quitModeSelected();
    } else { // Else, unknown mode, error and exit
        return unknownModeSelected(mode);
    }

    // Exit program successfully
    return 0;
}