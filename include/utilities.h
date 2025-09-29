// Define a header guard to prevent multiple inclusions
#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <string>
#include <set>
#include <algorithm>

/* GLOBALS */
// Mode-matching set for custom mode
inline std::set<std::string> customMode = {"custom", "[c]ustom", "c", "[c]"};
// Mode-matching set for demo mode
inline std::set<std::string> demoMode = {"demo", "[d]emo", "d", "[d]"};
// Mode-matching set for exit mode
inline std::set<std::string> exitMode = {"exit", "[e]xit", "e", "[e]"};
// Mode-matching set for quit mode
inline std::set<std::string> quitMode = {"quit", "[q]uit", "q", "[q]"};

/* FUNCTIONS */
// Print the program start banner
void printStartBanner(const std::string title);
// Print the program start banner with time and space complexity
void printStartBanner(const std::string title, const std::string timeComplexity, const std::string spaceComplexity);
// Get mode to run program in from user
std::string selectMode();
// Bool for if mode is in custom mode
bool isCustomMode(const std::string mode);
// Print custom mode banner
void customModeSelected();
// Bool for if mode is in demo mode
bool isDemoMode(const std::string mode);
// Print demo mode banner
void demoModeSelected();
// Bool for if mode is in exit mode
bool isExitMode(const std::string mode);
// Print exit mode banner
void exitModeSelected();
// Bool for if mode is in quit mode
bool isQuitMode(const std::string mode);
// Print quit mode banner and return 0
int quitModeSelected();
// Print unknown mode banner and return -1
int unknownModeSelected(const std::string mode);
// Convert input to lowercase in-place
void toLowercase(std::string& input);
// Convert input to lowercase and store in copy
void toLowercase(std::string& input, std::string& copy);
// Convert input to uppercase in-place
void toUppercase(std::string& input);
// Convert input to uppercase and store in copy
void toUppercase(std::string& input, std::string& copy);

#endif