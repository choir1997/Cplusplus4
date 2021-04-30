#ifndef CS235_LAB_7_MAZE_H
#define CS235_LAB_7_MAZE_H
#include "MazeInterface.h"

using namespace std;

class Maze : public MazeInterface {
private:
    int mazeHeight;
    int mazeWidth;
    int mazeLayer;
    int ***mazeArray; //original array of 0 and 1s
    int ***tempArray; //array for the solution maze, which includes directions
    const int HEIGHT;
    const int WIDTH;
    const int LAYERS;

public:
    Maze(int l, int h, int w);

    ~Maze(void) {
        for (int i = 0; i < LAYERS; i++) {
            for (int j = 0; j < HEIGHT; j++) {
                delete[] mazeArray[i][j];
                delete[] tempArray[i][j];
            }
            delete[] mazeArray[i];
            delete[]tempArray[i];
        }
        delete[] mazeArray;
        delete[] tempArray;
    }

    void setValue(int height, int width, int layer, int value);

    bool find_maze_path();

    bool rec_find_maze_path(int layer, int height, int width);

    string toString() const;

    string toStringSolution() const; //final string solution with directions

    friend ostream& operator<< (ostream& os, Maze& outputString)
    {
        os << outputString.toString();
        return os;
    }
};


#endif //CS235_LAB_7_MAZE_H
