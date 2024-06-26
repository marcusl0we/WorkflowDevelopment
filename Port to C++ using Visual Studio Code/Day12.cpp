#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <numeric>
#include <regex>
#include <algorithm>
#include <deque>
#include <unordered_map>
#include <set>

using namespace std;

int count_paths(vector<string>& path, bool& print_output)
{
    if (print_output)
    {
        for (int i = 0; i < path.size(); i++)
        {
            cout << path[i] << " ";
        }
        cout << "\n";
    }
    return 1;
}

bool cave_not_been_visited(string& x, vector<string>& path, string Part_1_or_2)
{
    if (Part_1_or_2 == "Part 1")
    {
        if (std::all_of(x.begin(), x.end(), [](unsigned char c) { return std::isupper(c); }))
        {
            return true;
        }
        if (std::all_of(x.begin(), x.end(), [](unsigned char c) { return std::islower(c); }))
        {
            for (int i = 0; i < path.size(); i++)
            {
                if (path[i] == x)
                {
                    return false;
                }
            }
            return true;
        }
        // Fix compiler warning for case if neither fully uppercase or fully lowercase input
        cout << "Warning: input is neither fully uppercase nor lowercase!" << endl;
        return false;
    }

    if (Part_1_or_2 == "Part 2")
    {
        if (std::all_of(x.begin(), x.end(), [](unsigned char c) { return std::isupper(c); }))
        {
            return true;
        }
        if (std::all_of(x.begin(), x.end(), [](unsigned char c) { return std::islower(c); }))
        {
            if (x == "start" || x == "end")
            {
                for (int i = 0; i < path.size(); i++)
                {
                    if (path[i] == x)
                    {
                        return false;
                    }
                }
                return true;
            }

            set<string> nodes_so_far_temp = set<string>{ path.begin(),path.end() };
            vector<string> nodes_so_far = vector<string>{ nodes_so_far_temp.begin(), nodes_so_far_temp.end() };

            unordered_map<string, int> node_on_path_occurrences;
            for (string element : nodes_so_far)
            {
                node_on_path_occurrences[element] = 0;
            }

            if ((find(nodes_so_far.begin(), nodes_so_far.end(), x) == nodes_so_far.end()))
            {
                node_on_path_occurrences[x] = 0;
            }

            for (int i = 0; i < path.size(); i++)
            {
                node_on_path_occurrences[path[i]] += 1;
            }

            bool small_cave_twice_once = false;
            for (auto& pair : node_on_path_occurrences)
            {
                string key = pair.first;
                int value = pair.second;
                if (std::all_of(key.begin(), key.end(), [](unsigned char c) { return std::islower(c); }) &&
                    value >= 2 &&
                    key != "start" &&
                    key != "end")
                {
                    small_cave_twice_once = true;
                }
            }

            if (node_on_path_occurrences[x] == 0)
            {
                return true;
            }
            if (node_on_path_occurrences[x] >= 1)
            {
                if (small_cave_twice_once)
                {
                    return false;
                }
                else
                {
                    return true;
                }
            }
        }
        // Fix compiler warning for case if neither fully uppercase or fully lowercase input
        cout << "Warning: input is neither fully uppercase nor lowercase!" << endl;
        return false;
    }
    // Fix compiler warning for case if neither Part_1 or Part_2 flag
    cout << "Warning: Part 1 or Part 2 flag not specified!" << endl;
    return false;
}

int find_paths(const unordered_map<string, vector<string>>& graph, const string source, const string destination, const string Part_1_or_2)
{
    int number_of_paths = 0;
    deque<vector<string>> q;
    vector<string> path;

    path.clear();
    path.push_back(source);
    q.push_back(path);

    while (!q.empty())
    {
        path = q.front();
        q.pop_front();
        string last = path[path.size() - 1];

        if (last == destination)
        {
            bool print_output = false;
            number_of_paths += count_paths(path, print_output);
        }

        int loopend = graph.at(last).size();
        for (int i = 0; i < loopend; i++)
        {
            vector<string> nodes_connected_to_last = graph.at(last);

            if (cave_not_been_visited(nodes_connected_to_last[i], path, Part_1_or_2))
            {
                vector<string> new_path = path;
                new_path.push_back(nodes_connected_to_last[i]);
                q.push_back(new_path);
            }
        }
    }

    return number_of_paths;
}

int main()
{
    ifstream myfile("..\\Personal txt Inputs\\Day12.txt");          //create an input stream object from file
    string file_line;                                               //create line object to read into
    vector<vector<string>> data;                                    //create vector of ints/strings
    string delimiter = "-";
    while (getline(myfile, file_line)) {                            //read each line and cast to file_line variable
        vector<string> splitstring;
        splitstring.push_back(file_line.substr(0, file_line.find(delimiter)));      // push back substring from 0 (start) to the location of delimiter
        splitstring.push_back(file_line.substr(file_line.find(delimiter) + 1, -1)); // push back substring from delimiter + 1 up to end of string -1
        data.push_back(splitstring);                                //append variable to vector
    }
    myfile.close();

    unordered_map<string, vector<string>> G;

    for (vector<string> line : data)
    {
        string nodeA = line[0];
        string nodeB = line[1];
        vector<string> lst = G[nodeA];
        if (!(find(lst.begin(), lst.end(), nodeB) != lst.end()))
        {
            lst.push_back(nodeB);
            G[nodeA] = lst;
        }
        lst = G[nodeB];
        if (!(find(lst.begin(), lst.end(), nodeA) != lst.end()))
        {
            lst.push_back(nodeA);
            G[nodeB] = lst;
        }
    }

    int num_paths = find_paths(G, "start", "end", "Part 1");
    cout << "The number of paths from start to end for Part 1 was " << num_paths << endl;

    // As its own indiviual self contained single C++ file, time taken for Part 2 is similar to
    // the Python version, it is only within the VS Commuinity/Pro project it is slowed down to 
    // several minutes?
    int num_paths_2 = find_paths(G, "start", "end", "Part 2");
    cout << "The number of paths from start to end for Part 2 was " << num_paths_2 << endl;

    return 0;
}