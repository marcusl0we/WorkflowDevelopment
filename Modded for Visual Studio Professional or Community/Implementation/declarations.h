#pragma once

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// DECLARATIONS FOR np_where
// structure to save row and column info of a located number and where it is in matrix
struct row_col_info {
    int row;
    int column;

    // added an operator function to allow the find function to locate this struct
    bool operator==(const row_col_info& other) const {
        return row == other.row && column == other.column;
    }
};
vector<row_col_info> np_where(vector<vector<int>>  matrix, int item, string equality = "==");

// DECLARATIONS FOR Day1
int number_of_increasing_values(vector<int> val_list);
int Day1();

// DECLARATIONS FOR Day2
auto get_positional_data_from_instructions(std::vector<std::string> instructions, bool part2);
int Day2();

// DECLARATIONS FOR Day3
auto useful_data_out_for_position(vector<string> bin_list, int position);
int Day3();

// DECLARATIONS FOR Day4
int card_winner_check(vector<vector<int>> i_card);
int Day4();

// DECLARATIONS FOR Day5
int Day5();

// DECLARATIONS FOR Day6
vector<int> get_input_from_data();
int Day6();

// DECLARATIONS FOR Day7
int Day7();

// DECLARATIONS FOR Day8
auto input_decipher(vector<string> input_under_test);
int Day8();

// DECLARATIONS FOR Day9
int basin_search_from_point(const int& x, const int& y, vector<vector<int>>& grid, const vector<int>& dimensions);
int Day9();

// DECLARATIONS FOR Day10
int Day10();

// DECLARATIONS FOR Day11
void octo_flash(vector<row_col_info>& flash, vector<vector<int>>& _grid, const vector<int>& dimensions);
struct flash_stepper_info {
    int num_flashes;
    int full_grid_flash;
    // this ^^ was a boolean in python that then has variable type changed to int
    // this is bad as we cannot cast declared bool to int value in c++
    // only value of 1 will be added instead of anything more than 1 when needed
    vector<vector<int>> _grid;
};
flash_stepper_info flash_stepper(const int& n, vector<vector<int>>& _grid, const vector<int>& dimensions, const int& grid_size);
int Day11();

// DECLARATIONS FOR Day12
int count_paths(vector<string>& path, bool& print_output);
bool cave_not_been_visited(string& x, vector<string>& path, string Part_1_or_2);
int find_paths(const unordered_map<string, vector<string>>& graph, const string source, const string destination, const string Part_1_or_2);
int Day12();
