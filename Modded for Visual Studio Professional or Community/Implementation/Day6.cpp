#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <numeric>
#include <regex>
#include <algorithm>
#include <map>
#include <cstdint>

using namespace std;

// function to get txt input as we need to do it twice to reset it
vector<int> get_input_from_data() {
    ifstream myfile("..\\Personal txt Inputs\\Day6.txt");   //create an input stream object from file
    string file_line;                                       //create string object to read into
    vector<int> lanternfish_timers;                                       //create vector of ints/strings
    while(getline(myfile, file_line)) {                     //read each line and cast to file_line variable
        stringstream ss(file_line);                         // create a stringstream from the variable
        string s;                                           // create a variable to temp store each split word from stringstream
        int x;
        while(getline(ss, s, ',')) {                        // split string via the ','
            x = stoi(s);
            lanternfish_timers.push_back(x);                          //append file_line variable to vector
        }
    }
    myfile.close();
    return lanternfish_timers;
}

int Day6() {
    //Get the txt input
    vector<int> lanternfish_timers = get_input_from_data();

    // Part 1
    int num_days = 80;  // number of days to run for

    int day = 0;  // initialise the day to start on
    int64_t num_fish_to_add = 0;  // initialise the number of fish to append to list at very start
    vector<int> add_fish = {};

    while (day <= num_days) {
        if (num_fish_to_add != 0) {
            add_fish.clear();
            for (int i = 0; i < num_fish_to_add; i++) {
                add_fish.push_back(8);
            }
            lanternfish_timers.insert(end(lanternfish_timers), begin(add_fish), end(add_fish));
        }
        num_fish_to_add = 0;
        for (int i = 0; i < lanternfish_timers.size(); i++) {
            if (lanternfish_timers[i] == 0) {
                lanternfish_timers[i] = 6;
                num_fish_to_add += 1;
                continue;
            }
            lanternfish_timers[i] -= 1;
        }
        day += 1;
    }

    cout << "The number of fish after " << num_days << " days using the inefficient method is " << lanternfish_timers.size() << endl;

    // Part 2
    // if we try to reuse a singular list like in part 1 but with num_days = 256 it takes too long to run

    //Get the txt input again to reset it
    lanternfish_timers.clear();
    lanternfish_timers = get_input_from_data();
    
    num_days = 256;  // number of days to run for

    day = 1;  // initialise the day to start on

    // need to specify a 64 bit int for this as numbers will get very large and overflow causing errors
    // basically use 64 bit ints for every variable declared for part 2
    map<int64_t, int64_t> lanternfish_dict;

    while (day <= num_days) {
        num_fish_to_add = 0;

        // if (map.find("f") == map.end()) {
        // // not found
        // } else {
        // // found
        // }

        if (lanternfish_dict.find(day) == lanternfish_dict.end()) {  //if dictionary key does NOT exist
            lanternfish_dict.insert({day, 0});  // then initialise that key to be zero to be added to later
        }

        for (int64_t i = 0; i != lanternfish_timers.size(); i++) {  // loop to check ONLY the original fishes
            if (lanternfish_timers[i] == 0) {
                lanternfish_timers[i] = 6;
                num_fish_to_add += 1;
                continue;
            }
            lanternfish_timers[i] -= 1;
        }

        // for each day, add the number of new fish that appeared that day due to the original fishes
        // use the [] operater to access key as we want to overwrite the key added with map.insert() above
        lanternfish_dict[day] += num_fish_to_add;

        // this loop creates future day's dictionary keys for the number of new fish that we know will be added that day due
        // to previous fish
        if (lanternfish_dict[day] != 0) {
            int64_t exponential_add = lanternfish_dict[day];  // number of new fish to add will be at least original offspring, + new
            // newly added fish(es) from above will produce new fish in 8+1 days time
            int64_t future_days = day + 9;
            if (lanternfish_dict.find(future_days) == lanternfish_dict.end()) {  // if dictionary key does NOT exist
                lanternfish_dict.insert({future_days, 0});  // then initialise that key to be zero
            }
            lanternfish_dict[future_days] += exponential_add;  // and then add the number of new fish to that day
            while (future_days <= num_days) {
                future_days += 7;  // then the fish will produce a new one every 7 days
                if (lanternfish_dict.find(future_days) == lanternfish_dict.end()) {  // if dictionary key does NOT exist
                    lanternfish_dict.insert({future_days, 0});  // then initialise that key to be zero
                }
                lanternfish_dict[future_days] += exponential_add;  // and then add the number of new fish to that day
            }  
        }
        day += 1;
    }

    int64_t numfish = 0;
    for (int64_t i = 1; i != num_days + 1; i++) {
        numfish += lanternfish_dict[i];
    }

    cout << "The number of fish after " << num_days << " days using the more efficient method is " << numfish + lanternfish_timers.size() << endl;

    return 0;
}