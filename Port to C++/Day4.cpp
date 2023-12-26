#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>

using namespace std;

// function to check rows and columns of a card to see if bingo is achieved
int card_winner_check(vector<vector<int>> i_card) {
    for (int idx = 0; idx < i_card.size(); idx++) {

        // rows are easy to extract to check
        vector<int> row_extract = i_card[idx];

        // but columns need a separate loop as below
        vector<int> column_extract;
        for (auto x : i_card){
            column_extract.push_back(x[idx]);
        }

        // SUM EXTRACTED VECTOR AND IF == 5 WE KNOW ALL VALUES ARE TRUE
        if ( accumulate(row_extract.begin(), row_extract.end(), 0) == 5 ) { //if code will execute if all true
            return 1;
        }
        else if ( accumulate(column_extract.begin(), column_extract.end(), 0) == 5 ) { //else if code will execute if all true
            return 1;
        }

        // // ALTERNATE METHOD, LOCATE IF ANY FALSE VALUES EXIST IN EXTRACTED VECTOR TO TEST IF ALL ARE TRUE
        // if ( find(row_extract.begin(), row_extract.end(), false) == row_extract.end() ) { //if code will execute if all true
        //     return 1;
        // }
        // else if ( find(column_extract.begin(), column_extract.end(), false) == column_extract.end() ) { //else if code will execute if all true
        //     return 1;
        // }

    }
    return 0;
}

// structure to save row and column info of a located number and where it is on card
struct row_col_info {
    int row;
    int column;
};

// function returns a vector of row_col_info as idk if a card will have that number more than once? 
// idk tbf cos i assume later that theres only one and only use the first item in this vector anyway
vector<row_col_info> np_where(vector<vector<int>>  card, int item){
    vector<row_col_info> find;
    row_col_info located;

    for (int row = 0; row < card.size(); row++) {
        for (int column = 0; column < card[row].size(); column++) {
            if (card[row][column] == item) {
                located.row = row;
                located.column = column;
                find.push_back(located);
            }
        }
    }

    return find;
}

int main () {
    //Get the txt input
    ifstream myfile("..\\Personal txt Inputs\\Day4.txt");   //create an input stream object from file
    string file_line;                                       //create string object to read into
    vector<string> data;                                    //create vector of ints/strings
    while(getline(myfile, file_line)) {                     //read each line and cast to file_line variable
        data.push_back(file_line);                          //append file_line variable to vector
    }
    myfile.close();

    // format the first line of the input text into vector<int> ss_split
    string line = data[0];
    stringstream ss(line);          // create a stringstream from the variable 'line'
    string s;                       // create a variable to temp store each split word from stringstream
    vector<int> bingo_numbers;      // create a variable to save each of those split words into vector of strings
    int x;
    while(getline(ss, s, ',')) {
        x = stoi(s);
        bingo_numbers.push_back(x); // append the split words to the vector string
    }

    // reformat matrices in .txt to proper list of integer matrix rows
    data.erase(data.begin());   // pop/remove the first element in vector
    vector<vector<int>> data2;  // create new vector of vectors to turn string lists from as c++ preallocates and cant overwrite original data
    for (auto x : data){
        if (x != "") {
            line = x;
            stringstream sss(line);
            vector<int> int_matrix_row;
            int xx;
            while(getline(sss, s, ' ')) {
                if (s != "") {    // added as the getline function doesnt take multiple delimiters and we have both " " and "  ".
                    xx = stoi(s);
                    int_matrix_row.push_back(xx); // append the split words to the vector of ints
                }
            }
            data2.push_back(int_matrix_row);  // list of all integer matrix rows
        }
    }

    // reformat matrix rows to proper list of full matrices
    // also initialise truth matrices for marking numbers as they happen
    int card_size = 5;
    vector<vector<vector<int>>> bingo_cards;
    vector<vector<vector<int>>> bingo_cards_marked;
    for (int i = 0; i < data2.size(); i = i + card_size) {

        // each item in bingo_cards list is a 5x5 card
        bingo_cards.push_back(vector<vector<int>>(data2.begin() + i, data2.begin() + i + card_size));

        // each item in bingo_cards_marked list is a 5x5 truth table, initialised all False/0
        bingo_cards_marked.push_back(
                                    vector<vector<int>> (card_size,
                                                         vector<int>(card_size, 0))
                                    );
    }

    // initialise list of card totals for all cards, list index corresponds to card number in .txt input
    vector<int> card_total;
    for (int i = 0; i < bingo_cards.size(); i++) {
        vector<vector<int>> card = bingo_cards[i];
        int sum = accumulate(card.begin(), card.end(), 0, 
                             [](int acc, const vector<int>& row) {  // c++ lambda function to get sum of each row before summing all rows
                                return acc + accumulate(row.begin(), row.end(), 0);
                                }
                            );
        card_total.push_back(sum);
    }

    // create a struct with a board number and the number that cause win, replaces the python dict
    struct winning_board {
        int board;
        int winning_num;
    };
 
    // vector of that stuct we just made
    vector<winning_board> order_of_winning_boards;
    for (int num : bingo_numbers) {
        for (int ii = 0; ii < bingo_cards.size(); ii++) {
            vector<vector<int>> card = bingo_cards[ii];

            // use custom function to return vector (if multiple matches) of locations of num inside card
            vector<row_col_info> find = np_where(card, num);

            if (find.size() > 0) {
                int row = find[0].row;
                int column = find[0].column;

                // minus found number from card cumulative sum to get sum of unmarked numbers after card win
                card_total[ii] = card_total[ii] - card[row][column];

                // multidimensional index format: bingo_cards_marked[card ID][card row][card column]
                bingo_cards_marked[ii][row][column] = 1;
                int bingo = card_winner_check(bingo_cards_marked[ii]);

                if (bingo != 0) {  // bingo == 1 means card has won
                    order_of_winning_boards.push_back(winning_board{ii, num});

                    // as the card has now won, no need to do any further operations so can discard by setting to all card nums to 999
                    // 999 is a number that we assume will never occur in input so its a bit dirty to do this way but eh, not as nice as python
                    bingo_cards[ii] = vector<vector<int>> (card_size,
                                                           vector<int>(card_size, 999));
                    bingo_cards_marked[ii] = vector<vector<int>> (card_size,
                                                                  vector<int>(card_size, 999));
                    // code above needs to be done otherwise the next number on bingo_numbers list can trigger repeat operations on old already won card 
                }
            }
        }
    }

    int first_win_idx = order_of_winning_boards[0].board;
    int first_win_num = order_of_winning_boards[0].winning_num;

    int last_win_idx = order_of_winning_boards.back().board;
    int last_win_num = order_of_winning_boards.back().winning_num;

    // Part 1
    cout << "The first winning card has an unmarked number sum of " << card_total[first_win_idx] << ", " <<
            "multiplied by the bingo number of " << first_win_num << " is " << card_total[first_win_idx]*first_win_num << endl;

    // Part 2
    cout << "The last winning card has an unmarked number sum of " << card_total[last_win_idx] << ", " <<
            "multiplied by the bingo number of " << last_win_num << " is " << card_total[last_win_idx]*last_win_num << endl;

}