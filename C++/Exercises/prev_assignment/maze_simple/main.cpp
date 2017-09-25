#include <iostream>
#include "mazeio.h"
#include "queue.h"

int main(){
	int rows, cols, res;				// initialize variables
	char** maze;
	std::cin >> rows >> cols;			// take rows/cols as std input
	maze = readMaze(&rows, &cols);		// allocate a maze

	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			std::cin >> maze[i][j];
		}
	}
	if(maze == NULL){
		std::cout << "ERROR: invalid format\n";
		return 1;
	}
	// begin search for shortest path
	res = mazeSearch(maze, rows, cols);

	// examine results from maze search
	if(res == 1){
		std::cout << rows << " " << cols << "\n";
		printMaze(maze, rows, cols);
	}
	else if(res == 0)
		std::cout << "No path could be found.\n";
	else
		std::cout << "Invalid maze.\n";

	for(int i=0; i<rows; i++)
		delete[] maze[i];				// deletes columns from each row
	delete[] maze;						// deletes the rows
	return 0;
}