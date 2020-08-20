#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//#include "ortools/linear_solver/linear_solver.h"

class Cell {
    int row;
    int col;
};

class Shape {
public:
    int id;
    int numAvailable;
    std::vector<Cell> cells;
};

class Input {
public:
    int dimRow;
    int dimCol;
    int numShapes;
    int numBLockedCells;
    std::vector<Cell> blockedCells;
    std::vector<Shape> shapes;
};

class Output {
    std::vector<Shape> shapes;
};



int main() {

    std::cout << "Hello, World!" << std::endl;
    std::ifstream file("documents/map_1.input");
    std::string str;
    while (std::getline(file, str)) {
        std::cout << str << "\n";
    }
    return 0;
}
