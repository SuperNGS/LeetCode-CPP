#include <cstdlib>
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <limits>

// Include custom utilities
#include <utilities.h>

// Use std namespace
using namespace std;

class MovieRentingSystem {
private:
    map<int, set<pair<int, int>>> unrentedMovies; // Key Movie = {price, shop}
    set<tuple<int, int, int>> rentedMovies; // {price, shop, movie}
    map<pair<int, int>, int> prices; // Key {shop, movie} = price
public:
    MovieRentingSystem(int n, vector<vector<int>>& entries) {
        // Loop through all entries
        for(int i = 0; i < entries.size(); i++) {
            // Break entry into components
            int shop = entries[i][0], movie = entries[i][1], price = entries[i][2];

            // Insert entry into unrentedMovies
            unrentedMovies[movie].insert({price, shop});

            // Insert the price information into prices
            prices[{shop, movie}] = price;
        }
    }
    
    vector<int> search(int movie) {
        // Initialize vector to hold shops
        vector<int> shops;

        // Loop through entries for movie, capturing the first five results
        if( unrentedMovies.find(movie) != unrentedMovies.end() ) {
            auto it = unrentedMovies[movie].begin();
            while(it != unrentedMovies[movie].end() && shops.size() < 5) {
                shops.push_back(it->second);
                it++;
            }
        }

        // Return the first five shops
        return shops;
    }
    
    void rent(int shop, int movie) {
        // Get the price
        int price = prices[{shop, movie}];
        
        // Remove from unrented
        unrentedMovies[movie].erase({price, shop});
        
        // Add to rented
        rentedMovies.insert({price, shop, movie});
    }
    
    void drop(int shop, int movie) {
        // Get the price
        int price = prices[{shop, movie}];
        
        // Remove from rented
        rentedMovies.erase({price, shop, movie});
        
        // Add back to unrented
        unrentedMovies[movie].insert({price, shop});
    }
    
    vector<vector<int>> report() {
        // Create a vector to hold report information
        vector<vector<int>> report;

        // Loop through the first five rented movies, adding them to the report
        auto it = rentedMovies.begin();
        while(it != rentedMovies.end() && report.size() < 5) {
            report.push_back({get<1>(*it), get<2>(*it)});
            it++;
        }

        // Return the report
        return report;
    }
};

MovieRentingSystem initMovieRentingSystem() {
    cout << "Initializing MovieRentingSystem" << endl;

    string input;

    // Get number of shops from the user
    cout << "Input number of shops or press enter to exit: ";
    getline(cin, input);
    toLowercase(input);
    
    // If user inputted blank, exit, or quit, exit the program
    if(isExitMode(input) || isQuitMode(input) || input.empty()) {
        exit(quitModeSelected());
    }

    // initialize n
    int n;

    try { // Convert input to int n
        n = stoi(input);
    } catch(...) { // Catch all exceptions
        cout << "ERROR: Invalid input '" << input << "'. Please only enter numbers." << endl;
        return initMovieRentingSystem();
    }

    // Initialize 2D vector of entries and start loop
    vector<vector<int>> entries;
    while(true) {
        // Get comma-seperated string representing an entry (shop, movie, price) from user
        cout << "Enter entry as a comma-seperated string (shop, movie, price) or press enter to exit entries: ";
        getline(cin, input);
        toLowercase(input);

        if(isQuitMode(input)) { // If input is quit, exit program
            exit(quitModeSelected());
        } else if(input.empty() || isExitMode(input)) { // If input is blank exit, break loop
            exitModeSelected();
            break;
        }

        // Tokenize the input and add it to vector representing an entry
        vector<int> entry;
        stringstream ss(input);
        string token;
        while(getline(ss, token, ',')) {
            try { // Try to convert token to int, if fail, print error and continue
                entry.push_back(stoi(token));
            } catch(...) { // Catch all exceptions
                cout << "ERROR: Invalid input '" << token << "'. Please only enter numbers." << endl;
                entry.clear();
                break;
            }
        }

        // If entry does not have exactly three entries, print error and continue
        if(entry.size() != 3) { 
            cout << "ERROR: Invalid input. Please enter exactly three numbers (shop, movie, price)." << endl;
            continue;
        }

        // Print the entry entered
        cout << "Entry: Shop = " << entry[0] << ", Movie = " << entry[1] << ", Price = " << entry[2] << endl;

        // Push the entry onto entries
        entries.push_back(entry);
    }

    // Return an initialized MovieRentingSystem
    return MovieRentingSystem(n, entries);
}

int main() {
    printStartBanner("1912. Design Movie Rental System", "O(n log n) for constructor, O(log n) per operation", "O(n)");

    // Get the mode to run program in from user input
    string mode = selectMode();

    if(isCustomMode(mode)) { // Custom mode selected, run with user input
        customModeSelected();

        // Clear input buffer before taking user input
        cin.ignore(numeric_limits<streamsize>::max(), '\n');    

        // Initialize the movie renting system from user input
        MovieRentingSystem mrs = initMovieRentingSystem();

        cout << "MovieRentingSystem initialized" << endl;

        // Create sets for the different operations
        set<string> initOp = {"init", "[i]nit", "i", "[i]"};
        set<string> rentOp = {"rent", "[r]ent", "r", "[r]"};
        set<string> dropOp = {"drop", "[d]rop", "d", "[d]"};
        set<string> repoOp = {"report", "[rep]ort", "rep", "[rep]"};

        // Initialiaze input holder and loop until exit or quit
        string input;
        while(true) {
            cout << "Select operation ([i]nit, [r]ent, [d]rop, [rep]ort, or press enter to exit): ";
            getline(cin, input);
            toLowercase(input);

            if(input.empty() || isExitMode(input)) { // If blank input or exit, break loop
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) { // If quit entered, exit program
                return quitModeSelected();
            }

            if(initOp.find(input) != initOp.end()) { // Init operation selected
                mrs = initMovieRentingSystem();
                cout << "MovieRentingSystem initialized" << endl;
            } else if(rentOp.find(input) != rentOp.end()) { // Rent operation selected
                // Get the comma-seperated movie to rent string (shop, movie) from user
                cout << "Enter movie to rent as a comma-seperated string (shop, movie): ";
                getline(cin, input);
                toLowercase(input);

                // If blank or exit entered, break loop
                if(input.empty() || isExitMode(input)) {
                    break;
                } else if(isQuitMode(input)) { // If quit entered, exit program
                    return quitModeSelected();
                }

                // Tokenize the input string into int vector [shop, movie]
                vector<int> rent;
                stringstream ss(input);
                string token;
                while(getline(ss, token, ',')) {
                    try { // Try to convert token to int, if fail, print error and continue
                        rent.push_back(stoi(token));
                    } catch(...) { // Catch all exceptions
                        cout << "ERROR: Invalid input '" << token << "'. Please only enter numbers." << endl;
                        rent.clear();
                        break;
                    }
                }

                // If rent vector does not have exactly two entries, print error and continue
                if(rent.size() != 2) { 
                    cout << "ERROR: Invalid input. Please enter exactly two numbers (shop, movie)." << endl;
                    continue;
                }

                // Rent the movie from the shop
                mrs.rent(rent[0], rent[1]);
                cout << "Rented movie " << rent[1] << " from shop " << rent[0] << endl;
            } else if(dropOp.find(input) != dropOp.end()) { // Drop operation selected
                // Get the comma-seperated movie to drop string (shop, movie) from user
                cout << "Enter movie to drop as a comma-seperated string (shop, movie): ";
                getline(cin, input);
                toLowercase(input);

                if(input.empty() || isExitMode(input)) { // If blank or exit entered, break loop
                    break;
                } else if(isQuitMode(input)) { // If quit entered, exit program
                    return quitModeSelected();
                }

                // Tokenize the input string into int vector [shop, movie]
                vector<int> drop;
                stringstream ss(input);
                string token;
                while(getline(ss, token, ',')) {
                    try { // Try to convert token to int, if fail, print error and continue
                        drop.push_back(stoi(token));
                    } catch(...) { // Catch all exceptions
                        cout << "ERROR: Invalid input '" << token << "'. Please only enter numbers." << endl;
                        drop.clear();
                        break;
                    }
                }

                // If drop vector does not have exactly two entries, print error and continue
                if(drop.size() != 2) { 
                    cout << "ERROR: Invalid input. Please enter exactly two numbers (shop, movie)." << endl;
                    continue;
                }

                // Drop the movie off at the shop
                mrs.drop(drop[0], drop[1]);
                cout << "Dropped off movie " << drop[1] << " at shop " << drop[0] << endl;
            } else if(repoOp.find(input) != repoOp.end()) { // Report operation selected
                cout << "Generated report of top 5 rented movies:" << endl;

                // Get the 2D vector report from MovieRentingSystem
                vector<vector<int>> report = mrs.report();

                // Print out each entry in the report
                if(report.empty()) {
                    cout << "NONE" << endl;
                }
                for(const auto& rep : report) {
                    cout << "\tShop = " << rep[0] << ", Movie = " << rep[1] << endl;
                }
            } else if(quitMode.find(input) != quitMode.end() || exitMode.find(input) != exitMode.end()) { // Quit mode selected, break loop
                break;
            } else { // Else, invalid operation entered
                cout << "Invalid operation: " << input << endl;
            }
        }
    } else if(isDemoMode(mode)) { // Demo mode selected, run with demo data
        demoModeSelected();

        // Set demo number of shops n
        int n = 3;
        // Set demo entries (2D vector of {shop, movie, price})
        vector<vector<int>> entries =   {
                                            {0, 0, 10},
                                            {0, 1, 5},
                                            {0, 2, 8},
                                            {1, 1, 7},
                                            {1, 3, 6},
                                            {2, 1, 8},
                                            {2, 2, 5},
                                            {2, 4, 6}
                                        };

        // Print out demo data
        cout << "Initializing movie rental system with " << n << " shops and entries:" << endl;
        for(const auto& entry : entries) {
            cout << "\tShop = " << entry[0] << ", Movie = " << entry[1] << endl; 
        }

        // Initialize the movie renting system with demo data
        MovieRentingSystem mrs = MovieRentingSystem(n, entries);

        // Test search
        vector<int> search = mrs.search(1);
        cout << "Shops with movie 1: ";
        if(search.empty()) {
            cout << "NONE";
        }
        for(const auto& shop : search) {
            cout << shop << " ";
        } 
        cout << endl;

        // Test report
        vector<vector<int>> report = mrs.report();
        cout << "Currently rented movies:" << endl;
        if(report.empty()) {
            cout << "NONE" << endl;
        }
        for(const auto& rep : report) {
            cout << "\tShop = " << rep[0] << ", Movie = " << rep[1] << endl;
        }

        // Test rent
        cout << "Renting movie 0 from shop 0" << endl;
        mrs.rent(0, 0);
        cout << "Renting movie 1 from shop 2" << endl;
        mrs.rent(2, 1);
        cout << "Renting movie 1 from shop 1" << endl;
        mrs.rent(1, 1);

        // Test report again
        report = mrs.report();
        cout << "Currently rented movies:" << endl;
        if(report.empty()) {
            cout << "NONE" << endl;
        }
        for(const auto& rep : report) {
            cout << "\tShop = " << rep[0] << ", Movie = " << rep[1] << endl;
        }

        // Test drop
        cout << "Returning movie 1 to shop 2" << endl;
        mrs.drop(2, 1);
        cout << "Returning movie 0 to shop 0" << endl;
        mrs.drop(0, 0);

        // Test report one more time
        report = mrs.report();
        cout << "Currently rented movies:" << endl;
        if(report.empty()) {
            cout << "NONE" << endl;
        }
        for(const auto& rep : report) {
            cout << "\tShop = " << rep[0] << ", Movie = " << rep[1] << endl;
        }
    } else if(isQuitMode(mode)) { // If quit mode selected, exit program
        return quitModeSelected();
    } else { // Else, unknown mode. Error
        return unknownModeSelected(mode);
    }

    // Exit program
    return 0;
}