#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <map>
#include <functional>

using namespace std;

class Board{
public:
	Board(int dim);							// construct solved board w/ given dim
  	// Init a board of given size and scramble it with numInitMoves 
  	// by moving the space tile with a randomly chosen direction N, W, S, E
  	// some of which may be invalid, in which case we skip that move
	Board(int size, int numInitMoves, int seed);
	Board(const Board &b);					// copy constructor
	~Board();								// destructor
	void move(int tile);					// swap blank w/ specified tile
  	// Generate potential moves and fill in the map with 
  	// Key=tile, Value=Ptr to corresponding Board
  	// Clear the moveMap as the first order of business.
  	//void potentialMoves(map<int, Board*> &moveMap); 
	map<int, Board*> potentialMoves() const; 
	bool solved() const;					// return true if board is solved
  	// Operators
	friend ostream& operator<<(ostream &os, const Board &b);
	bool operator<(const Board& rhs) const;
  
	// Accessors
	int getTile(int loc) const;				// return tile @ location in array
	int getSize() const;					// return size of board (i.e. board)
	int getDim() const;						// return dimension of side of board
  
 private:
  int *_tiles;								// pointer to array (i.e. board)
  int _size;								// Size of the array
};

#endif
