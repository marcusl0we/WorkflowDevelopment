#include <vector>
#include <string>

#include"declarations.h"

using namespace std;

// function returns a vector of row_col_info, mimics Python numpy.where function but in a nicer format
vector<row_col_info> np_where(vector<vector<int>>  matrix, int item, string equality) {
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