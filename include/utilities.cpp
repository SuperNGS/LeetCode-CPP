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

int quitModeSelected() {
    cout << "Quitting..." << endl;
    return 0;
}

int unknownModeSelected(string mode) {
    cout << "Unknown mode selected: " << mode << endl;
    return -1;
}