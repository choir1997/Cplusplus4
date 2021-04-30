#include "Maze.h"
#include <iostream>
#include <sstream>

using namespace std;

//todo: set enum values and then convert to string later
enum rules {
    OPEN = 0, BLOCKED = 1, PATH = 2, TEMPORARY = 3, EXIT = 4, LEFT = 5, RIGHT = 6, UP = 7, DOWN = 8, OUT = 9, IN = 10
};

Maze::Maze(int layer, int height, int width) : HEIGHT(height), WIDTH(width), LAYERS(layer)  {
    mazeArray = new int**[LAYERS];
    for (int i = 0; i < LAYERS; i++) {
        mazeArray[i] = new int*[HEIGHT];
        for (int j = 0; j < HEIGHT; j++) {
            mazeArray[i][j] = new int[WIDTH];
        }
    }
    tempArray = new int**[LAYERS];
    for (int i = 0; i < LAYERS; i++) {
        tempArray[i] = new int*[HEIGHT];
        for (int j = 0; j < HEIGHT; j++) {
            tempArray[i][j] = new int[WIDTH];
        }
    }
    this->mazeLayer = 0;
    this->mazeHeight = 0;
    this->mazeWidth = 0;
}

void Maze::setValue(int layer, int height, int width, int value) {
    mazeLayer = layer;
    mazeHeight = height;
    mazeWidth = width;
    mazeArray[mazeLayer][mazeHeight][mazeWidth] = value;
    tempArray[mazeLayer][mazeHeight][mazeWidth] = value;
}

bool Maze::find_maze_path() {
    return rec_find_maze_path(0, 0, 0);
}

bool Maze::rec_find_maze_path(int layer, int height, int width) {
    //todo:check if value is out of bounds
    if ((height < 0) || (height >= HEIGHT) || (width < 0) || (width >= WIDTH)
        || (layer < 0) || (layer >= LAYERS)) {
        return false;
    }
    //todo: check if path is open
    else if (tempArray[layer][height][width] != OPEN) {
        return false;
    }
    //todo: check if path is the exit
    else if ((height == HEIGHT - 1) && (width == WIDTH - 1) && (layer == LAYERS - 1)) {
        tempArray[layer][height][width] = EXIT;
        return true;
    }
    //todo: check if it is valid path and assign with appropriate directions
    else {
        tempArray[layer][height][width] = PATH;

        if (rec_find_maze_path(layer, height, width - 1)) {
            tempArray[layer][height][width] = LEFT;
            return true;
        }
        else if (rec_find_maze_path(layer, height, width + 1)) {
            tempArray[layer][height][width] = RIGHT;
            return true;
        }
        else if (rec_find_maze_path(layer, height - 1, width)) {
            tempArray[layer][height][width] = UP;
            return true;
        }
        else if (rec_find_maze_path(layer, height + 1, width)) {
            tempArray[layer][height][width] = DOWN;
            return true;
        }
        else if (rec_find_maze_path(layer - 1, height, width)) {
            tempArray[layer][height][width] = OUT;
            return true;
        }
        else if (rec_find_maze_path(layer + 1, height, width)) {
            tempArray[layer][height][width] = IN;
            return true;
        }
        else {
            tempArray[layer][height][width] = TEMPORARY;
            return false;
        }
    }
}

//todo outputs the array with characters X and _, make sure to convert to Char instead of int
string Maze::toString() const {
    ostringstream outputString;
    outputString << "Solve Maze:" << endl;
    for (int i = 0; i < LAYERS; i++) {
        outputString << "Layer " << i + 1 << endl;
        for (int j = 0; j < HEIGHT; j++) {
            for (int k = 0; k < WIDTH; k++) {
                if (mazeArray[i][j][k] == OPEN) {
                    outputString << '_' << " ";
                }
                else if (mazeArray[i][j][k] == BLOCKED) {
                    outputString << 'X' << " ";
                }
            }
            outputString << endl;
        }
    }
    return outputString.str();
}

string Maze::toStringSolution() const {
    ostringstream outputString;
    outputString << endl;
    outputString << "Solution: " << endl;
    for (int i = 0; i < LAYERS; i++) {
        outputString << "Layer " << i + 1 << endl;
        for (int j = 0; j < HEIGHT; j++) {
            for (int k = 0; k < WIDTH; k++) {
                if (tempArray[i][j][k] == BLOCKED) {
                    outputString << 'X' << " ";
                }
                else if (tempArray[i][j][k] == TEMPORARY) {
                    outputString << '*' << " ";
                }
                else if (tempArray[i][j][k] == EXIT) {
                    outputString << 'E' << " ";
                }
                else if (tempArray[i][j][k] == OPEN) {
                    outputString << '_' << " ";
                }
                else if (tempArray[i][j][k] == LEFT) {
                    outputString << 'L' << " ";
                }
                else if (tempArray[i][j][k] == RIGHT) {
                    outputString << 'R' << " ";
                }
                else if (tempArray[i][j][k] == UP) {
                    outputString << 'U' << " ";
                }
                else if (tempArray[i][j][k] == DOWN) {
                    outputString << 'D' << " ";
                }
                else if (tempArray[i][j][k] == OUT) {
                    outputString << 'O' << " ";
                }
                else if (tempArray[i][j][k] == IN) {
                    outputString << 'I' << " ";
                }
                else {
                    outputString << tempArray[i][j][k] << " ";
                }
            }
            outputString << endl;
        }
    }
    return outputString.str();
}
