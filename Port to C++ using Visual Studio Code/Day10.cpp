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

int main () {
    ifstream myfile("..\\Personal txt Inputs\\Day10.txt");   //create an input stream object from file
    string file_line;                                       //create string object to read into
    vector<vector<char>> data;                                  //create vector of ints/strings
    while(getline(myfile, file_line)) {                     //read each line and cast to file_line variable
        vector<char> row;
        for (char character : file_line) {
            row.push_back(character);
        }
        data.push_back(row);
    }
    myfile.close();

    // Part 1 
    map<int, char> corrupted_dict;  // dict to store which lines are corrupted and what exception was

    // loop to process all lines
    for (int j = 0; j < data.size(); j++) {

        bool line_processed = false;
        vector<char> line = data[j];  // get a line from all lines

        while (!line_processed) {  // loop to process individual line down to error/incomplete
            for (int i = 0; i < line.size(); i++) {
                char character = line[i];  // get individual character in each line
                if (character == ')' && line[i-1] != '(') {  // check mismatched segment
                    corrupted_dict[j] = character;  // add mismatch to hashmap/dict and what line it was
                    line_processed = true;  // break while loop to go to next line
                    break;  // break for loop
                }
                else if (character == ')' && line[i-1] == '(') {  //  if segment is complete/valid remove it from line
                   line.erase(begin(line)+i-1, begin(line) + i+1);  // remove segment
                    break;  // break for loop to restart from line check from beginning
                }

                if (character == ']' && line[i-1] != '[') {
                    corrupted_dict[j] = character;
                    line_processed = true;
                    break;
                }
                else if (character == ']' && line[i-1] == '[') {
                    line.erase(begin(line)+i-1, begin(line) + i+1);
                    break;
                }

                if (character == '}' && line[i-1] != '{') {
                    corrupted_dict[j] = character;
                    line_processed = true;
                    break;
                }
                else if (character == '}' && line[i-1] == '{') {
                    line.erase(begin(line)+i-1, begin(line) + i+1);
                    break;
                }

                if (character == '>' && line[i-1] != '<') {
                    corrupted_dict[j] = character;
                    line_processed = true;
                    break;
                }
                else if (character == '>' && line[i-1] == '<') {
                    line.erase(begin(line)+i-1, begin(line) + i+1);
                    break;
                }
            }

            if ((find(begin(line), end(line), ')' ) != end(line))  ||
                (find(begin(line), end(line), ']' ) != end(line))  ||
                (find(begin(line), end(line), '}' ) != end(line))  ||
                (find(begin(line), end(line), '>' ) != end(line))) {  // check if line is incomplete after each removal
                    continue;  // continue removing segments until line is confirmed incomplete or is invalid
            }
            else {  // otherwise if none of those are in the line we can move on to next line
                data[j] = line;  // for part 2, turn original line to incomplete line
                line_processed = true;  // break while loop to move to next
            }

        }   
    }

    // now use the hash map to calculate score
    int syntax_error_score = 0;
    for (auto key : corrupted_dict){
        if (corrupted_dict[key.first] == ')'){
            syntax_error_score += 3;
        }
        if (corrupted_dict[key.first] == ']'){
            syntax_error_score += 57;
        }
        if (corrupted_dict[key.first] == '}'){
            syntax_error_score += 1197;
        }
        if (corrupted_dict[key.first] == '>'){
            syntax_error_score += 25137;
        }
        data[key.first] = vector<char>{' '};  // for part 2, discard the invalid lines
    }
    
    cout << "The total syntax error score is: " << syntax_error_score << endl;

    // Part 2
    vector<string> to_complete_lines;  // initialise vector to store strings that would complete incomplete lines

    // first complete all the incomplete lines
    for (int j = 0; j < data.size(); j++) {
        vector<char> line = data[j];
        if (line[0] == ' ') {
            continue;
        }
        else {
            string striinngg = ""; 
            for (int i = line.size() - 1; i >= 0; i--){  // loop over incomplete string from end to start
                if (line[i] == '(') {
                    striinngg += ')';
                }
                else if (line[i] == '{') {
                    striinngg += '}';
                }
                else if (line[i] == '[') {
                    striinngg += ']';
                }
                else if (line[i] == '<') {
                    striinngg += '>';
                }
            }
            to_complete_lines.push_back(striinngg);
        }
    }

    // then calculate the score for each string that would complete a line
    vector<long long> scores;

    for (string striinngg : to_complete_lines) {
        long long score = 0; 
        for (char character : striinngg){
            score = score * 5;
            if (character == ')') {
                score += 1;
            }
            if (character == ']') {
                score += 2;
            }
            if (character == '}') {
                score += 3;
            }
            if (character == '>') {
                score += 4;
            }
        }
        scores.push_back(score);
    }

    sort(begin(scores), end(scores));
    int middle = (scores.size() + 1)/2;

    cout << "The middle score is: " << scores[middle-1] << endl;

}
