#include <cstdlib>
#include <string>
#include <unordered_map>
#include <vector>
#include <cctype>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <limits>

// Custom utilities header
#include <utilities.h>

// Use standard namespace
using namespace std;

class Spreadsheet {
public:
    unordered_map<string, int> ss;
    int ssRows;

    /**
     * Initialize the spreadsheet with the given number of rows
     */
    Spreadsheet(int rows) {
        ssRows = rows;
    }
    
    /**
     * Set the given cell in the spreadsheet to the given value
     */
    void setCell(string cell, int value) {
        ss[cell] = value;
    }
    
    /**
     * Reset the given cell in the spreadsheet
     */
    void resetCell(string cell) {
        ss[cell] = 0;
    }
    
    /**
     * Given a formula in the form of =a+b, where a and b are either integers or the names of cells,
     * compute the sum
     */
    int getValue(string formula) {
        vector<string> tokens; // Vector to hold the parsed tokens
        string delim = "+"; // The delimeter to use (+)
        size_t start = 1; // Start parsing the string after the = sign
        size_t end = formula.find(delim); // Find the first occurrence of the delimiter

        while (end != std::string::npos) { // Loop until no more delimiters are found
            tokens.push_back(formula.substr(start, end - start)); // Extract substring
            start = end + delim.length(); // Move start position past the delimiter
            end = formula.find(delim, start); // Find the next delimiter
        }
        tokens.push_back(formula.substr(start, formula.length() - start)); // Add the last token

        // If token is a map cell, use that value. Else, use the value of token
        int arg1 = isalpha(tokens[0][0]) ? ss[tokens[0]] : stoi(tokens[0]);
        int arg2 = isalpha(tokens[1][0]) ? ss[tokens[1]] : stoi(tokens[1]);

        // Return the result of addition
        return arg1 + arg2;
    }
};

/**
 * Main program to run the demo
 */
int main(int argc, char* argv[]) {
    printStartBanner("3484 Design Spreadsheet", "O(1) for set/rest, O(m) for get", "O(n)");

    // Get the mode to run the program in from the user
    string mode = selectMode();

    if(isCustomMode(mode)) { // If mode is custom, run with user-provided data
        customModeSelected();

        // Initialize input string
        string input;

        int rows;
        while(true) {
            cout << "Enter number of rows or press enter to exit: ";
            getline(cin, input);
            toLowercase(input);

            if(isExitMode(input) || isQuitMode(input)) { // If blank, quit, or exit entered, exit program
                return quitModeSelected();
            }

            try {
                rows = stoi(input);
                break;
            } catch(...) { // If conversion fails, print error and exit program
                cout << "Invalid input: " << input << ". Please enter only integers. Skipping..." << endl;
            }
        }

        Spreadsheet ss = Spreadsheet(rows);
        cout << "Spreadsheet initialized with " << rows << " rows" << endl;

        while(true) {
            cout << "Enter a command (initialize, set, reset, get) or press enter to exit: ";
            getline(cin, input);
            toLowercase(input);

            if(input == "initialize" || input == "i") {
                int rows;
                cout << "Enter number of rows or press enter to exit: ";
                getline(cin, input);
                toLowercase(input);

                if(isExitMode(input)) { // If blank or exit entered, exit operation
                    exitModeSelected();
                    continue;
                } else if(isQuitMode(input)) { // If quit entered, exit program
                    return quitModeSelected();
                }

                try {
                    rows = stoi(input);
                } catch(...) { // If conversion fails, print error and exit program
                    cout << "Invalid input: " << input << ". Please enter only integers. Skipping..." << endl;
                    continue;
                }
                ss = Spreadsheet(rows);
                cout << "Spreadsheet initialized with " << rows << " rows" << endl;
            } else if( input == "set" || input == "s") {
                string cell;
                cout << "Enter cell to set or press enter to exit: ";
                getline(cin, cell);
                toLowercase(cell);
                if(isExitMode(cell)) { // If blank or exit entered, exit operation
                    exitModeSelected();
                    continue;
                } else if(isQuitMode(cell)) { // If quit entered, exit program
                    return quitModeSelected();
                }
                toUppercase(cell);

                int value;
                cout << "Value to use or enter to exit: ";
                getline(cin, input);
                toLowercase(input);
                if(isExitMode(input)) { // If blank or exit entered, exit operation
                    exitModeSelected();
                    continue;
                } else if(isQuitMode(input)) { // If quit entered, exit program
                    return quitModeSelected();
                }

                try {
                    value = stoi(input);
                } catch(...) { // If conversion fails, print error and exit operation
                    cout << "Invalid input: " << input << ". Please enter only integers. Skipping..." << endl;
                    continue;
                }

                ss.setCell(cell, value);
                cout << "Cell " << cell << " set to value " << value << endl;
            } else if( input == "reset" || input == "r" ) {
                string cell;
                cout << "Cell to reset or enter to exit: ";
                getline(cin, cell);
                toLowercase(cell);
                if(isExitMode(cell)) { // If blank or exit entered, exit operation
                    exitModeSelected();
                    continue;
                } else if(isQuitMode(cell)) { // If quit entered, exit program
                    return quitModeSelected();
                }
                toUppercase(cell);

                ss.resetCell(cell);
                cout << "Cell " << cell << " reset" << endl;
            } else if( input == "get" || input == "g" ) {
                string val1;
                string val2;

                cout << "Enter first value or press enter to exit: ";
                getline(cin, val1);
                toLowercase(val1);
                if(isExitMode(val1)) { // If blank or exit
                    exitModeSelected();
                    continue;
                } else if(isQuitMode(val1)) { // If quit entered, exit program
                    return quitModeSelected();
                }
                toUppercase(val1);

                cout << "Enter second value or press enter to exit: ";
                getline(cin, val2);
                toLowercase(val2);
                if(isExitMode(val2)) { // If blank or exit
                    exitModeSelected();
                    continue;
                } else if(isQuitMode(val2)) { // If quit entered, exit program
                    return quitModeSelected();
                }
                toUppercase(val2);
                
                cout << "The value of =" << val1 << "+" << val2 << " is " << ss.getValue("=" + val1 + "+" + val2) << endl;
            } else if(isExitMode(input)) {
                exitModeSelected();
                break;
            } else if(isQuitMode(mode)) {
                return quitModeSelected();
            } else {
                cout << "Unknown operation: \'" << input << "\'. Skipping..." << endl;
            }
        }
        cout << "Demo ended" << endl;
    } else if(isDemoMode(mode)) { // If demo mode, run with demo data
        demoModeSelected();

        int rows = 5;
        Spreadsheet ss = Spreadsheet(rows);
        cout << "Spreadsheet initialized with " << rows << " rows" << endl;
        ss.setCell("A1", 10);
        cout << "Cell A1 set to 10" << endl;
        ss.setCell("A2", 5);
        cout << "Cell A2 set to 5" << endl;
        cout << "A1 + A2 = " << ss.getValue("=A1+A2") << endl;
        ss.resetCell("A2");
        cout << "Cell A2 reset" << endl;
        cout << "A1 + A2 = " << ss.getValue("=A1+A2") << endl;
        cout << "5 + 10 = " << ss.getValue("=5+10") << endl;
        cout << "A1 + 10 = " << ss.getValue("=A1+10") << endl;
    } else if(isExitMode(mode) || isQuitMode(mode)) { // If exit or quit selected, exit program
        return quitModeSelected();
    } else { // Else, unknown mode selected, error
        return unknownModeSelected(mode);
    }
    return 0;
}