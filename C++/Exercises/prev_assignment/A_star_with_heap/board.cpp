#include <iostream>
#include <iomanip>
#include <map>
#include <cmath>
#include <cstdlib>
#include "board.h"
using namespace std;

// constructs a solved board of a given dimension
Board::Board(int dim){
  _size = dim * dim;
  _tiles = new int[_size];
  for(int i = 0; i < _size; i++){
    _tiles[i] = i;
  }
}
// initializes a board with dimension, initial shuffles and a seed
Board::Board(int dim, int numInitMoves, int seed){
  _size = dim * dim;                      // initialize variables
  _tiles = new int[_size];
  srand(seed);                            // make random moves truely random
  for(int i = 0; i < _size; i++){
    _tiles[i] = i;
  }
  int blankLoc = 0;
  while(numInitMoves > 0){
    int r = rand()%4;
    int randNeighbor = -1;
    if(r == 0){
      int n = blankLoc - dim;
      if(n >= 0){
          randNeighbor = n;
      }
    }
    else if(r == 1){
      int w = blankLoc - 1;
      if(blankLoc % dim != 0){
          randNeighbor = w;
      }
    }
    else if(r == 2){
      int s = blankLoc + dim;
      if(s  < _size){
          randNeighbor = s;
      }
    }
    else {
      int e = blankLoc + 1;
      if(blankLoc % dim != dim-1){
          randNeighbor = e;
      }
    }
    if(randNeighbor > -1){
      _tiles[blankLoc] = _tiles[randNeighbor];
      _tiles[randNeighbor] = 0;
      blankLoc = randNeighbor;
      numInitMoves--;
    }
  }
}

// Destructor
Board::~Board(){
  delete [] _tiles;
}

// swaps blank with a specified tile
void Board::move(int tile){
  int dim = static_cast<int>(sqrt(_size));
  int tr, tc, br, bc;

  // find the tile
  int i=-1;
  while(_tiles[++i] != tile);
  tr = i / dim;
  tc = i % dim;

  // find the blank
  int j=-1;
  while(_tiles[++j] != 0);
  br = j / dim;
  bc = j % dim;
  
  // if they aren't next to each other just return
  if( abs(static_cast<double>(tr-br)) + abs(static_cast<double>(tc-bc)) != 1){
    cout << "Invalid move of tile " << tile << " at ";
    cout << tr << "," << tc << " and blank spot at ";
    cout << br << "," << bc << endl;
    return;
  }
  // Swap tile and blank spot
  _tiles[j] = tile;
  _tiles[i] = 0;
}

// make the copy constructor
Board::Board(const Board &b){
  _size = b.getSize();
  _tiles = new int[_size];
  for(int i = 0; i < _size; i++){
    _tiles[i] = b._tiles[i];
  }
}

map<int, Board*> Board::potentialMoves() const{
  Board* temp;
  map<int, Board*> _BoardList;
  int _blankIndex = -1;
  while(_tiles[++_blankIndex] != 0);
  if(getDim() > 1){
    // move blank tile up
    if(_blankIndex / getDim() > 0){   
      temp = new Board(*this);
      temp->move(_tiles[_blankIndex - getDim()]);
      _BoardList[_tiles[_blankIndex - getDim()]] = temp;
    }
    // move blank tile down
    if(_blankIndex / getDim() < getDim() - 1){
      temp = new Board(*this);
      temp->move(_tiles[_blankIndex + getDim()]);
      _BoardList[_tiles[_blankIndex + getDim()]] = temp;
    }
    // move blank tile left
    if(_blankIndex % getDim() > 0){
      temp = new Board(*this);
      temp->move(_tiles[_blankIndex - 1]);
      _BoardList[_tiles[_blankIndex - 1]] = temp;
    }
    // move blank tile right
    if(_blankIndex % getDim() < getDim() - 1){
      temp = new Board(*this);
      temp->move(_tiles[_blankIndex + 1]);
      _BoardList[_tiles[_blankIndex + 1]] = temp;
    }
  }
  return _BoardList;
}

// returns true if solved, false otherwise
bool Board::solved() const{
  // compare elements of _tiles to ordered numbers
  for(int i = 0; i < _size; i++){
    if(_tiles[i] != i){
      return false;
    }
  }
  return true;
}
/******************** Operators ********************/
ostream& operator<<(ostream &os, const Board &b){
  // display _tiles in dim * dim order
  os << setw(3);
  for(int i = 0; i < b._size; i++){
    if((i % b.getDim() == 0) && i != 0){
      os << endl;
    }
    if(b._tiles[i] == 0){
      os << " ";
    }
    else{
      os << b._tiles[i];
    }
    os << setw(3);
  }
  os << endl;
  return os;
}

bool Board::operator<(const Board &rhs) const{
  // can implement a for loop to compare _tiles and rhs_tiles
  for(int i = 0; i < _size; i++){
    if(_tiles[i] < rhs._tiles[i]){
      return true;
    }
    else if(_tiles[i] > rhs._tiles[i]){
      return false;
    }
  }
  return false;
}

/****************** Accessors ******************/
// returns tile at location los in the array
int Board::getTile(int loc) const{
  return _tiles[loc]; // returns locth element of array
}
// returns size of the array (Board)
int Board::getSize() const{
  return _size;
}
// returns the dimension of the side of the Board
int Board::getDim() const{
  return static_cast<int>(sqrt(_size));
}
