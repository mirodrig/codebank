#include <iostream>
#include <map>
#include <cmath>
#include <cstdlib>
#include "puzzle_move.h"
#include "puzzle_heur.h"
#include "board.h"

using namespace std;

// parent of PuzzleMove is Board
PuzzleMove::PuzzleMove(Board* board) {
   tileMove = 0;
   b = new Board(*board);
   g = 0;
   h = 0;
   prev = NULL;
}

// constructor for subsequent search boards
PuzzleMove::PuzzleMove(int tile, Board *board, PuzzleMove *parent){
   tileMove = tile;
   b = new Board(*board);
   prev = parent;
   h = 0;
   g = (parent->g) + 1;
}

// Destructor
PuzzleMove::~PuzzleMove(){
   delete b;
}

// compare puzzle moves based on the f distance
// (needed to maintain priority queue distance)
bool PuzzleMove::operator<(const PuzzleMove& p) const {
   // can be used to compare g + h to p.g and p.h
   // if f is less than p.f then return true
   // else return false
   if((g + h) < (p.g + p.h)){
      return true;
   }
   else{
      if((g + h) == (p.g + p.h)){
         if(g > p.g){
            return true;
         }
      }
      return false;
   }
}

// determines the score for heuristic
void PuzzleMove::score(PuzzleHeuristic* ph){
   // contains a pointer to a PuzzleHeuristic
   // PuzzleHeuristic contains virtual int function compute
   h = ph->compute(*b);
}
