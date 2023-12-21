// Your First C++ Program

#include <iostream>
#include <vector>
#include <string>


int main() {
    std::cout << "\nHello World!\n\n";

    std::vector<std::string> msg{"This", "is", "made", "in", "a", "loop\n"};

    for (const std::string &word : msg)
    {
        std::cout << word << " ";
    }
    std::cout << std::endl;

    return 0;
}