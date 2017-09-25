#include <cmath>
#include "board.h"
#include "puzzle_heur.h"

using namespace std;

int PuzzleManhattanHeuristic::compute(const Board& b) {
  int heur = 0; // heuristic number
  // create a for loop iterating through size of Board
  for(int i = 0; i < b.getSize(); i++){
     if(b.getTile(i) != i && b.getTile(i) != 0){
        // horizontal offset
        heur += abs((b.getTile(i) % b.getDim()) - (i % b.getDim()));
        // vertical offset
        heur += abs((b.getTile(i) / b.getDim()) - (i / b.getDim()));
     }
  }
  return heur;
}

int PuzzleOutOfPlaceHeuristic::compute(const Board& b) {
  int heur = 0;
  for(int i = 0; i < b.getSize(); i++){
     if(b.getTile(i) != i && b.getTile(i) != 0){
        heur++;
     }
  }
  return heur;
}

// BFS assumes h = 0 at all times
int PuzzleBFSHeuristic::compute(const Board& b) {
  return 0;
}
