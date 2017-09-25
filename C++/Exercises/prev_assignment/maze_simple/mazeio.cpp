#include <iostream>
#include "mazeio.h"
#include "queue.h"

// reads maze and returns a 2D array
// parameters: int pointers to row and column
// return: char** representing 2D maze
char** readMaze(int* row, int* col){
	char** maze;						// initialize double pointer
	maze = new char*[*row];				// create new 1D array row-size
	for(int i=0; i<*row; i++){
		maze[i] = new char[*col];		// each row will create new column
	}
	return maze;
}

// prints maze as standard output
// parameter: char** maze, int rows and columns
// return: nothing
void printMaze(char** maze, int row, int col){
	for(int i=0; i<row; i++){			// iterate thru each row of maze
		for(int j=0; j<col; j++){		// iterate thru each col of row
			std::cout << maze[i][j];	// O(n^2)
		}
		std::cout << "\n";
	}
}

// searches for the shortest path
// parameters: char** maze, int row & col
// return: 1 - success, 0 - no path exists, -1 - invalid maze
int mazeSearch(char** maze, int row, int col){
	int maxLen = row * col;				// max length of the maze
	Queue q(maxLen);					// initialize Queue object
	int found = 0;						// found status

	Loc start, noPred;					// coordinates for start
										// & for no predecessors

	noPred.row = -1;					// initialize row & col
	noPred.col = -1;

	int numStart = 0;					// location for start & finish
	int numFinish = 0;

	for(int i=0; i<row; i++){			// scans maze for start pos
		for(int j=0; j<col; j++){
			if(maze[i][j] == 'S'){
				start.row = i;
				start.col = j;
				numStart++;
			}
			if(maze[i][j] == 'F')		// scans maze for end pos
				numFinish++;
		}
	}
	if(numStart != 1 || numFinish != 1){
		return -1;						// checks number of start & finish
	}

	int** visit = new int*[row];		// once maze valid, dynamically alloc mem
	Loc** prev = new Loc*[row];
	
	for(int i=0; i<row; i++){
		visit[i] = new int[col];		// for each row, create a new column
		prev[i] = new Loc[col];
		for(int j=0; j<col; j++){
			visit[i][j] = 0;			// assign row/col coordinates w/ values
			prev[i][j] = noPred;
		}
	}

	visit[start.row][start.col] = 1;	// marks start pos as visited
	q.pushBack(start);
	Loc curr;							// sets current location

	while(!q.isEmpty() && found == 0){	// search while queue is not empty
		curr = q.popFront();
		Loc temp = curr;				// temp value with old current location

		int n, s, w, e;					// N, S, W & E coordinates
		n = curr.row - 1;
		w = curr.col - 1;
		s = curr.row + 1;
		e = curr.col + 1;

		if(curr.row == 0)				// prevents coordinates from being
			n = curr.row;				// out-of-bounds
		else if(curr.row == row - 1)
			s = curr.row;
		if(curr.col == 0)
			w = curr.col;
		else if(curr.col == curr.col - 1)
			e = curr.col;

		if(visit[n][curr.col] == 0){	// checks north location
			if(maze[n][curr.col] == 'F'){
				found = 1;
				break;
			}
			else if(maze[n][curr.col] == '.'){
				visit[n][curr.col] = 1;
				temp.row = n;
				prev[n][curr.col] = curr;
				q.pushBack(temp);
				temp = curr;
			}
		}
		if(visit[curr.row][w] == 0){	// checks west location
			if(maze[curr.row][w] == 'F'){
				found = 1;
				break;
			}
			else if(maze[curr.row][w] == '.'){
				visit[curr.row][w] = 1;
				temp.col = w; 
				prev[curr.row][w] = curr;
				q.pushBack(temp);
				temp = curr;
			}
		}
		if(visit[s][curr.col] == 0){	// checks south location
			if(maze[s][curr.col] == 'F'){
				found = 1;
				break;
			}
			else if(maze[s][curr.col] == '.'){
				visit[s][curr.col] = 1;
				temp.row = s;
				prev[s][curr.col] = curr;
				q.pushBack(temp);
				temp = curr;
			}
		}
		if(visit[curr.row][e] == 0){		// checks east location
			if(maze[curr.row][e] == 'F'){
				found = 1;
				break;
			}
			else if(maze[curr.row][e] == '.'){
				visit[curr.row][e] = 1;
				temp.col = e;
				prev[curr.row][e] = curr;
				q.pushBack(temp);
				temp = curr;
			}
		}
	}
	if(found == 1){							// traces path if path found
		while(maze[curr.row][curr.col] != 'S'){
			maze[curr.row][curr.col] = '*';
			curr = prev[curr.row][curr.col];
		}
	}
	for(int i=0; i< row; i++){				// delete columns from each row
		delete[] visit[i];
		delete[] prev[i];
	}
	delete[] visit;							// delete array of rows from mem
	delete[] prev;

	if(found == 1)							// return val based on results
		return 1;
	else if(q.isEmpty())
		return 0;
	return -1;
}
