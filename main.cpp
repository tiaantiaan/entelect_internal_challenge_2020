#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//#include "ortools/linear_solver/linear_solver.h"

class Cell {
public:
    int col;
    int row;
    Cell(int r, int c) {
        row = r;
        col = c;
    }
};

class Shape {
public:
    int id;
    int numAvailable;
    int rotation;
    std::vector<Cell> cells;
    Shape(int id2, int num, int rot) {
        id = id2;
        numAvailable = num;
        rotation = rot;
    }

    Shape(int id2, int num, int rot, std::vector<Cell> cells2) {
        id = id2;
        numAvailable = num;
        rotation = rot;
        cells = cells2;
    }
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
public:
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
