#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <numeric>
#include <regex>
#include <algorithm>

using namespace std;

class HydroThermalVent {
    // declare class attributes
    public:
    int x1;
    int x2;
    int y1;
    int y2;
    vector<int> coverage_x;
    vector<int> coverage_y;

    HydroThermalVent(int input_x1, int input_y1, int input_x2, int input_y2) 
        : x1(input_x1), y1(input_y1), x2(input_x2), y2(input_y2)  // c++ initialization list instead of doing in constructor           
        {
        // // set up contstructor of a hydrothermal vent line with the line end point coordinates and line coverage list
        // x1 = input_x1;
        // x2 = input_x2;
        // y1 = input_y1;
        // y2 = input_y2;

        // depending on which line type it is use a different method to get coverage
        if ((x1 == x2) || (y1 == y2)) {
            _vent_straight_line_coverage();
        }
        else {
            _vent_diagonal_line_coverage();
        }
    }

    private:
    void _vent_straight_line_coverage() {
        if (x1 == x2){  // straight lines have one or other coordinate the same
            int start = min(y1, y2);
            int end = max(y1, y2) + 1;
            for (int num = start; num < end; num++) {  // so update the other coordinate coverage list accordingly
                coverage_y.push_back(num);
                coverage_x.push_back(x1);
            }
        }
        else if (y1 == y2) {  // do the same for the y coord
            int start = min(x1, x2);
            int end = max(x1, x2) + 1;
            for (int num = start; num < end; num++) {
                coverage_x.push_back(num);
                coverage_y.push_back(y1);
            }
        }
    }

    void _vent_diagonal_line_coverage() {
        int start_x = x1; 
        int end_x = x2; 
        int start_y = y1; 
        int end_y = y2;
        int step_x;
        int step_y;
        if (start_x < end_x) {  // use this to get for loop step values accordingly, step will either be +ve or -ve
            step_x = 1;
            end_x = end_x + 1;  // done to include the end coordinate in the coverage list
        }
        else {
            step_x = -1;
            end_x = end_x - 1;
        }
        if (start_y < end_y) {  // do the same for y coord
            step_y = 1;
            end_y = end_y + 1;
        }
        else {
            step_y = -1;
            end_y = end_y - 1;
        }
        for (int numX = start_x; numX != end_x; numX = numX + step_x) {  // add x and y coord for diagonals to the coverage list
            coverage_x.push_back(numX);
        }
        for (int numY = start_y; numY != end_y; numY = numY + step_y) {
            coverage_y.push_back(numY);
        }
    }

};

class HydrothermalVentDiagram{
    public:
    vector<vector<int>> diagram;

    HydrothermalVentDiagram() {
        int size = 1000;
        diagram = vector<vector<int>> (size,
                                       vector<int>(size, 0));  // initialise empty diagram when object created
    }

    void update(HydroThermalVent vent) {  // method to update the diagram with a specific vent object
        for (int i = 0; i < vent.coverage_x.size(); i++) {
            int column = vent.coverage_x[i];
            int row = vent.coverage_y[i];
            diagram[row][column] += 1;
        }
    }
};

// structure to save row and column info of a located number and where it is in matrix
struct row_col_info {
    int row;
    int column;
};

// function returns a vector of row_col_info as idk if a matrix will have that number more than once?
vector<row_col_info> np_where(vector<vector<int>>  matrix, int item, string equality = "==") {
    vector<row_col_info> find;
    row_col_info located;

    for (int row = 0; row < matrix.size(); row++) {
        for (int column = 0; column < matrix[row].size(); column++) {
            if (equality == "==") {
                if (matrix[row][column] == item) {
                    located.row = row;
                    located.column = column;
                    find.push_back(located);
                }
            }
            else if (equality == ">=") {
                if (matrix[row][column] >= item) {
                    located.row = row;
                    located.column = column;
                    find.push_back(located);
                }
            }
        }
    }

    return find;
}

int main() {
    //Get the txt input
    ifstream myfile("..\\Personal txt Inputs\\Day5.txt");   //create an input stream object from file
    string file_line;                                       //create string object to read into
    vector<vector<int>> data;                               //create vector of ints/strings
    while(getline(myfile, file_line)) {                     //read each line and cast to file_line variable
        // str.replace(str.find(str2),str2.length(),str3);     // str is the base string, str2 is the sub string to find, str3 is the replacement substring
        // file_line.replace(file_line.find(" -> "), file_line.length(), ",");
        file_line = regex_replace(file_line, std::regex(" -> "), ",");
        stringstream ss(file_line);                         // create a stringstream from the variable
        string s;                                           // create a variable to temp store each split word from stringstream
        vector<int> data_ints;                              // create a variable to save each of those split words into vector of ints
        int x;
        while(getline(ss, s, ',')) {                        // split string via the ','
            x = stoi(s);
            data_ints.push_back(x);                         // append the split words to the vector
        }
        data.push_back(data_ints);                          //append file_line variable to vector
    }
    myfile.close();

    // create two diagram object instances for part one and two
    HydrothermalVentDiagram part1_diagram;
    HydrothermalVentDiagram part2_diagram;

    for (auto vent_idx : data) {
        int x_1 = vent_idx[0]; int y_1 = vent_idx[1]; int x_2 = vent_idx[2]; int y_2 = vent_idx[3];
        HydroThermalVent hydrothermal_vent(x_1, y_1, x_2, y_2);  // create a vent object instance
        if ((x_1 == x_2) || (y_1 == y_2)) {  // only update the part 1 diagram if the vent is horizontal or vertical
            part1_diagram.update(hydrothermal_vent);
        }
        part2_diagram.update(hydrothermal_vent);  // otherwise, part 2 diagram will update for all vents
    }

    vector<row_col_info> part1_bigger_than_2 = np_where(part1_diagram.diagram, 2, ">=");  // find where at least two vents overlap
    int part1_bigger_than_2_count = part1_bigger_than_2.size();
    cout << "The num. of overlapping points for horizontal/vertical hydrothermal vent lines are: " << part1_bigger_than_2_count << endl;

    vector<row_col_info> part2_bigger_than_2 = np_where(part2_diagram.diagram, 2, ">=");  // find where at least two vents overlap
    int part2_bigger_than_2_count = part2_bigger_than_2.size();
    cout << "The num. of overlapping points for all hydrothermal vent lines are: " << part2_bigger_than_2_count << endl;

}