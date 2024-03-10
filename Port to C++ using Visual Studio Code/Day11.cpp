#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <numeric>
#include <regex>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

// structure to save row and column info of a located number and where it is in matrix
struct row_col_info {
    int row;
    int column;

    // added an operator function to allow the find function to locate this struct
    bool operator==(const row_col_info &other) const {
        return row == other.row && column == other.column;
    }
};

// function returns a vector of row_col_info, mimics Python numpy.where function but in a nicer format
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

void octo_flash(vector<row_col_info> &flash, vector<vector<int>> &_grid, const vector<int> &dimensions){
    for (int j = 0; j < flash.size(); j++) {  // loop over each octopus ready to flash
        int flash_loc_x = flash[j].row;
        int flash_loc_y = flash[j].column;

        // check edge cases
        if ( (flash_loc_x == 0) && (flash_loc_y == 0) ) {  // top left position edge case
            _grid[flash_loc_x][flash_loc_y + 1] += 1;  // number to the right
            _grid[flash_loc_x + 1][flash_loc_y + 1] += 1;  // number to the bottom right
            _grid[flash_loc_x + 1][flash_loc_y] += 1;  // number below
        }
        else if ( (flash_loc_x == 0) && (flash_loc_y == dimensions[1]) ) {  // top right position edge case
            _grid[flash_loc_x][flash_loc_y - 1] += 1;  // number to the left
            _grid[flash_loc_x + 1][flash_loc_y - 1] += 1;  //number to the bottom left
            _grid[flash_loc_x + 1][flash_loc_y] += 1;  // number below
        }
        else if ( (flash_loc_x == dimensions[0]) && (flash_loc_y == 0) ) {  //bottom left position edge case
            _grid[flash_loc_x - 1][flash_loc_y] += 1;  // number above
            _grid[flash_loc_x - 1][flash_loc_y + 1] += 1;  // number to the top right
            _grid[flash_loc_x][flash_loc_y + 1] += 1;  // number to the right
        }
        else if ( (flash_loc_x == dimensions[0]) && (flash_loc_y == dimensions[1]) ) {  // bottom right position edge case
            _grid[flash_loc_x - 1][flash_loc_y] += 1;  // number above
            _grid[flash_loc_x - 1][flash_loc_y - 1] += 1;  // number to the top left
            _grid[flash_loc_x][flash_loc_y - 1] += 1;  // number to the left
        }
        // edge of map edge cases?- if one coordinate happens to be on one of the 4 edges of map
        else if ( (flash_loc_x == 0) && (1 <= flash_loc_y) && (flash_loc_y < dimensions[1])) {
            _grid[flash_loc_x][flash_loc_y - 1] += 1;  // number to the left
            _grid[flash_loc_x + 1][flash_loc_y - 1] += 1;  // number to the bottom left
            _grid[flash_loc_x + 1][flash_loc_y] += 1;  // number below
            _grid[flash_loc_x + 1][flash_loc_y + 1] += 1;  // number to the bottom right
            _grid[flash_loc_x][flash_loc_y + 1] += 1;  // number to the right
        }
        else if ( (flash_loc_x == dimensions[0]) && (1 <= flash_loc_y) && (flash_loc_y < dimensions[1]) ) {
            _grid[flash_loc_x][flash_loc_y - 1] += 1;  // number to the left
            _grid[flash_loc_x - 1][flash_loc_y - 1] += 1;  // number to the top left
            _grid[flash_loc_x - 1][flash_loc_y] += 1;  // number above
            _grid[flash_loc_x - 1][flash_loc_y + 1] += 1;  // number to the top right
            _grid[flash_loc_x][flash_loc_y + 1] += 1;  //number to the right
        }
        else if ( (1 <= flash_loc_x) && (flash_loc_x < dimensions[0]) && (flash_loc_y == 0) ) {
            _grid[flash_loc_x - 1][flash_loc_y] += 1;  // number above
            _grid[flash_loc_x - 1][flash_loc_y + 1] += 1;  // number to the top right
            _grid[flash_loc_x][flash_loc_y + 1] += 1;  // number to the right
            _grid[flash_loc_x + 1][flash_loc_y + 1] += 1;  // number to the bottom right
            _grid[flash_loc_x + 1][flash_loc_y] += 1;  // number below
        }
        else if ( (1 <= flash_loc_x) && (flash_loc_x < dimensions[0]) && (flash_loc_y == dimensions[1]) ) {
            _grid[flash_loc_x - 1][flash_loc_y] += 1;  // number above
            _grid[flash_loc_x - 1][flash_loc_y - 1] += 1;  // number to the top left
            _grid[flash_loc_x][flash_loc_y - 1] += 1;  // number to the left
            _grid[flash_loc_x + 1][flash_loc_y - 1] += 1;  // number to the bottom left
            _grid[flash_loc_x + 1][flash_loc_y] += 1;  // number below
        }
        else {  // normal flash not any of edge cases
            _grid[flash_loc_x - 1][flash_loc_y] += 1;  // number above
            _grid[flash_loc_x - 1][flash_loc_y + 1] += 1;  // number to the top right
            _grid[flash_loc_x][flash_loc_y + 1] += 1;  // number to the right
            _grid[flash_loc_x + 1][flash_loc_y + 1] += 1;  // number to the bottom right
            _grid[flash_loc_x + 1][flash_loc_y] += 1;  // number below
            _grid[flash_loc_x + 1][flash_loc_y - 1] += 1;  // number to the bottom left
            _grid[flash_loc_x][flash_loc_y - 1] += 1;  // number to the left
            _grid[flash_loc_x - 1][flash_loc_y - 1] += 1;  // number to the top left
        }

        for (int k = 0; k < flash.size(); k++) {  // loop over each octopus ready to flash
            int reset_x = flash[k].row;
            int reset_y = flash[k].column;
            _grid[reset_x][reset_y] = 0;  // reset each octopus to zero every time an original octo flashes
        }
    }
}

struct flash_stepper_info {
    int num_flashes;
    int full_grid_flash;
    // this ^^ was a boolean in python that then has variable type changed to int
    // this is bad as we cannot cast declared bool to int value in c++
    // only value of 1 will be added instead of anything more than 1 when needed
    vector<vector<int>> _grid;
};

// here we pass in by reference to the function as we want to modify the original grid passed in
// default in C++ does the equivalent to deepcopy in Python
// whereas default in Python does pass in by reference
flash_stepper_info flash_stepper(const int &n, vector<vector<int>> &_grid, const vector<int> &dimensions, const int &grid_size) {
    int num_flashes = 0;
    int full_grid_flash = 0;  // for part 2
    for (int i = 0; i < n; i++) {  // main loop to execute for n number of steps
        vector<row_col_info> pre_flash = np_where(_grid, 9, ">=");  // returns a vector of coordinates, row_col_info

        // in Python we have: _grid = _grid + 1
        // need to do this line in c++ eqivalent
        for (int i = 0; i < _grid.size(); i++) {
            for_each(_grid[i].begin(), _grid[i].end(), [](int &n){ n+=1; });
        }

        if (pre_flash.size() == 0) {  // means none ready to flash in this step so continue
            continue;
        }
        else {
            // pre_flash = [[pre_flash[0][x], pre_flash[1][x]] for x in range(len(pre_flash[1]))]
            // ^^ this line from python not needed here due to how I implmented np_where already as a vector of coordinates, row_col_info
            
            // flash the octopuses that are ready to be flashed
            octo_flash(pre_flash, _grid, dimensions);

            // add list of pre_flash to a list that tells us which ones have already flashed and can't flash again
            vector<row_col_info> do_not_flash_again = pre_flash;
            
            // check adjacent flash causing an unintended flash
            bool until_no_flash = true;
            while (until_no_flash) {
                vector<row_col_info> unint_flash = np_where(_grid, 10, ">=");
                if (unint_flash.size() != 0) {  // this means there are still existing octos to be flashed

                    // only add extra flash if unintentional flash not already flashed in pre flash by comparing
                    // done in Python with line:
                    // extra_flash = [unint_flash[x] for x in range(len(unint_flash)) if not unint_flash[x] in do_not_flash_again]
                    // ^^ this list comprehension needs deconstructing in c++
                    vector<row_col_info> extra_flash;
                    for (int x = 0; x < unint_flash.size(); x++) {
                        if ( find(do_not_flash_again.begin(), do_not_flash_again.end(), unint_flash[x]) == do_not_flash_again.end() ) {
                            extra_flash.push_back(unint_flash[x]);
                        }
                    }
                    octo_flash(extra_flash, _grid, dimensions);
                    do_not_flash_again.insert(do_not_flash_again.end(), extra_flash.begin(), extra_flash.end());
                    
                    // still need to make sure flashed octos at each step are returned to value of 0 so do this again
                    for (int k = 0; k < do_not_flash_again.size(); k++) {
                        int reset_x = do_not_flash_again[k].row;
                        int reset_y = do_not_flash_again[k].column;
                        _grid[reset_x][reset_y] = 0;  // reset each octopus to zero every time an original octo flashed
                    }

                }
                else {
                    until_no_flash = false;
                }
            }
        }

        vector<row_col_info> flashed = np_where(_grid, 0, "==");  // find if any have flashed
        num_flashes += flashed.size();  // add to number of flashes if there are

        // for part 2, in it is here where the bool gets converted to int which is not possible in c++
        // so we have it directly as int from start in c++, check variable == 0 later
        if (flashed.size() == grid_size) {  // check if the whole grid has flashed
            full_grid_flash = i + 1;  // turn index to step number to add later on
        }

    }
    return {num_flashes, full_grid_flash, _grid};
}

int main () {
    ifstream myfile("..\\Personal txt Inputs\\Day11.txt");   //create an input stream object from file
    string file_line;                                       //create string object to read into
    vector<vector<int>> grid;                                  //create vector of ints/strings
    while(getline(myfile, file_line)) {                     //read each line and cast to file_line variable
        vector<int> row;
        for (char character : file_line) {
            string s(1, character);
            row.push_back(stoi(s));
        }
        grid.push_back(row);
    }
    myfile.close();

    // Part 1
    int grid_rows = grid[1].size();
    int grid_columns = grid.size();
    vector<int> dimensions = {grid_rows, grid_columns};  // get dimensions of map
    int grid_size = dimensions[0] * dimensions[1];  // for part 2
    dimensions = {dimensions[0]-1, dimensions[1]-1};  // turn dimensions into index limits

    int number_of_steps = 100;

    flash_stepper_info info_out = flash_stepper(number_of_steps, grid, dimensions, grid_size);
    int number_of_flashes = info_out.num_flashes;
    int full_flash = info_out.full_grid_flash;
    vector<vector<int>> grid_at_end = info_out._grid;

    cout << "The number of flashes after " << number_of_steps << " steps are: " << number_of_flashes << endl;

    // Part 2
    int increment_steps = 10;
    while (full_flash == 0) {

        flash_stepper_info info_out = flash_stepper(increment_steps, grid_at_end, dimensions, grid_size);
        number_of_flashes = info_out.num_flashes;
        full_flash = info_out.full_grid_flash;
        grid_at_end = info_out._grid;
        
        if (full_flash == 0) {
            number_of_steps += increment_steps;
        }
    }
    int step_no = number_of_steps + full_flash;

    cout << "The first time the full grid flashed simultaneously was at step " << step_no << endl;
    
}
