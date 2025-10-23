#include <utilities.h>

using namespace std;

void printStartBanner(const string title) {
    cout << title << " Demo" << endl;
    cout << string(title.length() + 5, '=') << endl;
    cout << endl;
}

void printStartBanner(const string title, const string timeComplexity, const string spaceComplexity) {
    cout << title << " Demo" << endl;
    cout << string(title.length() + 5, '=') << endl;
    cout << "Time Complexity: " << timeComplexity << endl;
    cout << "Space Complexity: " << spaceComplexity << endl;
    cout << endl;
}

string selectMode() {

    // Prompt the user to enter mode and capture input
    string mode;
    cout << "Select mode ([c]ustom, [d]emo, or [q]uit): ";

    getline(cin, mode);

    // Convert the mode to lowercase
    toLowercase(mode);

    // Return the mode parsed from user input
    return mode;
}

bool isCustomMode(const string mode) {
    return customMode.find(mode) != customMode.end();
}

void customModeSelected() {
    cout << "Custom mode selected" << endl;
}

bool isDemoMode(const string mode) {
    return demoMode.find(mode) != demoMode.end();
}

void demoModeSelected() {
    cout << "Demo mode selected" << endl;
}

bool isExitMode(const string mode) {
    return mode.empty() || exitMode.find(mode) != exitMode.end();
}

void exitModeSelected() {
    cout << "Exiting..." << endl;
}

bool isQuitMode(const string mode) {
    return quitMode.find(mode) != quitMode.end();
}

int quitModeSelected() {
    cout << "Quitting..." << endl;
    return 0;
}

int unknownModeSelected(const string mode) {
    cout << "Unknown mode selected: " << mode << endl;
    return -1;
}

void toLowercase(string& input) {
    // Convert the input string to lowercase in-place
    transform(input.begin(), input.end(), input.begin(), ::tolower);
}

void toLowercase(string& input, string& copy) {
    // Resize the copy to match input
    copy.resize(input.size());
    // Convert the input string to lowercase and store it in copy
    transform(input.begin(), input.end(), copy.begin(), ::tolower);
}

void toUppercase(string& input) {
    // Convert the input string to uppercase in-place
    transform(input.begin(), input.end(), input.begin(), ::toupper);
}

void toUppercase(string& input, string& copy) {
    // Resize the copy to match input
    copy.resize(input.size());
    // Convert the input string to uppercase and store it in copy
    transform(input.begin(), input.end(), copy.begin(), ::toupper);
}

vector<int> stringToIntVector(string& input) {
    // Initialize int vector
    vector<int> result;
    // Initialize stringstream on input and string token
    stringstream ss(input);
    string token;

    // Loop over string, tokenize by commas
    while(getline(ss, token, ',')) {
        try { // Attempt to convert token to an int and push back onto result
            result.push_back(stoi(token));
        } catch(...) { // Catch unconvertable type, error and skip
            cout << "ERROR: Invalid input '" << token << "'. Please only enter integers. Skipping..." << endl;
            continue;
        }
    }

    // Return the result
    return result;
}

bool isNumericString(std::string &input)
{
    // Return true if all characters in input are digits, false otherwise
    return all_of(input.begin(), input.end(), ::isdigit);
}
