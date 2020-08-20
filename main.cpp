#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <sstream>
//#include "ortools/linear_solver/linear_solver.h"

class Cell {
public:
    Cell() = default;

    Cell(int r, int c) {
        row = r;
        col = c;
    }

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
    int rotation;
    std::vector<Cell> cells;

    Shape() = default;

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

class PlacedShape {
public:
    int id;
    int row;
    int col;
    int rotation;

    PlacedShape(int id2, int r, int c, int rot) {
        id = id2;
        row = r;
        col = c;
        rotation = rot;
    };
};


class Board {
public:
    explicit Board(const Input &input) {
        for (int k = 0; k < input.dimRow; ++k) {
            std::vector<Cell> bob(input.dimRow);
            for (int i = 0; i < input.dimCol; ++i) {
                //Set everything to -1 White
                bob[i] = Cell(k, i, -1);
            }
            boardCells.push_back(bob);
        }

        for (auto &blockedCells : input.blockedCells) {
            boardCells[blockedCells.col][blockedCells.row].value = -2;
        }

        for (auto &shape : input.shapes) {
            for (auto &cell : shape.cells) {
                //Trying to place ontop of previous placement OR trying to place on blocked section
                if (boardCells[cell.col][cell.row].value != -1)
                    baseScore = -1;
                boardCells[cell.col][cell.row].value = cell.value;
            }
        }

    }

    std::vector<std::vector<Cell>> boardCells;
    //Score of the board after initial build
    int baseScore = 0;
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

            Shape(2, 0, 1, {Cell(0, 0), Cell(0, 1), Cell(0, 2), Cell(1, 0)}),
            Shape(2, 0, 2, {Cell(0, 0), Cell(1, 0), Cell(2, 0), Cell(2, 1)}),
            Shape(2, 0, 3, {Cell(2, 0), Cell(2, 1), Cell(2, 2), Cell(1, 2)}),
            Shape(2, 0, 4, {Cell(0, 2), Cell(1, 2), Cell(0, 1), Cell(2, 2)}),

            Shape(3, 0, 1, {Cell(0, 2), Cell(0, 1), Cell(11, 1), Cell(1, 0)}),
            Shape(3, 0, 2, {Cell(0, 0), Cell(1, 0), Cell(11, 1), Cell(2, 1)}),
            Shape(3, 0, 3, {Cell(0, 2), Cell(0, 1), Cell(11, 1), Cell(1, 0)}),
            Shape(3, 0, 4, {Cell(0, 0), Cell(1, 0), Cell(11, 1), Cell(2, 1)}),

            Shape(4, 0, 1, {Cell(0, 1), Cell(0, 0), Cell(1, 0), Cell(2, 0), Cell(3, 0), Cell(2, 1)}),
            Shape(4, 0, 2, {Cell(3, 0), Cell(3, 1), Cell(3, 2), Cell(3, 3), Cell(2, 0), Cell(2, 2)}),
            Shape(4, 0, 3, {Cell(0, 0), Cell(0, 1), Cell(0, 2), Cell(0, 3), Cell(1, 0), Cell(1, 2)}),
            Shape(4, 0, 4, {Cell(1, 2), Cell(3, 2), Cell(0, 3), Cell(1, 3), Cell(2, 3), Cell(3, 3)}),

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
    std::vector<Shape> allShapes = getShapes();

    Shape result;
    bool found = false;

    for (int i = 0; i < allShapes.size(); ++i) {
        if (allShapes[i].id == id && allShapes[i].rotation == rotation) {
            result = allShapes[i];
            found = true;
            break;
        }
    }
    if (!found) {
        throw "SHAPE NOT FOUND!!!!";
    }
    return result;
}

Input getInput(const std::string &filename);

std::vector<std::string> split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}
std::string generateOutputString(const Input &input) {
    std::string output = "";

    for (int i = 0; i < input.shapes.size(); ++i) {
        Shape shape = input.shapes[i];
        output += std::to_string(shape.id) + "|";
        for (int j = 0; j < shape.cells.size(); ++j) {
            output += std::to_string(shape.cells[j].row) + "," + std::to_string(shape.cells[j].col);
            if (j < shape.cells.size() -1) {
                output += "|";
            }
        }
        output += "\n";
    }

    return output;
}


Input populateInput(Input input) {

    std::vector<PlacedShape> placedShapes = {PlacedShape(1, 10, 20, 1), PlacedShape(2, 30, 40, 1)};

    std::vector<Shape> shapes;

    for (int i = 0; i < placedShapes.size(); ++i) {
        Shape shape = Shape(placedShapes[i].id, 0, placedShapes[i].rotation);
        Shape unitShape = getShapeWithRotation(placedShapes[i].id, placedShapes[i].rotation);
        std::vector<Cell> cells;
        for (int j = 0; j < unitShape.cells.size(); ++j) {
            Cell cell = Cell(unitShape.cells[j].row + placedShapes[i].row,
                             unitShape.cells[j].col + placedShapes[i].col);
            cells.push_back(cell);
        }
        shape.cells = cells;

        shapes.push_back(shape);
    }

    // populate input.shapes
    input.shapes = shapes;

    return input;
}

int main() {

    // Get input
    Input input = getInput("documents/map_1.input");
    Input populatedInput = getInput("documents/map_1.input");

    // Populate Input.shapes
    Input validPopulatedInput = populateInput(populatedInput);

    // Calculate score


    //    OUtput

    //todo delete test junk
    Input test;

    std::vector<Cell> cells1;
    cells1.push_back(Cell(0,2));
    cells1.push_back(Cell(0,3));
    cells1.push_back(Cell(1,3));

    std::vector<Cell> cells2;
    cells2.push_back(Cell(2,5));
    cells2.push_back(Cell(3,5));
    cells2.push_back(Cell(3,6));
    cells2.push_back(Cell(4,6));

    test.shapes.push_back(Shape(1, 1, 0, cells1));
    test.shapes.push_back(Shape(3, 1, 0, cells2));

    std::cout << generateOutputString(test);


    //todo delete test junk
    std::cout << "---------------------------\n";
    for (int i = 0; i < validPopulatedInput.shapes.size(); ++i) {
        std::cout << "ID: ";
        std::cout << validPopulatedInput.shapes[i].id;
        for (int j = 0; j < validPopulatedInput.shapes[i].cells.size(); ++j) {
            std::cout << "(";

            std::cout << validPopulatedInput.shapes[i].cells[j].row;

            std::cout << ",";
            std::cout << validPopulatedInput.shapes[i].cells[j].col;
            std::cout << ")";
            std::cout << "\n";

        }
    }
    std::cout << "---------------------------\n";


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
    std::string col = lines[0].substr(lines[0].find(',') + 1, lines[0].length());

    input.dimRow = std::stoi(row);
    input.dimCol = std::stoi(col);

    input.numShapes = std::stoi(lines[1]);
    input.numBLockedCells = std::stoi(lines[2]);

    for (int i = 3; i < lines.size() - 1; i++) {
        std::string id = lines[i].substr(0, lines[i].find(','));
        std::string num = lines[i].substr(lines[i].find(',') + 1, lines[i].length());
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

//count number of filled cells
int numberOfFilledCells(const std::vector<Shape> &shapes) {
    int numberOfFilledCells = 0;
    for (auto &shape : shapes) {
        numberOfFilledCells += shape.cells.size();
    }

    return numberOfFilledCells;
}

//todo check valid groups??????
bool isNewWhiteCell(int i, int j, Board board, std::vector<Cell> foundCells) {
    if (foundCells.empty())
        return true;

    return false;
}

bool isWhiteCell(int i, int j, const Input &input, Board board) {
    if (i > 0 && j > 0 && i < input.dimRow && j < input.dimCol) {
        return false;
    }
    return board.boardCells[i][j].value == -1;
}

//count number of individual empty groups
int numberOfEmptyGroupings(const Input &input) {
    Board board = Board(input);

    std::vector<Cell> foundCells;

    for (int i = 0; i < input.dimCol; ++i) {
        for (int j = 0; j < input.dimRow; ++j) {
            if (board.boardCells[i][j].value == -1) {
                if (isWhiteCell(i, j, input, board) && isNewWhiteCell(i, j, board, foundCells)) {
                    foundCells.push_back(board.boardCells[i][j]);
                }
            }
        }
    }

    return foundCells.size();

}


int numberOfSoloWhiteBlocks(const Input &input) {
    Board board = Board(input);

    int numberOfSoloWhiteBlocks = 0;
    for (int i = 0; i < input.dimCol; ++i) {
        for (int j = 0; j < input.dimRow; ++j) {
            //if is a white block
            if (board.boardCells[i][j].value == -1) {
                if (!isWhiteCell(i - 1, j - 1, input, board)
                    && !isWhiteCell(i - 1, j, input, board)
                    && !isWhiteCell(i - 1, j + 1, input, board)
                    && !isWhiteCell(i, j - 1, input, board)
                    && !isWhiteCell(i, j, input, board)
                    && !isWhiteCell(i, j + 1, input, board)
                    && !isWhiteCell(i + 1, j - 1, input, board)
                    && !isWhiteCell(i + 1, j, input, board)
                    && !isWhiteCell(i + 1, j + 1, input, board))
                    numberOfSoloWhiteBlocks++;
            }
        }
    }

    return numberOfSoloWhiteBlocks;


}

int calculateScore(const Input &input) {
    int totalCapacity = input.dimCol * input.dimRow;

    Board board = Board(input);

    //Invalid board
    if (board.baseScore < 0)
        return -100;

    int score = numberOfFilledCells(input.shapes) * 10;
    score -= numberOfEmptyGroupings(input) * 2;
    score -= numberOfSoloWhiteBlocks(input) * 4;

    return floor(totalCapacity / numberOfFilledCells(input.shapes) * score);
}

