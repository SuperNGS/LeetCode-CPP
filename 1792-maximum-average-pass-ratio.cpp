#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>

// Include custom utilities
#include <utilities.h>

using namespace std;

class Solution {
private:
    /**
    Calculate the gain for a given class
    */
    double gain(int pass, int total) {
        // Return gain = (# of passes + 1) / (# of students + 1) - (# of passes / # of students)
        return (double)(pass + 1) / (total + 1) - (double)pass / total;
    }
public:
    /**
    Calculate the max average ratio for the given classes
    */
    double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
        // Create a type for MaxHeap entries (pair<gain, {pass, total}>)
        using ClassInfo = pair<double, pair<int, int>>;

        // Create a priority_queue implemented as a MaxHeap
        priority_queue<ClassInfo> pq;

        // Loop through all classes, push them onto the heap
        for (auto& cls : classes) {
            // Break the class into it's number of passing students and number of total students
            int pass = cls[0], total = cls[1];

            // Create an instance of ClassInfo (pair<gain, {pass, total}>)
            ClassInfo info = {gain(pass, total), pair{pass, total}};

            // Push entry onto the MaxHeap
            pq.push(info);
        }

        // Iterate through all extra-students, add them where they produce max gain
        for (int i = 0; i < extraStudents; ++i) {
            auto [g, ratio] = pq.top();
            pq.pop();
            int pass = ratio.first + 1;
            int total = ratio.second + 1;

            // Create an instance of ClassInfo (pair<gain, {pass, total}>)
            ClassInfo info = {gain(pass, total), pair{pass, total}};

            // Push entry onto the MaxHeap
            pq.push(info);
        }

        // Loop through the heap, calculate the total ratio
        double totalRatio = 0.0;
        while (!pq.empty()) {
            auto [g, ratio] = pq.top();
            pq.pop();
            totalRatio += (double)ratio.first / ratio.second;
        }

        // Return the total average across all classes
        return totalRatio / classes.size();
    }
};

int main() {
    printStartBanner("1792. Maximum Average Pass Ratio", "O((n + k) log n)", "O(n)");

    // Get the mode to run program in from the user
    string mode = selectMode();
    
    // Initialize solution
    Solution s;

    if(isCustomMode(mode)) { // Custom mode selected, run with user input
        customModeSelected();

        // Initialize a 2D vector of classes and an int for extra students
        vector<vector<int>> classes;
        int extraStudents;

        // Create a holder for user input and loop until exit called
        string input;
        while(true) {
            // Get the class pair (pass, total) from user input
            cout << "Enter class as a comma-separated string (pass, total) or press enter to stop entries: ";
            getline(cin, input);
            toLowercase(input); // Convert input to lowercase for easier comparison

            if(input.empty() || isExitMode(input)) { // if blank input or exit mode selected, stop taking entries
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) { // If quit mode selected, exit program
                return quitModeSelected();
            }

            // Parse the input into a class pair (pass, total)
            vector<int> cls;
            stringstream ss(input);
            string token;
            while(getline(ss, token, ',')) {
                cls.push_back(stoi(token));
            }
            // Print the class entered and add it to classes
            cout << "Class entered: Pass = " << cls[0] << ", Total = " << cls[1] << endl;
            classes.push_back(cls);
        }
        
        // Get the number of extra students from user input
        cout << "Enter number of extra students: ";
        cin >> extraStudents;
        cout << "Extra students entered: " << extraStudents << endl;

        // Print the result of calculating Max Average Pass Ratio
        cout << "Max average pass ratio is: " << s.maxAverageRatio(classes, extraStudents) << endl;
    } else if(isDemoMode(mode)) { // Demo mode selected, run with demo data
        demoModeSelected();

        // Initialize a 3D vector of demoClasses to use for running demos
        vector<vector<vector<int>>> demoClasses =   {
                                                {
                                                    {1, 2}, {3, 5}, {2, 2}
                                                },
                                                {
                                                    {2, 4}, {3, 9}, {4, 5}, {2, 10}
                                                },
                                            };
        // Initialize vector demoExtraStudents to use for running demos
        vector<int> demoExtraStudents = {2, 4};

        // Loop through each set of demo data, print it, then calculate the MaxAveragePassRatio and print the result
        for(int i = 0; i < demoClasses.size(); i++) {
            cout << "Classes #" << i <<":" << endl;
            for(int j = 0; j < demoClasses[i].size(); j++) {
                vector<int> cls = demoClasses[i][j];
                cout << "\tClass #" << j << ": Pass = " << cls[0] << ", Total = " << cls[1] << endl;
            }
            cout << "\tExtra Students: " << demoExtraStudents[i] << endl;

            // Print the result of calculating Max Average Pass Ratio
            cout << "\tMax average pass ratio is: " << s.maxAverageRatio(demoClasses[i], demoExtraStudents[i]) << endl;
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // Quit or exit mode selected, exit program
        return quitModeSelected();
    } else { // Else, unknown mode. Error
        return unknownModeSelected(mode);
    }

    // Exit program
    return 0;
}