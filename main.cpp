#include <iostream>
#include <fstream>
#include <sstream>
#include "Maze.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 3)
    {
        cerr << "Please provide name of input and output files";
        return 1;
    }
    cout << "Input file: " << argv[1] << endl;
    ifstream in(argv[1]);
    if (!in)
    {
        cerr << "Unable to open " << argv[1] << " for input";
        return 1;
    }
    cout << "Output file: " << argv[2] << endl;
    ofstream out(argv[2]);
    if (!out)
    {
        in.close();
        cerr << "Unable to open " << argv[2] << " for output";
    }
    string measurementsLine;
    getline(in, measurementsLine);

    int mazeHeight = 0;
    int mazeWidth = 0;
    int numLayers = 0;

    istringstream iss(measurementsLine);

    iss >> mazeHeight >> mazeWidth >> numLayers;

    Maze newMaze = Maze(numLayers, mazeHeight, mazeWidth);

    string inputLine;

    //todo: read input and store it in the newMaze object (setValue)
    while (!in.eof()) {
        try {
            for (int i = 0; i < numLayers; i++) {
                for (int j = 0; j < mazeHeight; j++) {
                    for (int k = 0; k < mazeWidth; k++) {
                        in >> inputLine;
                        int x;
                        istringstream inFS(inputLine);
                        inFS >> x;
                        newMaze.setValue(i, j, k, x);
                    }
                }
            }
            out << newMaze.toString();
            if (newMaze.find_maze_path()) { //TODO: check to see if solution exists
                out << newMaze.toStringSolution();
            }
            else {
                throw -1;
            }
        }
        catch (int x) {
            if (x == -1) {
                out << "No Solution Exists!";
            }
        }
    }
    return 0;
}
