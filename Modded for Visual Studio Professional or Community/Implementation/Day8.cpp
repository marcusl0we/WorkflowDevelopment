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

// # 0 abcefg  6
// # 1 cf      2
// # 2 acdeg   5
// # 3 acdfg   5
// # 4 bcdf    4
// # 5 abdfg   5
// # 6 abdefg  6
// # 7 acf     3
// # 8 abcdefg 7
// # 9 abcdfg  6

// # LETTERED DIAGRAM:
// #   AAAA
// #  B    C
// #  B    C
// #   DDDD
// #  E    F
// #  E    F
// #   GGGG

// big function to decode input
auto input_decipher(vector<string> input_under_test){
    set<char> _zero, _one, _two, _three, _four, _five, _six, _seven, _eight, _nine;
    vector<char> diff;
    char seg_A_confirmed;
    char seg_E_opt1;
    char seg_E_opt2;
    char seg_G_opt1;
    char seg_G_opt2;

    // first, deduce the unique char length numbers
    for (string inp : input_under_test) {
        if (inp.length() == 2) {  // unique length of 2 is trying to output one
            // //loop to manually add each char to a vector and then convert it all to a set 
            // vector<char> one;
            // for (char character : inp) {
            //     one.push_back(character);
            // }
            // _one = set<char>(begin(one), end(one));
            
            // or just use the insert function in set. can directly use set<char> instead of list comprehension and
            // then conversion to set like in python
            for (char character : inp) {
                _one.insert(character);
            }
            break;
        }
    }
    for (string inp : input_under_test) {
        if (inp.length() == 3) {  // unique length of 3 is trying to output seven
            for (char character : inp) {
                _seven.insert(character);
            }
            diff.clear();  // clear the diff variable to reset it and recalculate difference in sets
            set_difference(_seven.begin(), _seven.end(), _one.begin(), _one.end(),
                            inserter(diff, diff.end()));  // insert set difference to the diff vector
            // we know this segment difference is segment A in the diagram
            seg_A_confirmed = diff[0];  // set is non subscriptable, vectors are.
            break;
        }
    }
    for (string inp : input_under_test) {
        if (inp.length() == 4) {  // unique length of 4 is trying to output four
            for (char character : inp) {
                _four.insert(character);
            }
            break;
        }
    }
    for (string inp : input_under_test) {
        if (inp.length() == 7) {  // unique length of 7 is trying to output eight
            for (char character : inp) {
                _eight.insert(character);
            }

            // use the segment difference between numbers eight and four to get options for segment E and G
            diff.clear();
            set_difference(_eight.begin(), _eight.end(), _four.begin(), _four.end(),
                            inserter(diff, diff.end()));
            
            // remove a confirmed segment we already know is true to refine options
            // c++ erase remove method to locate a certain element in vector and remove it?
            diff.erase(remove(diff.begin(), diff.end(), seg_A_confirmed), diff.end());
            seg_E_opt1 = diff[0];
            seg_E_opt2 = diff[1];
            seg_G_opt1 = diff[0];
            seg_G_opt2 = diff[1];
            break;
        }
    }

    // now we can further deduce segment options for numbers that use 5 segments
    vector<set<char>> possible_235;   // numbers that use 5 segments are two, three and five
    for (string inp : input_under_test) {
        if (inp.length() == 5) {  // this is trying to output either two, three and five
            set<char> tempset;
            for (char character : inp) {
                tempset.insert(character);
            }
            possible_235.push_back(tempset);  // vector of sets, same as the list of sets in python
        }
    }
    
    for (set<char> x : possible_235) {  // now loop over those numbers and do a difference to known numbers to deduce more numbers
        diff.clear();
        set_difference(x.begin(), x.end(), _one.begin(), _one.end(),
                            inserter(diff, diff.end()));
        if (diff.size() == 3) {  //we know a difference of 3 segments between five seg numbers and two seg number has to make that number a three
            _three = x;
            possible_235.erase(remove(possible_235.begin(), possible_235.end(), _three), possible_235.end());
            break;
        }
    }

    // the two remaining numbers of two and five in possible_235 can be better compared to segments of four
    for (set<char> x : possible_235) {
        diff.clear();
        set_difference(x.begin(), x.end(), _four.begin(), _four.end(),
                            inserter(diff, diff.end()));
        diff.erase(remove(diff.begin(), diff.end(), seg_A_confirmed), diff.end());
        if (diff.size() == 2) {
            _two = x;
            possible_235.erase(remove(possible_235.begin(), possible_235.end(), _two), possible_235.end());
            break;
        }
    }
    _five = possible_235[0];  // last one has to be segments for five

    // now we use newly found number of three to compare against other known numbers to confirm previous segment options
    diff.clear();
    set_difference(_three.begin(), _three.end(), _four.begin(), _four.end(),
                            inserter(diff, diff.end()));
    // narrow down known segments to better match unknown segments                            
    diff.erase(remove(diff.begin(), diff.end(), seg_A_confirmed), diff.end());
    char seg_G_confirmed = diff[0];  // now we can confirm the options we had for segments E and G
    char seg_E_confirmed;
    if (seg_G_confirmed == seg_G_opt1) {
        seg_E_confirmed = seg_E_opt2;
    }
    else if (seg_G_confirmed == seg_G_opt2) {
        seg_E_confirmed = seg_E_opt1;
    }

    // finally deduce numbers for 6 segment numbers
    vector<set<char>> possible_069;
    for (string inp : input_under_test) {
        if (inp.length() == 6) {   // this is trying to output either zero, six, or nine
            set<char> tempset;
            for (char character : inp) {
                tempset.insert(character);
            }
            possible_069.push_back(tempset);
        }
    }
    for (set<char> x : possible_069) {
        diff.clear();
        set_difference(x.begin(), x.end(), _five.begin(), _five.end(),
                            inserter(diff, diff.end()));
        if (diff.size() == 2) {  // number of segments difference of 2 when compared to number five has to be number zero
            _zero = x;
            continue;
        }
        else if (diff.size() == 1) {  // otherwise number of segments difference of 1 could be either six or nine
            if (diff[0] == seg_E_confirmed) {
                _six = x;
            }
            else {
                _nine = x;
            }
        }
    }
    int fin = 0;

    struct returnvals {
        set<char> _0; set<char> _1; set<char> _2; set<char> _3; set<char> _4; set<char> _5; set<char> _6; set<char> _7; set<char> _8; set<char> _9;
    };
    return returnvals{_zero, _one, _two, _three, _four, _five, _six, _seven, _eight, _nine};
}

int Day8() {
    ifstream myfile("..\\Personal txt Inputs\\Day8.txt");   //create an input stream object from file
    string file_line;                                       //create string object to read into
    vector<string> output;                                  //create vector of ints/strings
    vector<vector<string>> seg_input;
    vector<vector<string>> seg_output;
    while(getline(myfile, file_line)) {                     //read each line and cast to file_line variable
        stringstream ss(file_line);                         // create a stringstream from the variable
        string s;                                           // create a variable to temp store each split word from stringstream
        vector<string> segments;
        while(getline(ss, s, ' ')) {                        
            segments.push_back(s);                          // parse each line into list of strings
        }
        
        // split each line into sub vectors before and after seperator "|"
        vector<string> pre_seperator(begin(segments), begin(segments) + 10);
        vector<string> post_seperator(begin(segments) + 11, end(segments));
        
        // // flatten all the strings post seperator into one long vector to easily iterate over
        // for (string x : post_seperator) {
        //     output.push_back(x);
        // }
        output.insert(end(output), begin(post_seperator), end(post_seperator));  // different way to flatten it 

        // turn input text into vector of vectors of strings
        seg_input.push_back(pre_seperator);
        seg_output.push_back(post_seperator);
        
    }
    myfile.close();

    // Part 1
    // c++ lambda equivalent to the python one, add to the count if lambda function return true
    int num_unique_uses = count_if(begin(output), end(output),[](string x){ // c++ lambda function
                                                                           return (x.length()==2 || x.length()==4 || x.length()==3 || x.length()==7);
                                                                          }
                                  );

    cout << "The number of times the digits 1,4,7 and 8 appear are " << num_unique_uses << endl;

    // Part 2
    vector<int> displays;

    for (int i = 0; i < seg_input.size(); i++) {
        vector<string> inp_under_test = seg_input[i];
        auto [zero, one, two, three, four, five, six, seven, eight, nine] = input_decipher(inp_under_test);
        string disp_str = "";  // initialise the individual display number as a string to cast to int later
        for (string out_str : seg_output[i]) {
            set<char> out;
            for (char character : out_str) {
                out.insert(character);  // convert to set to compare against deciphered number sets
            }
            int fin = 0;
            if (out == zero) {
                disp_str += "0";
            }
            else if (out == one) {
                disp_str += "1";
            }
            else if (out == two) {
                disp_str += "2";
            }
            else if (out == three) {
                disp_str += "3";
            }
            else if (out == four) {
                disp_str += "4";
            }
            else if (out == five) {
                disp_str += "5";
            }
            else if (out == six) {
                disp_str += "6";
            }
            else if (out == seven) {
                disp_str += "7";
            }
            else if (out == eight) {
                disp_str += "8";
            }
            else if (out == nine) {
                disp_str += "9";
            }
        }
        int disp_num = stoi(disp_str);
        displays.push_back(disp_num);
    }

    cout << "Total of each of the deciphered four number display outputs is: " << accumulate(begin(displays), end(displays), 0) << endl;

    return 0;
}
