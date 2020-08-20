#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
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

Input getInput(const std::string &filename);

std::vector<std::string> split(const std::string& s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {

    Input input = getInput("documents/map_1.input");

    std::cout << input.numBLockedCells;

    return 0;
}

Input getInput(const std::string &filename) {
    std::ifstream file(filename);
    std::string str;
    std::vector<std::string> lines;
    while (std::getline(file, str)) {
        lines.push_back(str);
    }

    Input input;

    std::string row = lines[0].substr(0, lines[0].find(','));
    std::string col  = lines[0].substr(lines[0].find(',') + 1, lines[0].length());

    input.dimRow = std::stoi(row);
    input.dimCol = std::stoi(col);

    input.numShapes = std::stoi(lines[1]);
    input.numBLockedCells = std::stoi(lines[2]);

    for (int i = 3; i < lines.size() - 1; i++) {
        std::string id = lines[i].substr(0, lines[i].find(','));
        std::string num  = lines[i].substr(lines[i].find(',') + 1, lines[i].length());
        input.shapes.push_back(Shape(std::stoi(id), std::stoi(num)));
    }

    const std::vector<std::string> blockedCells = split(lines[lines.size() - 1], '|');

    for (int i = 0; i < blockedCells.size(); ++i) {
        const std::vector<std::string> cell = split(blockedCells[i], ',');
        input.blockedCells.push_back(Cell(std::stoi(cell[0]), std::stoi(cell[1])));
    }
    return input;
}

