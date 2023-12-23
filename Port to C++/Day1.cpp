#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <numeric>

using namespace std;

int number_of_increasing_values(vector<int> val_list) {
    int num_increased = 0;
    for (int idx = 0; idx < val_list.size(); ++idx) {               // loop starting at zero up to size of vector
        if ((idx >= 1) && (val_list[idx] > val_list[idx - 1])) {    // if index is bigger than previous add one to num_increased
            num_increased += 1;
        }
    }
    return num_increased;
}

int main() {
    //Get the txt input
    ifstream myfile("..\\Personal txt Inputs\\Day1.txt");   //create an input stream object from file
    string line;                                            //create line object to read into
    vector<int> valuesList = {};                            //create vector of ints/strings
    while(getline(myfile, line)) {                          //read each line and cast to line variable
        int i_line = stoi(line);                            //cast string to int
        valuesList.push_back(i_line);                       //append line variable to valuesList vector
    }
    myfile.close();

    // Part 1
    int numIncreased = number_of_increasing_values(valuesList);
    cout << "The number of measurements larger than the previous for the raw data are: " << numIncreased << endl;

    // Part 2 
    int windowSize = 3;
    vector<int> movSum = {};
    for (int i = windowSize; i < valuesList.size()+1; ++i) {  //start at index windowSize, up to length of original list
        movSum.push_back(       // now append the sum of a subvector of size three using accumulate
                         accumulate(valuesList.begin()+i-windowSize, valuesList.begin()+i, 0) 
                        );      // index for arguments use the beginning of valuesList vector position, which we then add
                                // beginning position of sub vector and end position of subvector we want respectively
    }
    numIncreased = number_of_increasing_values(movSum);
    cout << "The number of measurements larger than the previous for the averaged data are: " << numIncreased << endl;
        
    return 0;
}