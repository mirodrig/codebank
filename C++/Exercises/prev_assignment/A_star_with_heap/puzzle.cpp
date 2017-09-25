#include <iostream>
#include <cstdlib>
#include <deque>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"

int main(int argc, char *argv[]){
  if(argc < 5){
    cerr << "Usage: ./puzzle size initMoves seed heur" << endl;
    return 1;
  }
  int size, initMoves, seed, heur;
  size = atoi(argv[1]);
  initMoves = atoi(argv[2]);
  seed = atoi(argv[3]);
  heur = atoi(argv[4]);
  Board b(size, initMoves, seed); // starting Board
  
  PuzzleHeuristic* ph;
  if(heur == 0){
     ph = new PuzzleBFSHeuristic;
  }
  else if(heur == 1){
     ph = new PuzzleOutOfPlaceHeuristic;
  }
  else{
     ph = new PuzzleManhattanHeuristic;
  }

  // gameplay implementation
  while(!b.solved()){
     cout << b;
     cout << "Enter tile number to move or -1 for a cheat: ";
     int tile; cin >> tile;
    PuzzleSolver game(b, ph);
    if(tile == 0){
        break;
     }   
     else if(tile > 0){
        b.move(tile);
     }
     else{
        game.run();   
     }
  }
  if(b.solved()){
     cout << b << "You win!" << endl;
  }
  else{
     cout << "Goodbye" << endl;
  }
  delete ph;
  return 0;
}
