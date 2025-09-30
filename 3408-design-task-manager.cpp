#include <unordered_map>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <sstream>

// Custom utilities header
#include <utilities.h>

// Use standared namespace
using namespace std;

class TaskManager {
private:
    unordered_map<int, int> taskToUser; // Key: taskId, Value: userId
    unordered_map<int, int> taskToPriority; // Key: taskId, Value: priority
    priority_queue<pair<int, int>> maxHeap; // MaxHeap of {priority, taskId} pairs
    
public:
    TaskManager(vector<vector<int>>& tasks) {
        // Loop over all provided tasks
        for (const auto& task : tasks) {
            // Separate task triple into it's components
            int userId = task[0], taskId = task[1], priority = task[2];

            // Assign task-to-user and task-to-priority map pairs
            taskToUser[taskId] = userId;
            taskToPriority[taskId] = priority;

            // Add the task to the heap
            maxHeap.push({priority, taskId});
        }
    }
    
    void add(int userId, int taskId, int priority) {
        // Set the task-to-user and task-to-priority map values
        taskToUser[taskId] = userId;
        taskToPriority[taskId] = priority;

        // Push the task on to the max-heap
        maxHeap.push({priority, taskId});
    }
    
    void edit(int taskId, int newPriority) {
        // Update the task-to-priority value
        taskToPriority[taskId] = newPriority;

        // Push the updated task on to the heap
        maxHeap.push({newPriority, taskId});
    }
    
    void rmv(int taskId) {
        // Remove the task-to-user and task-to-priority map entries
        taskToUser.erase(taskId);
        taskToPriority.erase(taskId);
    }
    
    int execTop() {
        // Lazy cleanup until finding valid task
        while (!maxHeap.empty()) {
            // Get the priority and task from the top of the heap
            auto [priority, taskId] = maxHeap.top();
            
            // Check if task exists and priority is current
            auto it = taskToPriority.find(taskId);

            // If taskId in task-to-priority and priority is current, process it
            if (it != taskToPriority.end() && it->second == priority) {
                // Remove the top element from the MaxHeap
                maxHeap.pop();

                // Get the userId from task-to-user map by taskId
                int userId = taskToUser[taskId];

                // Erase the task from the task-to-user and task-to-priority maps
                taskToUser.erase(taskId);
                taskToPriority.erase(taskId);

                // Return the userId
                return userId;
            }
            
            // Remove outdated entries
            maxHeap.pop();
        }
        
        return -1; // No valid tasks
    }
};

TaskManager initTaskManager() {
    cout << "Initializing TaskManager" << endl;
    
    // Create sets to match the inputtable modes
    set<string> quitMode = {"quit", "[q]uit", "q", "[q]"};
    set<string> exitMode = {"exit", "[e]xit", "e", "[e]"};

    // Create a 2D vector for entered tasks
    vector<vector<int>> tasks;

    // Create a holder for user input and loop
    string input;
    while(true) {
        // Get the comma-seperated task string from the user
        cout << "Input task as a comma-seperated string (UserID, TaskID, Priority) or press enter to stop entries: ";
        getline(cin, input);
        toLowercase(input);

        if(isQuitMode(input)) { // If quit entered, exit program
            exit(0);
        } else if(isExitMode(input)) { // If exit entered, break out of loop
            exitModeSelected();
            break;
        }

        // Tokenize the input string into task vector, print and push back to tasks
        vector<int> task;
        stringstream ss(input);
        string token;
        while(getline(ss, token, ',')) {
            try {
                task.push_back(stoi(token));
            } catch(...) { // If conversion fails, print error and skip to next iteration of loop
                cout << "Invalid input: " << token << ". Please enter only integers. Skipping..." << endl;
                task.clear();
                break;
            }
        }

        if(task.size() != 3) { // If task does not contain exactly 3 integers, print error and continue loop
            cout << "ERROR: Please enter exactly three integers separated by commas. Skipping..." << endl;
            continue;
        }

        cout << "Task: UserID = " << task[0] << ", TaskID = " << task[1] << ", Priority = " << task[2] << endl;
        tasks.push_back(task);
    }

    return TaskManager(tasks);
}

int main() {
    printStartBanner("3408. Design Task Manager", "O(log(n)) for Add, Edit, ExecTop and O(1) for Rmv", "O(n)");

    // Get mode to run program in from user
    string mode = selectMode();

    if(isCustomMode(mode)) { // Custom mode selected, run with user input
        customModeSelected();

        // Initialize the TaskManager
        TaskManager tm = initTaskManager();

        // Create sets to match operation types
        set<string> initOp = {"init", "[i]nit", "i", "[i]"};
        set<string> addOp = {"add", "[a]dd", "a", "[a]"};
        set<string> editOp = {"edit", "[e]dit", "e", "[e]"};
        set<string> rmvOp = {"remove", "[r]emove", "rmv", "[r]mv", "r", "[r]"};
        set<string> execOp = {"execute", "[ex]ecute", "exec", "[ex]ec", "ex", "[ex]"};



        // Create a holder for user input and loop
        string input;
        while(true) {
            // Get the operation to run from the user
            cout << "Select operation ([i]nit, [a]dd, [e]dit, [r]emove, [ex]ecute) or press enter to quit: ";
            getline(cin, input);
            toLowercase(input);

            if(initOp.find(input) != initOp.end()) { // Init operation selected
                tm = initTaskManager();
            } else if(addOp.find(input) != addOp.end()) { // Add operation selected
                // Get the comma-seperated task string (UserID, TaskID, Priority) from the user
                cout << "Enter the comma-seperated task string (UserID, TaskID, Priority) to add or press enter to exit: ";
                getline(cin, input);
                toLowercase(input);

                if(isExitMode(input)) { // if exit mode selected, continue
                    exitModeSelected();
                    continue;
                }else if(isQuitMode(input)) { // if quit mode selected, exit program
                    return quitModeSelected();
                }

                // Tokenize input string into ints, push back to task
                vector<int> task;
                stringstream ss(input);
                string token;
                while(getline(ss, token, ',')) {
                    try { // Attempt to convert each token to an integer and add to task vector
                        task.push_back(stoi(token));
                    } catch(...) { // If conversion fails, print error and skip to next iteration of loop
                        cout << "Invalid input: " << token << ". Please enter only integers. Skipping..." << endl;
                        task.clear();
                        break;
                    }
                }

                if(task.size() != 3) { // If task does not contain exactly 3 integers, print error and continue loop
                    cout << "ERROR: Please enter exactly three integers separated by commas. Skipping..." << endl;
                    continue;
                }

                // Add the task and print it
                tm.add(task[0], task[1], task[2]);
                cout << "Added task: UserID = " << task[0] << ", TaskID = " << task[1] << ", Priority = " << task[2] << endl;
            } else if(editOp.find(input) != editOp.end()) { // Edit operation selected
                // Get the comma-seperated edit string (TaskID, Priority) from the user
                cout << "Enter the comma-seperated edit string (TaskID, Priority) to edit or press enter to exit: ";
                getline(cin, input);
                toLowercase(input);

                if(isExitMode(input)) { // if exit mode selected, continue
                    exitModeSelected();
                    continue;
                }else if(isQuitMode(input)) { // if quit mode selected, exit program
                    return quitModeSelected();
                }

                // Tokenize input string into ints, push back to edit
                vector<int> edit;
                stringstream ss(input);
                string token;
                while(getline(ss, token, ',')) {
                    try { // Attempt to convert each token to an integer and add to edit vector
                        edit.push_back(stoi(token));
                    } catch(...) { // If conversion fails, print error and skip to next iteration of loop
                        cout << "Invalid input: " << token << ". Please enter only integers. Skipping..." << endl;
                        edit.clear();
                        break;
                    }
                }

                if(edit.size() != 2) { // If edit does not contain exactly 2 integers, print error and continue loop
                    cout << "ERROR: Please enter exactly two integers separated by a comma. Skipping..." << endl;
                    continue;
                }

                // Edit the task and print it
                tm.edit(edit[0], edit[1]);
                cout << "Edited task: TaskID = " << edit[0] << ", Priority = " << edit[1] << endl;
            } else if(rmvOp.find(input) != rmvOp.end()) { // Remove operation selected
                // Get the TaskID to remove from the user
                cout << "Enter the TaskID to remove or press enter to exit: ";
                getline(cin, input);
                toLowercase(input);

                if(isExitMode(input)) { // if exit mode selected, break
                    exitModeSelected();
                    continue;
                } else if(isQuitMode(input)) { // if quit mode selected, exit program
                    return quitModeSelected();
                }

                int taskId;
                // Attempt to convert the entered taskID to an int
                try {
                    taskId = stoi(input);
                } catch(...) { // If conversion fails, print error and skip to next iteration of loop
                    cout << "Invalid input: " << input << ". Please enter only integers. Skipping..." << endl;
                    continue;
                }

                // Remove the task and print
                tm.rmv(taskId);
                cout << "Task Removed: TaskID = " << taskId << endl;
            } else if(execOp.find(input) != execOp.end()) { // Execute operation selected
                cout << "Executing top task" << endl;
                int userId = tm.execTop();
                cout << "Executed top task for user " << userId << endl;
            } else if(isQuitMode(input)) { // Quit operation selected
                return quitModeSelected();
            } else if(isExitMode(input)) { // Exit operation selected
                exitModeSelected();
                break;
            } else { // Else, unknown operation
                cout << "Unknown operation: " << input << endl;
            }

        }
    } else if(isDemoMode(mode)) { // Demo mode selected, run with demo data
        demoModeSelected();

        // Create a 2D vector of demo data
        vector<vector<int>> demoData =  {
                                            {1,1,5},
                                            {1,2,3},
                                            {2,3,4},
                                            {2,4,2},
                                            {3,5,3},
                                            {3,6,5}
                                        };

        // Print out the demo tasks
        cout << "Initializing with tasks:" << endl;
        for(const auto& task : demoData) {
            cout << "\tUserID = " << task[0] << ", TaskID = " << task[1] << ", Priority: " << task[2] << endl;
        }

        // Initialize the TaskManager
        TaskManager tm = TaskManager(demoData);

        // Test execTop
        int userId = tm.execTop();
        cout << "Executed top task for user " << userId << endl;

        // Test add
        tm.add(3, 7, 15);
        cout << "Added task: UserID = 3, TaskID = 7, Priority = 15" << endl;

        // Test edit
        tm.edit(4, 20);
        cout << "Edited task: UserID = 2, TaskID = 4, Priority = 2 to New Priority = 20" << endl;

        // Test rmv
        tm.rmv(6);
        cout << "Removed task: UserID = 3, TaskID = 6, Priority = 5" << endl;

        // Execute top tasks three times
        for(int i = 0; i < 3; i++) {
            userId = tm.execTop();
            cout << "Executed top task for user " << userId << endl;
        }
    } else if(isExitMode(mode) || isQuitMode(mode)) { // Quit mode selected, exit program
        return quitModeSelected();
    } else { // Else, unknown mode, error
        return unknownModeSelected(mode);
    }

    // Exit program
    return 0;
}