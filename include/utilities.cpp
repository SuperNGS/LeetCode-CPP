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
    cin >> mode;

    // Convert the mode to lowercase
    transform(mode.begin(), mode.end(), mode.begin(), ::tolower);

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
    return exitMode.find(mode) != exitMode.end();
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