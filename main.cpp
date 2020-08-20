#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
//#include "ortools/linear_solver/linear_solver.h"

class Cell {
public:
    Cell() = default;

    Cell(int c, int r, int val) {
        col = c;
        row = r;
        value = val;
    }

    int col;
    int row;
    int value;
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


class Board {
public:
    explicit Board(const Input &input) {
        for (int k = 0; k < input.dimRow; ++k) {
            std::vector<Cell> bob;
            for (int i = 0; i < input.dimCol; ++i) {
                bob.emplace_back(i, k, -1);
            }
            boardCells.push_back(bob);
        }

        for (auto &shape : input.shapes) {
            for (auto &cell : shape.cells) {
                boardCells[cell.col][cell.row].value = cell.value;
            }
        }

    }

    std::vector<std::vector<Cell>> boardCells;
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
int numberOfFilledCells(const std::vector<Shape> &shapes) {
    int numberOfFilledCells = 0;
    for (auto &shape : shapes) {
        numberOfFilledCells += shape.cells.size();
    }

    return numberOfFilledCells;
}


bool isNewWhiteCell(int i, int j, Board board, std::vector<Cell> foundCells) {
    if (foundCells.empty())
        return true;
    return false;
}

//count number of individual empty groups
int numberOfEmptyGroupings(const Input &input) {
    Board board = Board(input);

    std::vector<Cell> foundCells;

    for (int i = 0; i < input.dimCol; ++i) {
        for (int j = 0; j < input.dimRow; ++j) {
            if (board.boardCells[i][j].value == -1) {
                if (isNewWhiteCell(i, j, board, foundCells)) {
                    foundCells.push_back(board.boardCells[i][j]);
                }
            }
        }
    }

    return foundCells.size();

}

int numberOfSoloWhiteBlocks(const std::vector<Shape> &shapes) {

}

int calculateScore(const Input &input) {
    int totalCapacity = input.dimCol * input.dimRow;
    int score = numberOfFilledCells(input.shapes) * 10;
    score -= numberOfEmptyGroupings(input) * 2;
    score -= numberOfSoloWhiteBlocks(input.shapes) * 4;

    return floor(totalCapacity / numberOfFilledCells(input.shapes) * score);
}

