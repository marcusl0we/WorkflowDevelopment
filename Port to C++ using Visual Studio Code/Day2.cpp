#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <numeric>

//comment out below to practise using std:: everywhere as well as including below
//using namespace std;

auto get_positional_data_from_instructions(std::vector<std::string> instructions, bool part2) {
    int horizontal_pos = 0;
    int depth_pos = 0;
    int aim = 0;

    for (auto line : instructions) {        // short hand to loop through vector 'instructions', assigns each element to 'line'
        std::stringstream ss(line);         // create a variable stringstream from the variable 'line'
        std::string s;                      // create a variable to temp store each split word from stringstream
        std::vector<std::string> ss_split;  // create a variable to save each of those split words into vector of strings
        while(getline(ss, s, ' ')) {
            ss_split.push_back(s);          // append the split words to the vector string
        }
        
        struct DirectionAmount {                // create a structure to store the direction instruction and amount instruction
            std::string Direction;
            int Amount;
        };
        DirectionAmount decoded_line;           // instantiate an object of that structure
        decoded_line.Direction = ss_split[0];   // store the instructions from split stringstream to the structure appropriately
        decoded_line.Amount = stoi(ss_split[1]);


        // begin logic ported from python version and converted to use variables made above
        if (decoded_line.Direction == "forward") {
            horizontal_pos += int(decoded_line.Amount);
            if (part2) {
                depth_pos += aim * decoded_line.Amount;
            }
        }
            
        else if (decoded_line.Direction == "down") {
            if (part2) {
                aim += decoded_line.Amount;
            }
            else {
                depth_pos += decoded_line.Amount;
            }
        }
            
        else if (decoded_line.Direction == "up") {
            if (part2) {
                aim -= decoded_line.Amount;
            }
            else {
                depth_pos -= decoded_line.Amount;
            }
        }

    }

    struct ReturnVals {
        int _1;
        int _2;
        int _3;
    };
    return ReturnVals {horizontal_pos, depth_pos, aim};
}

int main() {
    //Get the txt input
    std::ifstream myfile("..\\Personal txt Inputs\\Day2.txt");   //create an input stream object from file
    std::string file_line;                                            //create line object to read into
    std::vector<std::string> instruction_list;                            //create vector of ints/strings
    while(getline(myfile, file_line)) {                          //read each line and cast to file_line variable
        instruction_list.push_back(file_line);                       //append file_line variable to vector
    }
    myfile.close();

    // Part 1
    auto [h_pos, d_pos, a] = get_positional_data_from_instructions(instruction_list, false);
    std::cout << "The Part 1 horizontal position is: " << h_pos << std::endl;
    std::cout << "The Part 1 depth position is: " << d_pos << std::endl;
    std::cout << "These numbers multiplied is: " << h_pos * d_pos << std::endl << "\n";

    // Part 2
    auto [h_pos2, d_pos2, a2] = get_positional_data_from_instructions(instruction_list, true);
    std::cout << "The Part 2 horizontal position is: " << h_pos2 << std::endl;
    std::cout << "The Part 2 depth position is: " << d_pos2 << std::endl;
    std::cout << "These numbers multiplied is: " << h_pos2 * d_pos2 << std::endl << "\n";
    
}