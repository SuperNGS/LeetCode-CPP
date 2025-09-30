#include <bits/stdc++.h>

// Custom utilities header
#include <utilities.h>

// Use std namespace
using namespace std;

class FoodRatings {
    // create foodMap as a map keyed by foodname with a pair of <cuisine, rating> as values
    unordered_map<string, pair<string, int>> foodMap; 
    // Create a cuisineMap as a map keyed by cuisine name with a set of values of type pair <rating, food>
    unordered_map<string, set<pair<int, string>>> cuisineMap;

public:
    FoodRatings(vector<string>& foods, vector<string>& cuisines, vector<int>& ratings) {
        // Loop through all items of the three arrays, tracking <cuisine, rating> in the foodMap
        // keyed by food and tracking <rating, food> in the cuisineMap keyed by cuisine
        // NOTE: Cuisine ratings are stored as negatives to push to top of Set
        foodMap = {};
        cuisineMap = {};
        for (int i = 0; i < foods.size(); i++) {
            foodMap[foods[i]] = {cuisines[i], ratings[i]};
            cuisineMap[cuisines[i]].insert({-ratings[i], foods[i]});
        }
    }

    void changeRating(string food, int newRating) {
        // Get the cuisine and rating from the foodMap
        auto [cuisine, oldRating] = foodMap[food];

        // Update the cuisineMap with the new rating
        cuisineMap[cuisine].erase({-oldRating, food});
        cuisineMap[cuisine].insert({-newRating, food});

        // update the foodMap with the new rating
        foodMap[food].second = newRating;
    }

    string highestRated(string cuisine) {
        // Return the first element from cuisineMap with the key cuisine
        return cuisineMap[cuisine].begin()->second;
    }
};

/**
 * Helper function to custom init FoodRatings
 */
FoodRatings initFoodRatings() {
    // Initialize blank input string
    string input;

    // Provided a comma-separated string by the user, create a vector<string> of foods    
    cout << "Enter foods as a comma-separated string: ";
    string foodString;
    getline(cin, foodString);
    toLowercase(foodString, input);

    if(isExitMode(input) || isQuitMode(input)) { // If blank, exit, or quit entered, exit program
        exit(quitModeSelected());
    }

    vector<string> foods;
    stringstream ssf(foodString);
    string foodToken;
    cout << "Initializing with foods: ";
    while(getline(ssf, foodToken, ',')) {
        transform(foodToken.begin(), foodToken.end(), foodToken.begin(), ::tolower);
        cout << foodToken << " ";
        foods.push_back(foodToken);
    }
    cout << endl;

    // Provided a comma-separated string by the user, create a vector<string> of cuisines
    cout << "Enter cuisines as a comma-separated string: ";
    string cuisineString;
    getline(cin, cuisineString);
    toLowercase(cuisineString, input);

    if(isExitMode(input) || isQuitMode(input)) { // If blank, exit, or quit entered, exit program
        exit(quitModeSelected());
    }

    vector<string> cuisines;
    stringstream ssc(cuisineString);
    string cuisineToken;
    cout << "Initializing with cuisines: ";
    while(getline(ssc, cuisineToken, ',')) {
        transform(cuisineToken.begin(), cuisineToken.end(), cuisineToken.begin(), ::tolower);
        cout << cuisineToken << " ";
        cuisines.push_back(cuisineToken);
    }
    cout << endl;

    // Provided a comma-separated string by the user, create a vecctor<int> of ratings
    cout << "Enter ratings as a comma-separated string: ";
    string ratingString;
    getline(cin, ratingString);
    toLowercase(ratingString, input);

    if(isExitMode(input) || isQuitMode(input)) { // If blank, exit, or quit entered, exit program
        exit(quitModeSelected());
    }
    
    vector<int> ratings;
    stringstream ssr(ratingString);
    string ratingToken;
    while(getline(ssr, ratingToken, ',')) {
        try {
            ratings.push_back(stoi(ratingToken));
        } catch(...) {
            cout << "ERROR: invalid input '" << ratingToken << "'. Please only enter integers. Skipping..." << endl;
        }
    }

    if(ratings.size() != cuisines.size()) {
        cout << "ERROR: Number of ratings must match number of entries. Try again" << endl;
        return initFoodRatings();
    }

    // Print the ratings used for initialization
    cout << "Initializing with ratings: ";
    for(const auto& rating : ratings) {
        cout << rating << " ";
    }
    cout << endl;

    // Return the initialized FoodRatings object
    return FoodRatings(foods, cuisines, ratings);
}

int main() {
    printStartBanner("2353. Design a Food Rating System", "O(n log n) for initialization, O(log m) for rating change, O(1) for query highest", "O(1)");

    // Get mode to run in from the user
    string mode = selectMode();

    if(isCustomMode(mode)) { // Custom mode selected, run with user-provided data
        cout << "Custom mode selected" << endl;

        // Create the initialized FoodRatings object
        FoodRatings fr = initFoodRatings();

        cout << "Food Rating System initialized" << endl;

        set<string> initOp = {"init", "[i]nit", "i", "[i]"};
        set<string> changeOp = {"change", "[c]hange", "c", "[c]"};
        set<string> highOp = {"highest", "[h]ighest", "h", "[h]"};

        // Initialize input and begin loop
        string input;
        while(true) {
            cout << "Select operation ([i]nit, [c]hange, [h]ighest) or press enter to exit: ";
            getline(cin, input);
            toLowercase(input);

            if(isExitMode(input)) { // If blank string or exit entered, break loop
                exitModeSelected();
                break;
            } else if(isQuitMode(input)) { // If quit selected, exit program
                return quitModeSelected();
            }

            if(initOp.find(input) != initOp.end()) { // If user selected 'init' or 'i', reinitialize FoodRatings
                cout << "Init operation selected" << endl;
                fr = initFoodRatings();
            } else if(changeOp.find(input) != changeOp.end()) { // If user selected 'change' or 'c', run changeRating with user input
                cout << "Change operation selected" << endl;
                string food;
                int rating;

                cout << "Select food: ";
                getline(cin, food);
                toLowercase(food, input);

                if(isExitMode(input)) { // If blank string or exit entered, break loop
                    exitModeSelected();
                    break;
                } else if(isQuitMode(input)) { // If quit selected, exit program
                    return quitModeSelected();
                }
                cout << "Select rating: ";
                getline(cin, input);
                toLowercase(input);

                if(isExitMode(input)) { // If blank string or exit entered, break loop
                    exitModeSelected();
                    break;
                } else if(isQuitMode(input)) { // If quit selected, exit program
                    return quitModeSelected();
                }

                try {
                    rating = stoi(input);
                } catch(...) {
                    cout << "ERROR: Invalid input '"<< input << "'. Rating must be an int. Skipping..." << endl;
                    continue;
                }

                // Change the rating and print
                fr.changeRating(food, rating);
                cout << "Changed rating for food " << food << " to " << rating << endl;
            } else if(highOp.find(input) != highOp.end()) { // If user selected 'highest' or 'h', run highestRated with user input
                cout << "Highest operation selected" << endl;
                
                string cuisine;
                cout << "Select cuisine: ";
                getline(cin, cuisine);
                toLowercase(cuisine, input);

                if(isExitMode(input)) { // If blank string or exit entered, break loop
                    exitModeSelected();
                    break;
                } else if(isQuitMode(input)) { // If quit selected, exit program
                    return quitModeSelected();
                }

                cout << "The highest rated food for cuisine " << cuisine << " is " << fr.highestRated(cuisine) << endl;
            } else { // If none of the above selected, invalid operation specified
                cout << "Unknown operation: '" << input << "'. Skipping..." << endl;
            }
        }
        
    } else if(isDemoMode(mode)) { // Demo mode selected, run with demo data
        // Create vectors for food, cuisines, and ratings
        vector<string> foods = {"kimchi", "miso", "sushi", "moussaka", "ramen", "bulgogi"};
        vector<string> cuisines = {"korean", "japanese", "japanese", "greek", "japanese", "korean"};
        vector<int> ratings = {9, 12, 8, 15, 14, 7};

        // Print out the demo data
        cout << "Initializing food rating system with:" << endl;
        for(int i = 0; i < foods.size(); i++) {
            cout << "Food: " << foods[i] << ", Cuisine: " << cuisines[i] << ", Rating: " << ratings[i] << endl;
        }
        cout << endl;

        // Initialize the FoodRatings system
        FoodRatings fr = FoodRatings(foods, cuisines, ratings);

        // Get the highest rated for each type of cuisine
        cout << "Highest rated Japanese cuisine: " << fr.highestRated("japanese") << endl;
        cout << "Highest rated Korean cuisine: " << fr.highestRated("korean") << endl;
        cout << "Highest rated Greek cuisine: " << fr.highestRated("greek") << endl;

        // Change rating for ramen to 5 and bulgogi to 10
        fr.changeRating("ramen", 5);
        cout << "Changed rating for Ramen to 5" << endl;
        fr.changeRating("bulgogi", 10);
        cout << "Changed rating for Bulgogi to 10" << endl;
        
        // Get the new highest ratings
        cout << "Highest rated Japanese cuisine: " << fr.highestRated("japanese") << endl;
        cout << "Highest rated Korean cuisine: " << fr.highestRated("korean") << endl;
        cout << "Highest rated Greek cuisine: " << fr.highestRated("greek") << endl;

    } else if(isExitMode(mode) || isQuitMode(mode)) { // Exit or quit selected, exit program
        return quitModeSelected();
    } else { // Unknown mode selected, return error
        return unknownModeSelected(mode);
    }

    // Exit program successfully
    return 0;
}