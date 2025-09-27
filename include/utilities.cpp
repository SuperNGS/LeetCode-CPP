#include <utilities.h>

using namespace std;

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

void customModeSelected() {
    cout << "Custom mode selected" << endl;
}

void demoModeSelected() {
    cout << "Demo mode selected" << endl;
}

void exitModeSelected() {
    cout << "Exiting..." << endl;
}

int quitModeSelected() {
    cout << "Quitting..." << endl;
    return 0;
}

int unknownModeSelected(string mode) {
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