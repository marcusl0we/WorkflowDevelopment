#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <numeric>
#include <bitset>

using namespace std;

auto useful_data_out_for_position(vector<string> bin_list, int position) {
    int zeros = 0;
    int ones = 0;
    vector<string> z_list;
    vector<string> o_list;
    for (auto x : bin_list) {
        //x = x.strip()
        if (x[position] == '0') {
            zeros += 1;
            z_list.push_back(x);
        }
        else if (x[position] == '1') {
            ones += 1;
            o_list.push_back(x);
        }            
    }
    
    struct ReturnVals {
        int _1;
        int _2;
        vector<string> _3;
        vector<string> _4;
    };
    return ReturnVals {zeros, ones, z_list, o_list};
}

int main() {
    //Get the txt input
    ifstream myfile("..\\Personal txt Inputs\\Day3.txt");   //create an input stream object from file
    string file_line;                                            //create line object to read into
    vector<string> binary_list;                            //create vector of ints/strings
    while(getline(myfile, file_line)) {                          //read each line and cast to file_line variable
        binary_list.push_back(file_line);                       //append file_line variable to vector
    }
    myfile.close();

    int num_bits = 12;

    vector<int> bit_info[num_bits];  // create array of vector strings as python dict equivalent, index is bit num, vector contains info
    // skip counter i used in python version as we do not bother initialising dict values to [0,0] like we do there

    for (int j = 0; j < num_bits; ++j) {
        auto [num_zeros, num_ones, zeros_list, ones_list] = useful_data_out_for_position(binary_list, j);
        bit_info[j].push_back(num_zeros);
        bit_info[j].push_back(num_ones);
    }

    string gamma_rate;
    for (int k = 0; k < num_bits; ++k) {

        if (bit_info[k][0] > bit_info[k][1]) {
            gamma_rate += '0';
        }
        else {
            gamma_rate += '1';
        }
    }
    int gamma_rate_dec = stoi(gamma_rate, nullptr, 2);
    cout << "The gamma rate: binary = " << gamma_rate << ", decimal = " << gamma_rate_dec << endl;

    string epsilon_rate;
    for (char i : gamma_rate) {
        if (i == '0'){
            epsilon_rate += '1';
        } else {
            epsilon_rate += '0';
        }
    }
    int epsilon_rate_dec = stoi(epsilon_rate, nullptr, 2);
    cout << "The epsilon_rate: binary = " << epsilon_rate << ", decimal = " << epsilon_rate_dec << endl;
    
    int power_consumption_dec = gamma_rate_dec * epsilon_rate_dec;
    string power_consumption = bitset<24>(gamma_rate_dec * epsilon_rate_dec).to_string();
    cout << "The power_consumption: binary = " << power_consumption << ", decimal = " << power_consumption_dec << endl << endl;


    // Part 2 
    // use the function to loop over a filtered list until the filtered list becomes one value for oxygen generator rating
    vector<string> filtered_list = binary_list;  
    int m = 0;
    while (filtered_list.size() != 1) {
        auto [num_zeros, num_ones, zeros_list, ones_list] = useful_data_out_for_position(filtered_list, m);
        if (num_zeros > num_ones) {
            filtered_list = zeros_list;
            m += 1;
        }
        else if (num_ones > num_zeros) {
            filtered_list = ones_list;
            m += 1;
        }
        else if (num_ones == num_zeros) {
            filtered_list = ones_list;
            m += 1;
        }
    }

    string oxygen_generator_rating = filtered_list[0];  // filtered_list should only contain one value now
    int oxygen_generator_rating_dec = stoi(oxygen_generator_rating, nullptr, 2);
    cout << "The oxygen_generator_rating: binary = " << oxygen_generator_rating << ", decimal = " << oxygen_generator_rating_dec << endl;

    // use the function to loop over a filtered list until the filtered list becomes one value for c02 scrubber rating
    // essentially same code as above but switch the list that gets assigned to filtered list
    filtered_list = binary_list;  
    m = 0;
    while (filtered_list.size() != 1) {
        auto [num_zeros, num_ones, zeros_list, ones_list] = useful_data_out_for_position(filtered_list, m);
        if (num_zeros > num_ones) {
            filtered_list = ones_list;  // switch what list we assign for c02 scrubber rating
            m += 1;
        }
        else if (num_ones > num_zeros) {
            filtered_list = zeros_list;  // switch what list we assign for c02 scrubber rating
            m += 1;
        }
        else if (num_ones == num_zeros) {
            filtered_list = zeros_list;  // switch what list we assign for c02 scrubber rating
            m += 1;
        }
    }

    string c02_scrubber_rating = filtered_list[0];  // filtered_list should only contain one value now
    int c02_scrubber_rating_dec = stoi(c02_scrubber_rating, nullptr, 2);
    cout << "The c02_scrubber_rating: binary = " << c02_scrubber_rating << ", decimal = " << c02_scrubber_rating_dec << endl;

    int life_support_rating_dec = oxygen_generator_rating_dec * c02_scrubber_rating_dec;
    string life_support_rating = bitset<25>(oxygen_generator_rating_dec * c02_scrubber_rating_dec).to_string();
    cout << "The life_support_rating: binary = " << life_support_rating << ", decimal = " << life_support_rating_dec << endl;

};

