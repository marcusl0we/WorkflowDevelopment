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

int Day7() {
    ifstream myfile("..\\Personal txt Inputs\\Day7.txt");   //create an input stream object from file
    string file_line;                                       //create string object to read into
    vector<int> crab_positions;                                       //create vector of ints/strings
    while(getline(myfile, file_line)) {                     //read each line and cast to file_line variable
        stringstream ss(file_line);                         // create a stringstream from the variable
        string s;                                           // create a variable to temp store each split word from stringstream
        int x;
        while(getline(ss, s, ',')) {                        // split string via the ','
            x = stoi(s);
            crab_positions.push_back(x);                          //append file_line variable to vector
        }
    }
    myfile.close();


    // Part 3 - refactor the two lines of code added to solve Part 2 into a solution that gives both Part 1 and 2 at once
    auto max_crab_pos = max_element(begin(crab_positions), end(crab_positions));

    map<int, vector<int>> move_cost_dict;

    for (int pos_under_test = 0; pos_under_test < *max_crab_pos + 1; pos_under_test++) {  // positions to move to from 0 to max_crab_pos
        int fuel_usage_lin = 0;  // initialise the fuel that will be used for linear fuel usage model
        int fuel_usage_exp = 0;  // initialise the fuel that will be used for non-linear fuel usage model
        for (int crab : crab_positions) {  // each crab is in a certain position
            int fuel_usage = abs(crab - pos_under_test);
            fuel_usage_lin += fuel_usage;
            fuel_usage_exp += int((fuel_usage * (fuel_usage + 1))/2);  // nth term expression for addition factorial
        }
        move_cost_dict[pos_under_test] = {fuel_usage_lin, fuel_usage_exp};
    }
    
    vector<int> linear;
    for (int x = 0; x < move_cost_dict.size(); x++){
        linear.push_back(move_cost_dict[x][0]);
    }
    auto lowest_fuel_usage_lin = min_element(begin(linear), end(linear));
    auto lowest_cost_pos_lin = distance(begin(linear), lowest_fuel_usage_lin);  
    // distance function is used to get distance from beginning of vector up to lowest_fuel_usage_lin (distance between those two iterator inputs)
    // could use find function to get location iterator for lowest_fuel_usage_lin (2nd arg) if we didn't already basically have one from the min_element function return

    vector<int> exp;
    for (int x = 0; x < move_cost_dict.size(); x++){
        exp.push_back(move_cost_dict[x][1]);
    }
    auto lowest_fuel_usage_exp = min_element(begin(exp), end(exp));
    auto lowest_cost_pos_exp = distance(begin(exp), lowest_fuel_usage_exp);

    // need to use a dereference pointer * to the iterator returned from min_element functions in order to print the actual int value
    cout << "The lowest fuel cost move using a linear fuel usage model is to position " << lowest_cost_pos_lin << 
            " which costs " << *lowest_fuel_usage_lin << " fuel" << endl;
    cout << "The lowest fuel cost move using an addition factorial fuel usage model is to position " << lowest_cost_pos_exp << 
            " which costs " << *lowest_fuel_usage_exp << " fuel" << endl;        

    return 0;
}

