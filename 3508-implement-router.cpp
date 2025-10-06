#include <cstdlib>
#include <queue>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <sstream>

// Custom utilities header
#include <utilities.h>

// Use standard namespace
using namespace std;

class Router {
private:
    string stringifyPacket(int source,int destination,int timestamp) {
        return to_string(source) + " " + to_string(destination) + " " + to_string(timestamp);
    }
public:
    int LIMIT; // Max packets that can be stored
    queue<string> queue; // Queue of packets
    unordered_map<string,vector<int>> packets;  // key -> packet [source,dest,timestamp]
    unordered_map<int, vector<int>> destToTimestamp; // destination -> sorted timestamps

    Router(int memoryLimit) {
        LIMIT = memoryLimit;
    }
    
    bool addPacket(int source, int destination, int timestamp) {
        // Stringify the packet to use as key
        string key = stringifyPacket(source,destination,timestamp);

        // If packet found, duplicate detected. Return false
        if(packets.find(key) != packets.end()) {
            return false;
        }

        // If packets over limit, forward the first packet
        if(queue.size() >= LIMIT) {
            forwardPacket();
        }

        // Add the packet to the map and queue, add the timestamp to the destToTimestamp map
        packets[key] = {source, destination, timestamp};
        queue.push(key);
        destToTimestamp[destination].push_back(timestamp);

        // Return true (Packet added)
        return true;
    }
    
    vector<int> forwardPacket() {
        // If no packets, return empty
        if(packets.empty()) {
            return {};
        }

        // Pop the first packet off the queue and save it's key
        string key = queue.front();
        queue.pop();

        // Get the packet and erase it from the stored packets
        vector<int> packet = packets[key];
        packets.erase(key);

        // Erase the timestamp from the destToTimestamp map
        int dest = packet[1];
        destToTimestamp[dest].erase(destToTimestamp[dest].begin());

        // Return the packet
        return packet;
    }
    
    int getCount(int destination, int startTime, int endTime) {

        // Find the timestamps associated with the given destination
        auto it = destToTimestamp.find(destination);
        if(it == destToTimestamp.end() || it->second.empty())
            return 0;

        // Get the lower and upper bounds of the range startTime -> endTime
        int i = lower_bound(begin(it->second),end(it->second),startTime) - it->second.begin();
        int j = upper_bound(begin(it->second),end(it->second),endTime) - it->second.begin();

        // Result is the difference of upper_bound - lower_bound
        return j - i;
    }
};

int main() {
    printStartBanner("3508. Implement Router", "O(n log n)", "O(n)");

    // Prompt user for mode to run program in
    string mode = selectMode();

    if(isCustomMode(mode)) { // If custom mode selected, run proram with user input
        customModeSelected();

        // Initialize router with user input
        string input;
        cout << "Enter memory limit for router or press enter to exit: ";
        getline(cin, input);
        toLowercase(input);

        if(isExitMode(input) || isQuitMode(input)) { // If exit or quit mode selected, exit program
            return quitModeSelected();
        }

        // Initialize int for router memory limit
        int memory_limit;
        try{ // Attempt to convert input to an int and assign to memory_limit
            memory_limit = stoi(input);
        } catch(...) { // If input invalid type, print and error
            cout << "ERROR: Invalid input '" << input << "'. Please only enter an integer." << endl;
            return -1;
        }

        // Initialize the router and print
        Router rtr = Router(memory_limit);
        cout << "Router initialized with memory limit of " << memory_limit << endl;

        // Create sets for operations
        set<string> iniOp = {"init", "[i]nit", "i", "[i]"};
        set<string> addOp = {"add", "[a]dd", "a", "[a]"};
        set<string> fwdOp = {"forward", "[f]orward", "f", "[f]"};
        set<string> cntOp = {"count", "[c]ount", "c", "[c]"};

        // Start looping for operations
        while(true) {
            cout << "Select operation ([i]nit, [a]dd, [f]orward, [c]ount) or press enter to exit: ";
            getline(cin, input);
            toLowercase(input);

            if(isExitMode(input)) { // If exit mode selected, exit loop
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) { // If quit mode selected, exit program
                return quitModeSelected();
            }

            if(iniOp.count(input)) { // If init op selected, reinitalize router
                cout << "Init operation selected" << endl;

                cout << "Please enter memory limit: ";
                getline(cin, input);
                toLowercase(input);

                if(isExitMode(input)) { // If exit mode selected, exit loop
                    exitModeSelected();
                    break;
                } else if(isQuitMode(input)) { // If quit mode selected, exit program
                    return quitModeSelected();
                }

                try { // Attempt to convert input into int and assign to memory_limit
                    memory_limit = stoi(input);
                } catch(...) { // Catch invalid input type, skip
                    cout << "ERROR: Invalid input '" << input << "'. Please only enter an integer. Skipping..." << endl;
                    continue;
                }

                // Reinitialize the router and print
                rtr = Router(memory_limit);
                cout << "Router reinitialized with memory limit " << memory_limit << endl;
            } else if(addOp.count(input)) { // if add op selected, add packet
                cout << "Add operation selected" << endl;

                // Get the packet to add details from user input
                cout << "Enter packet as a comma-separated string (source, destination, timestamp) or press enter to exit: ";
                getline(cin, input);
                toLowercase(input);

                if(isExitMode(input)) { // If exit mode selected, exit loop
                    exitModeSelected();
                    break;
                } else if(isQuitMode(input)) { // If quit mode selected, exit program
                    return quitModeSelected();
                }

                // Attempt to tokenize the input string into int vector packet
                vector<int> packet;
                stringstream ss(input);
                string token;
                while(getline(ss, token, ',')) {
                    try { // Attempt to convert token to an int and push back onto packet
                        packet.push_back(stoi(token));
                    } catch(...) { // Catch invalid type, print error and skip
                        cout << "ERROR: Invalid input '" << token << "'. Please only enter integers. Skipping..." << endl;
                        continue;
                    }
                }

                // If too few inputs to form a packet, error and skip
                if(packet.size() < 3) {
                    cout << "ERROR: Too few arguments (" << packet.size() << ") provided for packet. Three are required: source, destination, and timestamp. Skipping..." << endl;
                    continue;
                }

                // If more than three inputs provided, display an info message
                if(packet.size() > 3) {
                    cout << "INFO: Too many arguments (" << packet.size() << ") provided. Will only use first three." << endl;
                }

                // Add the packet, print details
                cout << "Packet with source = " << packet[0] << ", destination = " << packet[1] << ", and timestamp = " << packet[2] << " added successfully: " << (rtr.addPacket(packet[0], packet[1], packet[2]) ? "yes" : "no") << endl;


            } else if(fwdOp.count(input)) { // if fwd op selected, forward packet
                cout << "Forward operation selected" << endl;

                // Forward top packet, capture details
                vector<int> packet = rtr.forwardPacket();

                // Print details
                cout << "Forwarded packet with source = " << packet[0] << ", destination = " << packet[1] << ", and timestamp = " << packet[2] << endl;
            } else if(cntOp.count(input)) { // if cnt op selected, return count
                cout << "Count operation selected" << endl;

                cout << "Enter destination, start time, and end time as a comma-separated string: ";
                getline(cin, input);
                toLowercase(input);

                if(isExitMode(input)) { // If exit mode selected, exit loop
                    exitModeSelected();
                    break;
                } else if(isQuitMode(input)) { // If quit mode selected, exit program
                    return quitModeSelected();
                }

                // Attempt to parse the destination, start time, and end time from the input into int vector args
                vector<int> args;
                stringstream ss(input);
                string token;
                while(getline(ss, token, ',')) {
                    try { // Attempt to convert token to an int and push back onto args
                        args.push_back(stoi(token));
                    } catch(...) { // Catch invalid type and skip
                        cout << "ERROR: Invalid input '" << token << "'. Please only enter integers. Skipping..." << endl;
                        continue;
                    }
                }

                // If too few arguments, error and skip
                if(args.size() < 3) {
                    cout << "ERROR: Too few arguments provided (" << args.size() << "). Please enter 3 values. Skipping..." << endl;
                    continue;
                }

                // If too many arguments, print informational message
                if(args.size() > 3) {
                    cout << "INFO: Too many arguments (" << args.size() << ") provided. Will only use first three." << endl;
                }

                // Print input
                cout << "Getting count for destination = " << args[0] << ", start time = " << args[1] << ", end time = " << args[2] << endl;
                // Calculate and print count
                cout << "Count is " << rtr.getCount(args[0], args[1], args[2]) << endl;
            } else { // Else, unknown op, error and skip
                cout << "ERROR: Unknown operation '" << input << "'. Skipping..." << endl;
                continue;
            }
        }
    } else if(isDemoMode(mode)) { // If demo mode selected, run program with demo data
        demoModeSelected();

        // Set a demo router limit of 5
        int demo_limit = 5;

        // Initialize the router
        Router demo = Router(demo_limit);

        // Print router initialization
        cout << "Demo router initialized with memory limit of " << demo_limit << endl;

        // Initialize 2D vector of demo packets (source, destination, timestamp)
        vector<vector<int>> demoPackets = {
            {1, 2, 10},
            {2, 1, 15},
            {1, 2, 20},
            {2, 1, 25},
            {1, 3, 30}
        };

        // Add the packets to the router and print
        for(const auto& packet : demoPackets) {
            cout << "Adding packet: source = " << packet[0] << ", destination = " << packet[1] << ", timestamp = " << packet[2] << endl;
            cout << "Packet added successfully: " << (demo.addPacket(packet[0], packet[1], packet[2]) ? "yes" : "no") << endl;
        }

        // Get count of packets sent to destination 1
        cout << "Packets sent to destination 1: " << demo.getCount(1, 0, 50) << endl;
        // Get count of packets sent to destination 2
        cout << "Packets sent to destination 2: " << demo.getCount(2, 0, 50) << endl;
        // Get count of packets sent to destination 3
        cout << "Packets sent to destination 3: " << demo.getCount(3, 0, 50) << endl;


        // Attempt to add duplicate packet
        cout << "Duplicate packet successfully added: " << (demo.addPacket(1, 2, 10) == 1 ? "yes" : "no") << endl;

        // Add a packet over memory limit
        cout << "Packet successfully added over memory limit: " << (demo.addPacket(3, 1, 35) == 1 ? "yes" : "no") << endl;

        // Forward a packet
        vector<int> packet = demo.forwardPacket();
        cout << "Forwarded packet: source = " << packet[0] << ", destination = " << packet[1] << ", timestamp = " << packet[2] << endl;

        // Get count of packets sent to destination 1
        cout << "Packets sent to destination 1: " << demo.getCount(1, 0, 50) << endl;
        // Get count of packets sent to destination 2
        cout << "Packets sent to destination 2: " << demo.getCount(2, 0, 50) << endl;
        // Get count of packets sent to destination 3
        cout << "Packets sent to destination 3: " << demo.getCount(3, 0, 50) << endl;    
    } else if(isExitMode(mode) || isQuitMode(mode)) { // If exit or quit mode selected, exit program
        return quitModeSelected();
    } else { // Else, unknown mode selected, error
        return unknownModeSelected(mode);
    }

    // Exit program successfully
    return 0;
}