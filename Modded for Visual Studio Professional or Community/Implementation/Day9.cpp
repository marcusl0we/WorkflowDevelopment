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
#include <set>

using namespace std;

// not modifiying input x and y points so have them as const references to orginal inputs
// but we are modifiying the original grid (passed in by reference) so we don't use const
int basin_search_from_point(const int& x, const int& y, vector<vector<int>>& grid, const vector<int>& dimensions) {
    int basin_add = 0;  // set number to add to be zero for if point is already 9, or marked as 100 and checked
    if (grid[x][y] == 100 || grid[x][y] == 9) {
        return basin_add;  // return zero to add and check next point
    }
    grid[x][y] = 100;  // if number isn't high point or marked 100 as point checked, mark it as point checked
    basin_add += 1;  // add one to the number of points converted to checked
    if (!(x == 0)) {  // check the number above the point
        basin_add += basin_search_from_point(x - 1, y, grid, dimensions);  // if number is marked as 100 or is 9, will add 0 to basin size
    }
    if (!(x == dimensions[0] - 1)) {  // then check the number below the point
        basin_add += basin_search_from_point(x + 1, y, grid, dimensions);
    }
    if (!(y == 0)) {  // then check the number to left of point
        basin_add += basin_search_from_point(x, y - 1, grid, dimensions);
    }
    if (!(y == dimensions[1] - 1)) {  /// then check number to right of point
        basin_add += basin_search_from_point(x, y + 1, grid, dimensions);
    }
    return basin_add;  // should return the cumulative addition from all the recursive calls
}

int Day9() {
    ifstream myfile("..\\Personal txt Inputs\\Day9.txt");   //create an input stream object from file
    string file_line;                                       //create string object to read into
    vector<vector<int>> grid;                                  //create vector of ints/strings
    while(getline(myfile, file_line)) {                     //read each line and cast to file_line variable
        vector<int> row;
        for (char character : file_line) {
            row.push_back(stoi(string{character}));
        }
        grid.push_back(row);
    }
    myfile.close();

    int rowsize = grid[0].size();
    int columnsize = grid.size();
    vector<int> dimensions;  // idk why doing dimensions{rowsize, columnsize} doesnt give the right numbers :(( so I'm using push_back
    dimensions.push_back(rowsize);
    dimensions.push_back(columnsize);

    int risk_level_sum = 0;  // initialise sum
    vector<vector<int>> lowest_points;  // for part 2
    for (int i = 0; i < dimensions[0]; i++) {
        for (int j = 0; j < dimensions[1]; j++) {
            int _above = 100;  // set numbers as high numbers if point doesn't exist e.g. beyond edge of map
            int _below = 100;
            int _left = 100;
            int _right = 100;

            if (!(i == 0)) {  // check the number above the point
                _above = grid[i - 1][j];
            }
            if (!(i == dimensions[0] - 1)) {  // then check the number below the point
                _below = grid[i + 1][j];
            }
            if (!(j == 0)) {  // then check the number to left of point
                _left = grid[i][j - 1];
            }
            if (!(j == dimensions[1] - 1)) {  // then check number to right of point
                _right = grid[i][j + 1];
            }

            int num_under_test = grid[i][j];

            if (num_under_test < _above &&
                num_under_test < _below &&
                num_under_test < _left &&
                num_under_test < _right) {
                    risk_level_sum += num_under_test + 1;
                    lowest_points.push_back(vector<int>{i, j});  // make a list of lowest points for part 2
                }
        }
    }

    cout << "The sum of the risk levels are: " << risk_level_sum << endl;

    // Part 2
    vector<int> sizes;
    for (auto point : lowest_points) {
        int _x = point[0];
        int _y = point[1];
        sizes.push_back(basin_search_from_point(_x, _y, grid, dimensions));
    }
    // sort vector in decreasing order, third argument specfies this
    sort(begin(sizes), end(sizes), greater<int>());

    cout << "The multiplication of the three largest basins are: "  << sizes[0] * sizes[1] * sizes[2] << endl;

    return 0;
}
