#ifndef MAZEIO_H
#define MAZEIO_H

// reads maze and returns a 2D array
// parameters: int pointers to row and column
// return: char** representing 2D maze
char** readMaze(int* row, int* col);

// prints maze as standard output
// parameter: char** maze, int rows and columns
// return: nothing
void printMaze(char** maze, int row, int col);

// searches for the shortest path
// parameters: char** maze, int row & col
// return: 1 - success, 0 - no path exists, -1 - invalid maze
int mazeSearch(char** maze, int row, int col);

#endif