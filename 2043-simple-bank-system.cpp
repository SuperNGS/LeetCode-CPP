// Include custom utilities header
#include <utilities.h>

// Use standard namespace
using namespace std;

class Bank {
private:
    // Vector of account balances
    vector<long long> accounts;
    // Total number of accounts
    int numOfAccounts;
    // Helper method, returns true if transaction is valid (account exists and has enough money)
    // Returns false if transaction is not valid
    inline bool isValidTransaction(int account, long long money) {
        return  accountExists(account) && accounts[account] >= money;
    }
    // Helper method, returns true if account exists
    // Returns false if account doesn't exist
    inline bool accountExists(int account) {
        return account >= 1 && account <= numOfAccounts;
    }
public:
    Bank(vector<long long>& balance) : accounts(balance.size() + 1), numOfAccounts(balance.size()) {
        for (int i = 0; i < balance.size(); ++i) {
            accounts[i + 1] = balance[i];
        }
    }
    
    bool transfer(int account1, int account2, long long money) {
        if(isValidTransaction(account1, money) && accountExists(account2)) {
            accounts[account1] -= money;
            accounts[account2] += money;
            return true;
        } else {
            return false;
        }
    }
    
    bool deposit(int account, long long money) {
        if(accountExists(account)) {
            accounts[account] += money;
            return true;
        } else {
            return false;
        }
    }
    
    bool withdraw(int account, long long money) {
        if(isValidTransaction(account, money)) {
            accounts[account] -= money;
            return true;
        } else {
            return false;
        }
    }
};

int main() {
    printStartBanner("2043. Simple Bank System", "O(n) for constructor, O(1) for operations", "O(n) for constructor, O(1) for operations");

    // Get the mode to run program in from user;
    string mode = selectMode();

    if(isCustomMode(mode)) { // If custom mode, run with user input
        customModeSelected();

        // Initialize input string and get accounts long long vector as a comma-separated string
        string input;
        cout << "Enter account balances as a comma-separated string: ";
        getline(cin, input);
        toLowercase(input);

        // If exit or quit entered, exit program
        if(isExitMode(input) || isQuitMode(input)) {
            return quitModeSelected();
        }

        // Convert input to accounts
        vector<long long> accounts = stringToLongLongVector(input);

        // If no accounts entered, exit
        if(accounts.empty()) {
            cout << "INFO: No accounts entered. Exiting..." << endl;
            return 0;
        }

        // Print the accounts
        cout << "Initializing bank with accounts:" << endl;
        for(int i = 0; i < accounts.size(); i++) {
            cout << "\tAccount #" << i + 1 << ": $" << accounts[i] << endl;
        }

        // Initialize bank with accounts
        Bank bnk = Bank(accounts);
        cout << "Bank initialized with accounts" << endl;

        // Initialize operation string sets
        set<string> initOp = {"[i]nit", "init", "[i]", "i"};
        set<string> depositOp = {"[d]eposit", "deposit", "[d]", "d"};
        set<string> transferOp = {"[t]ransfer]", "transfer", "[t]", "t"};
        set<string> withdrawOp = {"[w]ithdraw", "withdraw", "[w]", "w"};

        // Start looping and taking operations
        while(true) {
            cout << "Enter an operation ([i]nit, [d]eposit, [t]ransfer, [w]ithdraw) or press enter to exit: ";
            getline(cin, input);
            toLowercase(input);

            // If exit or quit entered, exit program
            if(isExitMode(input) || isQuitMode(input)) {
                return quitModeSelected();
            }

            if(initOp.count(input)) { // If init op, reinitialize bank
                cout << "Enter account balances as a comma-separated string: ";
                getline(cin, input);
                toLowercase(input);

                // If exit or quit entered, exit program
                if(isExitMode(input) || isQuitMode(input)) {
                    return quitModeSelected();
                }

                // Convert input to accounts
                accounts = stringToLongLongVector(input);

                // If no accounts entered, skip
                if(accounts.empty()) {
                    cout << "INFO: No accounts entered. Skipping..." << endl;
                    continue;
                }

                // Print the accounts
                cout << "Initializing bank with accounts:" << endl;
                for(int i = 0; i < accounts.size(); i++) {
                    cout << "\tAccount #" << i + 1 << ": $" << accounts[i] << endl;
                }

                // Initialize bank with accounts
                bnk = Bank(accounts);
                cout << "Bank initialized with accounts" << endl;
            } else if(depositOp.count(input)) { // IF deposit op, process deposit
                // Get account to deposit into
                cout << "Enter account to deposit into: ";
                getline(cin, input);
                toLowercase(input);

                // If exit or quit entered, exit program
                if(isExitMode(input) || isQuitMode(input)) {
                    return quitModeSelected();
                }

                // Attempt to convert input to int account
                int account;
                try {
                    account = stoi(input);
                } catch(...) {
                    cout << "ERROR: Invalid input '" << input << "'. Please only enter an integer. Skipping..." << endl;
                    continue;
                }

                // Get money to deposit into account
                cout << "Enter money to deposit into account #" << account << ": ";
                getline(cin, input);
                toLowercase(input);

                // If exit or quit entered, exit program
                if(isExitMode(input) || isQuitMode(input)) {
                    return quitModeSelected();
                }

                // Attempt to convert input to long long money
                int money;
                try {
                    money = stoll(input);
                } catch(...) {
                    cout << "ERROR: Invalid input '" << input << "'. Please only enter a long long. Skipping..." << endl;
                    continue;
                }

                // Print result of the deposit
                cout << "$" << money << " successfully deposited into account #" << account << ": " << (bnk.deposit(account, money) ? "yes" : "no") << endl;
            } else if(transferOp.count(input)) { // If transfer op, process transfer
                // Get account to deposit into
                cout << "Enter account to transfer from: ";
                getline(cin, input);
                toLowercase(input);

                // If exit or quit entered, exit program
                if(isExitMode(input) || isQuitMode(input)) {
                    return quitModeSelected();
                }

                // Attempt to convert input to int accountOne
                int accountOne;
                try {
                    accountOne = stoi(input);
                } catch(...) {
                    cout << "ERROR: Invalid input '" << input << "'. Please only enter an integer. Skipping..." << endl;
                    continue;
                }

                // Get account to transfer to
                cout << "Enter account to transfer to: ";
                getline(cin, input);
                toLowercase(input);

                // If exit or quit entered, exit program
                if(isExitMode(input) || isQuitMode(input)) {
                    return quitModeSelected();
                }

                // Attempt to convert input to int accountTwo
                int accountTwo;
                try {
                    accountTwo = stoi(input);
                } catch(...) {
                    cout << "ERROR: Invalid input '" << input << "'. Please only enter an integer. Skipping..." << endl;
                    continue;
                }

                // Get money to transfer between accounts
                cout << "Enter money to transfer from account #" << accountOne << " to account #" << accountTwo << ": ";
                getline(cin, input);
                toLowercase(input);

                // If exit or quit entered, exit program
                if(isExitMode(input) || isQuitMode(input)) {
                    return quitModeSelected();
                }

                // Attempt to convert input to long long money
                int money;
                try {
                    money = stoll(input);
                } catch(...) {
                    cout << "ERROR: Invalid input '" << input << "'. Please only enter a long long. Skipping..." << endl;
                    continue;
                }

                // Print result of the deposit
                cout << "$" << money << " successfully transferred from account #" << accountOne << " to account #" << accountTwo << ": " << (bnk.transfer(accountOne, accountTwo, money) ? "yes" : "no") << endl;
            } else if(withdrawOp.count(input)) { // If withdraw op, process withdraw
                // Get account to deposit into
                cout << "Enter account to withdraw from: ";
                getline(cin, input);
                toLowercase(input);

                // If exit or quit entered, exit program
                if(isExitMode(input) || isQuitMode(input)) {
                    return quitModeSelected();
                }

                // Attempt to convert input to int account
                int account;
                try {
                    account = stoi(input);
                } catch(...) {
                    cout << "ERROR: Invalid input '" << input << "'. Please only enter an integer. Skipping..." << endl;
                    continue;
                }

                // Get money to withdraw from account
                cout << "Enter money to withdraw from account #" << account << ": ";
                getline(cin, input);
                toLowercase(input);

                // If exit or quit entered, exit program
                if(isExitMode(input) || isQuitMode(input)) {
                    return quitModeSelected();
                }

                // Attempt to convert input to long long money
                int money;
                try {
                    money = stoll(input);
                } catch(...) {
                    cout << "ERROR: Invalid input '" << input << "'. Please only enter a long long. Skipping..." << endl;
                    continue;
                }

                // Print result of the withdraw
                cout << "$" << money << " successfully withdrawn from account #" << account << ": " << (bnk.withdraw(account, money) ? "yes" : "no") << endl;
            } else { // Else, unknown op, error and skip
                cout << "ERROR: Invalid operation '" << input << "'. Skipping..." << endl;
                continue;
            }
        }

    } else if(isDemoMode(mode)) { // If demo mode, run with demo data
        demoModeSelected();

        // Create long long vector demoAccounts
        vector<long long> demoAccounts = {10,100,20,50,30};

        // Print demo accounts
        cout << "Running demo with accounts:" << endl;
        for(int i = 0; i < demoAccounts.size(); i++) {
            cout << "\tAccount #" << i + 1 << ": $" << demoAccounts[i] << endl;
        }
        // Initialize demo bank with demoAccounts
        cout << "Initializing demo bank...";
        Bank demoBank = Bank(demoAccounts);
        cout << "...demo bank initialized" << endl;

        // Demo withdraw 10 dollars from account 3
        cout << "Successfully withdrew $10 from account 3: " << (demoBank.withdraw(3, 10) ? "yes" : "no") << endl;

        // Demo transfer 20 dollars from account 5 to account 1
        cout << "Successfully transferred $20 from account 5 to account 1: " << (demoBank.transfer(5, 1, 20) ? "yes" : "no") << endl;

        // Demo deposit $20 into account 5
        cout << "Successfully deposited $20 into account 5: " << (demoBank.deposit(5, 20) ? "yes" : "no") << endl;

        // Demo transfer $15 from account 3 to account 4
        cout << "Successfully transferred $15 from account 3 to account 4: " << (demoBank.transfer(3, 4, 15) ? "yes" : "no") << endl;

        // Demo withdraw $50 from account 10
        cout << "Successfully withdrew $50 from account 10: " << (demoBank.withdraw(10, 50) ? "yes" : "no") << endl;
    } else if(isExitMode(mode) || isQuitMode(mode)) { // If exit or quit mode, exit program
        return quitModeSelected();
    } else { // Else, unknown mode, error
        return unknownModeSelected(mode);
    }

    // Exit program successfully
    return 0;
}