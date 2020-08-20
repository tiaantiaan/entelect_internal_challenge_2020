#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::ifstream file("input.txt");
    std::string str;
    while (std::getline(file, str)) {
        std::cout << str << "\n";
    }
    return 0;
}
