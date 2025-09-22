#include <cstdlib>
#include <string>
#include <unordered_map>
#include <vector>
#include <cctype>
#include <iostream>
#include <sstream>
#include <algorithm>

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
    cout << "Design Spreadsheet Demo" << endl << endl;

    cout << "Select mode (custom or demo): ";
    string mode;
    cin >> mode;
    transform(mode.begin(), mode.end(), mode.begin(), ::tolower);

    if(mode == "custom" || mode == "c") {
        cout << "Custom mode selected" << endl;

        int rows;
        cout << "Number of rows: ";
        cin >> rows;
        Spreadsheet ss = Spreadsheet(rows);
        cout << "Spreadsheet initialized with " << rows << " rows" << endl;

        string input;
        while(input != "quit" || input != "q") {
            cout << "Enter a command (initialize, set, reset, get): ";
            cin >> input;
            if(input == "initialize" || input == "i") {
                int rows;
                cout << "Number of rows: ";
                cin >> rows;
                ss = Spreadsheet(rows);
                cout << "Spreadsheet initialized with " << rows << " rows" << endl;
            } else if( input == "set" || input == "s") {
                string cell;
                cout << "Cell to set: ";
                cin >> cell;
                transform(cell.begin(), cell.end(), cell.begin(), ::toupper);
                int value;
                cout << "Value to use: ";
                cin >> value;
                ss.setCell(cell, value);
                cout << "Cell " << cell << " set to value " << value << endl;
            } else if( input == "reset" || input == "r" ) {
                string cell;
                cout << "Cell to reset: ";
                cin >> cell;
                transform(cell.begin(), cell.end(), cell.begin(), ::toupper);
                ss.resetCell(cell);
                cout << "Cell " << cell << " reset" << endl;
            } else if( input == "get" || input == "g" ) {
                string val1;
                string val2;
                cout << "First value: ";
                cin >> val1;
                transform(val1.begin(), val1.end(), val1.begin(), ::toupper);
                cout << "Second value: ";
                cin >> val2;
                transform(val2.begin(), val2.end(), val2.begin(), ::toupper);
                cout << "The value of =" << val1 << "+" << val2 << " is " << ss.getValue("=" + val1 + "+" + val2) << endl;
            } else {
                break;
            }
        }
        cout << "Demo ended" << endl;
    } else if(mode == "demo" || mode == "d") {
        cout << "Demo mode selected" << endl;

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
    } else {
        cout << "Invalid mode: " << mode << endl;
    }
    return 0;
}