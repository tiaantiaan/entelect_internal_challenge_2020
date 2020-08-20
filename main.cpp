#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
//#include "ortools/linear_solver/linear_solver.h"

class Cell {
public:
    int col;
    int row;
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
public:
    std::vector<Shape> shapes;
};


int main() {
//    operations_research::SimpleLpProgram();

    Shape shape;
    Cell cell;
    shape.id = 1;
    cell.row = 0;

    std::cout << "Hello, World!" << std::endl;
    std::ifstream file("documents/map_1.input");
    std::string str;
    while (std::getline(file, str)) {
        std::cout << str << "\n";
    }
    return 0;
}


//count number of filled cells
int numberOfFilledCells(const std::vector<Shape>& shapes) {
    int numberOfFilledCells = 0;
    for (auto & shape : shapes) {
        numberOfFilledCells += shape.cells.size();
    }

    return numberOfFilledCells;
}

//count number of individual empty groups
int numberOfEmptyGroupings(const std::vector<Shape>& shapes) {
    int numberOfFilledCells = 0;
    for (auto & shape : shapes) {
        numberOfFilledCells += shape.cells.size();
    }
}

int numberOfSoloWhiteBlocks(const std::vector<Shape>& shapes) {

}

int calculateScore(Input input) {
    int totalCapacity = input.dimCol * input.dimRow;
    int score = numberOfFilledCells(input.shapes) * 10;
    score -= numberOfEmptyGroupings(input.shapes) * 2;
    score -= numberOfSoloWhiteBlocks(input.shapes) * 4;

    return floor(totalCapacity / numberOfFilledCells(input.shapes) * score);
}

