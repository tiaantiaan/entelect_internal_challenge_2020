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

std::vector<Shape> getShapes() {
    std::vector<Shape> shapes = {
            Shape(1, 0, 1, {Cell(0, 0), Cell(1, 0), Cell(1, 1)}),
            Shape(1, 0, 2, {Cell(1, 0), Cell(1, 1), Cell(0, 1)}),
            Shape(1, 0, 3, {Cell(0, 0), Cell(1, 1), Cell(0, 1)}),
            Shape(1, 0, 4, {Cell(0, 0), Cell(1, 0), Cell(0, 1)}),

            Shape(2, 0, 1, {Cell(0, 0), Cell(10, 1), Cell(10, 2), Cell(11, 0)}),
            Shape(2, 0, 2, {Cell(0, 0), Cell(11, 0), Cell(12, 0), Cell(12, 1)}),
            Shape(2, 0, 3, {Cell(2, 0), Cell(12, 1), Cell(12, 2), Cell(11, 2)}),
            Shape(2, 0, 4, {Cell(0, 2), Cell(11, 2), Cell(10, 1), Cell(12, 2)}),

            Shape(3, 0, 1, {Cell(0, 2), Cell(10, 1), Cell(11, 1), Cell(11, 0)}),
            Shape(3, 0, 2, {Cell(0, 0), Cell(11, 0), Cell(11, 1), Cell(12, 1)}),
            Shape(3, 0, 3, {Cell(0, 2), Cell(10, 1), Cell(11, 1), Cell(11, 0)}),
            Shape(3, 0, 4, {Cell(0, 0), Cell(11, 0), Cell(11, 1), Cell(12, 1)}),

            Shape(4, 0, 1, {Cell(0, 1), Cell(10, 0), Cell(11, 0), Cell(12, 0), Cell(13, 0), Cell(12, 1)}),
            Shape(4, 0, 2, {Cell(3, 0), Cell(13, 1), Cell(13, 2), Cell(13, 3), Cell(12, 0), Cell(12, 2)}),
            Shape(4, 0, 3, {Cell(0, 0), Cell(10, 1), Cell(10, 2), Cell(10, 3), Cell(11, 0), Cell(11, 2)}),
            Shape(4, 0, 4, {Cell(1, 2), Cell(13, 2), Cell(10, 3), Cell(11, 3), Cell(12, 3), Cell(13, 3)}),

            Shape(5, 0, 1, {Cell(0, 0), Cell(10, 1), Cell(10, 2), Cell(11, 0), Cell(12, 0), Cell(13, 0)}),
            Shape(5, 0, 2, {Cell(1, 0), Cell(12, 0), Cell(13, 0), Cell(13, 1), Cell(13, 2), Cell(13, 3)}),
            Shape(5, 0, 3, {Cell(3, 1), Cell(13, 2), Cell(13, 3), Cell(12, 3), Cell(11, 3), Cell(10, 3)}),
            Shape(5, 0, 4, {Cell(0, 0), Cell(10, 1), Cell(10, 2), Cell(10, 3), Cell(11, 3), Cell(12, 3)}),

            Shape(6, 0, 1, {Cell(0, 0), Cell(11, 0)}),
            Shape(6, 0, 2, {Cell(1, 0), Cell(11, 1)}),
            Shape(6, 0, 3, {Cell(1, 1), Cell(10, 1)}),
            Shape(6, 0, 4, {Cell(0, 1), Cell(10, 0)}),

            Shape(7, 0, 1, {Cell(0, 0), Cell(11, 0), Cell(12, 0), Cell(13, 0)}),
            Shape(7, 0, 2, {Cell(3, 0), Cell(13, 1), Cell(13, 2), Cell(13, 3)}),
            Shape(7, 0, 3, {Cell(2, 3), Cell(11, 3), Cell(13, 3), Cell(10, 3)}),
            Shape(7, 0, 4, {Cell(0, 3), Cell(10, 2), Cell(10, 1), Cell(10, 0)}),

            Shape(8, 0, 1, {Cell(3, 0), Cell(13, 1), Cell(13, 2), Cell(12, 2), Cell(12, 3)}),
            Shape(8, 0, 2, {Cell(3, 2), Cell(12, 2), Cell(11, 2), Cell(11, 3), Cell(10, 3)}),
            Shape(8, 0, 3, {Cell(0, 1), Cell(10, 2), Cell(10, 3), Cell(11, 0), Cell(11, 1)}),
            Shape(8, 0, 4, {Cell(0, 0), Cell(11, 0), Cell(12, 0), Cell(12, 1), Cell(13, 1)}),

            Shape(9, 0, 1, {Cell(0, 1), Cell(11, 2), Cell(11, 1), Cell(12, 1), Cell(11, 0)}),
            Shape(9, 0, 2, {Cell(2, 1), Cell(10, 1), Cell(11, 2), Cell(11, 1), Cell(11, 0)}),
            Shape(9, 0, 3, {Cell(1, 0), Cell(11, 1), Cell(11, 2), Cell(10, 1), Cell(12, 1)}),
            Shape(9, 0, 4, {Cell(1, 2), Cell(12, 1), Cell(11, 1), Cell(11, 0), Cell(10, 1)}),

            Shape(10, 0, 1, {Cell(0, 0), Cell(11, 0), Cell(11, 1), Cell(10, 2), Cell(11, 2)}),
            Shape(10, 0, 2, {Cell(0, 1), Cell(10, 0), Cell(11, 0), Cell(12, 0), Cell(12, 1)}),
            Shape(10, 0, 3, {Cell(0, 0), Cell(11, 0), Cell(10, 1), Cell(10, 2), Cell(11, 2)}),
            Shape(10, 0, 4, {Cell(0, 1), Cell(10, 2), Cell(11, 2), Cell(12, 2), Cell(12, 1)}),

            Shape(11, 0, 1, {Cell(0, 0), Cell(11, 0), Cell(12, 0)}),
            Shape(11, 0, 2, {Cell(2, 0), Cell(12, 1), Cell(12, 2)}),
            Shape(11, 0, 3, {Cell(2, 2), Cell(10, 2), Cell(11, 2)}),
            Shape(11, 0, 4, {Cell(0, 1), Cell(10, 2), Cell(10, 0)}),

            Shape(12, 0, 1, {Cell(2, 0), Cell(12, 1), Cell(11, 1), Cell(11, 2), Cell(10, 2)}),
            Shape(12, 0, 2, {Cell(2, 0), Cell(11, 0), Cell(11, 1), Cell(10, 1), Cell(10, 2)}),
            Shape(12, 0, 3, {Cell(0, 0), Cell(10, 1), Cell(11, 1), Cell(11, 2), Cell(12, 2)}),
            Shape(12, 0, 4, {Cell(2, 1), Cell(12, 2), Cell(11, 0), Cell(11, 1), Cell(10, 0)}),

            Shape(13, 0, 1, {Cell(0, 0), Cell(11, 0), Cell(11, 1), Cell(12, 1), Cell(11, 2)}),
            Shape(13, 0, 2, {Cell(2, 0), Cell(12, 1), Cell(11, 1), Cell(11, 2), Cell(10, 1)}),
            Shape(13, 0, 3, {Cell(1, 0), Cell(11, 1), Cell(11, 2), Cell(10, 1), Cell(12, 2)}),
            Shape(13, 0, 4, {Cell(0, 1), Cell(10, 2), Cell(11, 0), Cell(11, 1), Cell(12, 1)}),

            Shape(14, 0, 1, {Cell(0, 0), Cell(10, 1), Cell(10, 2), Cell(11, 1), Cell(11, 2)}),
            Shape(14, 0, 2, {Cell(0, 0), Cell(10, 1), Cell(11, 0), Cell(11, 1), Cell(12, 0)}),
            Shape(14, 0, 3, {Cell(2, 0), Cell(12, 1), Cell(12, 2), Cell(11, 1), Cell(11, 2)}),
            Shape(14, 0, 4, {Cell(2, 1), Cell(12, 2), Cell(11, 1), Cell(11, 2), Cell(10, 2)}),

            Shape(15, 0, 1, {Cell(0, 0), Cell(10, 1), Cell(11, 0), Cell(11, 2), Cell(12, 0), Cell(12, 1)}),
            Shape(15, 0, 2, {Cell(2, 0), Cell(12, 1), Cell(12, 2), Cell(11, 0), Cell(11, 2), Cell(10, 1)}),
            Shape(15, 0, 3, {Cell(2, 1), Cell(12, 2), Cell(10, 1), Cell(10, 2), Cell(11, 0), Cell(11, 2)}),
            Shape(15, 0, 4, {Cell(0, 0), Cell(10, 1), Cell(10, 2), Cell(11, 0), Cell(11, 2), Cell(12, 1)}),

            Shape(16, 0, 1, {Cell(0, 1), Cell(11, 0), Cell(11, 1), Cell(11, 2), Cell(12, 0), Cell(12, 1)}),
            Shape(16, 0, 2, {Cell(0, 1), Cell(11, 0), Cell(11, 1), Cell(11, 2), Cell(12, 1), Cell(12, 2)}),
            Shape(16, 0, 3, {Cell(0, 1), Cell(10, 2), Cell(11, 0), Cell(11, 1), Cell(11, 2), Cell(12, 1)}),
            Shape(16, 0, 4, {Cell(0, 0), Cell(10, 1), Cell(11, 0), Cell(11, 1), Cell(11, 2), Cell(12, 1)}),

            Shape(17, 0, 1, {Cell(0, 0), Cell(10, 1), Cell(11, 0), Cell(11, 1)}),
            Shape(17, 0, 2, {Cell(1, 0), Cell(10, 0), Cell(11, 1), Cell(10, 1)}),
            Shape(17, 0, 3, {Cell(1, 1), Cell(10, 1), Cell(11, 0), Cell(10, 0)}),
            Shape(17, 0, 4, {Cell(1, 0), Cell(10, 1), Cell(10, 0), Cell(11, 1)}),

            Shape(18, 0, 1, {Cell(0, 0), Cell(10, 1), Cell(10, 2), Cell(11, 1), Cell(12, 1)}),
            Shape(18, 0, 2, {Cell(0, 0), Cell(11, 0), Cell(11, 1), Cell(11, 2), Cell(12, 0)}),
            Shape(18, 0, 3, {Cell(2, 0), Cell(12, 1), Cell(12, 2), Cell(11, 1), Cell(10, 1)}),
            Shape(18, 0, 4, {Cell(2, 2), Cell(11, 0), Cell(11, 1), Cell(11, 2), Cell(10, 2)}),

            Shape(19, 0, 1, {Cell(0, 2), Cell(11, 1), Cell(11, 2), Cell(12, 0), Cell(12, 1), Cell(12, 2)}),
            Shape(19, 0, 2, {Cell(0, 0), Cell(10, 1), Cell(10, 2), Cell(11, 1), Cell(11, 2), Cell(12, 2)}),
            Shape(19, 0, 3, {Cell(0, 0), Cell(10, 1), Cell(10, 2), Cell(11, 0), Cell(11, 1), Cell(12, 0)}),
            Shape(19, 0, 4, {Cell(2, 0), Cell(12, 1), Cell(12, 2), Cell(11, 0), Cell(11, 1), Cell(10, 0)}),

            Shape(20, 0, 1, {Cell(0, 1), Cell(11, 0), Cell(12, 0), Cell(12, 1), Cell(12, 2), Cell(13, 0), Cell(13, 2)}),
            Shape(20, 0, 2, {Cell(2, 0), Cell(13, 1), Cell(13, 2), Cell(13, 3), Cell(11, 2), Cell(11, 3), Cell(12, 2)}),
            Shape(20, 0, 3, {Cell(3, 2), Cell(12, 3), Cell(11, 1), Cell(11, 2), Cell(11, 3), Cell(10, 3), Cell(10, 1)}),
            Shape(20, 0, 4, {Cell(1, 3), Cell(10, 0), Cell(10, 1), Cell(10, 2), Cell(12, 0), Cell(12, 1), Cell(11, 1)}),

            Shape(21, 0, 1, {Cell(0, 1), Cell(11, 2), Cell(12, 1), Cell(11, 0)}),
            Shape(21, 0, 2, {Cell(2, 1), Cell(10, 1), Cell(11, 2), Cell(11, 0)}),
            Shape(21, 0, 3, {Cell(1, 0), Cell(11, 2), Cell(10, 1), Cell(12, 1)}),
            Shape(21, 0, 4, {Cell(1, 2), Cell(12, 1), Cell(11, 0), Cell(10, 1)}),

            Shape(22, 0, 1, {Cell(1, 0), Cell(11, 1), Cell(10, 1), Cell(10, 2), Cell(10, 3), Cell(11, 3)}),
            Shape(22, 0, 2, {Cell(0, 0), Cell(10, 1), Cell(11, 0), Cell(12, 0), Cell(12, 1), Cell(13, 1)}),
            Shape(22, 0, 3, {Cell(2, 0), Cell(13, 0), Cell(13, 1), Cell(13, 2), Cell(12, 2), Cell(12, 3)}),
            Shape(22, 0, 4, {Cell(0, 2), Cell(10, 3), Cell(11, 2), Cell(12, 2), Cell(12, 3), Cell(13, 3)}),

            Shape(23, 0, 1, {Cell(0, 0), Cell(11, 0), Cell(11, 1), Cell(11, 2), Cell(11, 3), Cell(10, 3)}),
            Shape(23, 0, 2, {Cell(0, 0), Cell(10, 1), Cell(11, 0), Cell(12, 0), Cell(13, 0), Cell(13, 1)}),
            Shape(23, 0, 3, {Cell(0, 2), Cell(10, 3), Cell(11, 3), Cell(12, 3), Cell(13, 2), Cell(13, 3)}),
            Shape(23, 0, 4, {Cell(2, 0), Cell(12, 1), Cell(12, 2), Cell(12, 3), Cell(13, 0), Cell(13, 3)}),

            Shape(24, 0, 1, {Cell(0, 0)}),
            Shape(24, 0, 2, {Cell(0, 0)}),
            Shape(24, 0, 3, {Cell(0, 0)}),
            Shape(24, 0, 4, {Cell(0, 0)}),

            Shape(25, 0, 1, {Cell(0, 0), Cell(11, 0), Cell(12, 1), Cell(11, 2), Cell(12, 3), Cell(11, 4), Cell(10, 4)}),
            Shape(25, 0, 2, {Cell(4, 0), Cell(13, 0), Cell(12, 1), Cell(13, 2), Cell(12, 3), Cell(13, 4), Cell(14, 4)}),
            Shape(25, 0, 3, {Cell(0, 1), Cell(10, 2), Cell(11, 0), Cell(12, 1), Cell(13, 0), Cell(14, 1), Cell(14, 2)}),
            Shape(25, 0, 4, {Cell(0, 2), Cell(10, 3), Cell(11, 4), Cell(12, 3), Cell(13, 4), Cell(14, 2), Cell(14, 3)})
    };

    return shapes;
}

Shape getShapeWithRotation(int id, int rotation) {
    getShapes();
}

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
    getShapes();


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
        // todo shape cells and rot needs to come from somewhere?
        input.shapes.push_back(Shape(std::stoi(id), std::stoi(num), 0));
    }

    const std::vector<std::string> blockedCells = split(lines[lines.size() - 1], '|');

    for (int i = 0; i < blockedCells.size(); ++i) {
        const std::vector<std::string> cell = split(blockedCells[i], ',');
        input.blockedCells.push_back(Cell(std::stoi(cell[0]), std::stoi(cell[1])));
    }
    return input;
}

