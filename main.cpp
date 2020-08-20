#include <iostream>
#include <fstream>
#include <string>
//#include "ortools/linear_solver/linear_solver.h"

class Cell {
    int x;
    int y;
};

class Cells {
    Cell cells[];
};

class Shape {
public:
    int id;
    int numAvailable;
    Cells cells;
};
class Input {
public:
    int dimX;
    int dimY;
    int numShapes;
    int numBLockedCells;
    Cells blockedCells;
    Shape shapes[];
};

class Output {
    Shape shapes[];
};



int main() {
//    operations_research::SimpleLpProgram();

    std::cout << "Hello, World!" << std::endl;
    std::ifstream file("input.txt");
    std::string str;
    while (std::getline(file, str)) {
        std::cout << str << "\n";
    }
    return 0;
}
