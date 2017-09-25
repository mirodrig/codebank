#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <iterator>
#include "puzzle_solver.h"

using namespace std;

// Constructor (makes a copy of Board and stores it in _b)
PuzzleSolver::PuzzleSolver(const Board& b, PuzzleHeuristic *ph) :
   _b(b), _expansions(0), _ph(ph)
{   }

PuzzleSolver::~PuzzleSolver(){
}

// run the A* search algorithm
void PuzzleSolver::run(){
   PuzzleMoveHeap open_list;
   PuzzleMoveSet closed_list;
   Board* _board = new Board(_b); // create a new pointer to a Board
   // creates a dynamically allocated Board with no parents
   PuzzleMove* start_board = new PuzzleMove(_board);
   // push back and insert the pointer to the start_board to the heap/set
   open_list.push(start_board);
   closed_list.insert(start_board);

   // while open list is not empty and puzzle is not solved
   while( !open_list.empty() && !_board->solved() ){
      // set min state equal to lowest f value in open list
      PuzzleMove* minState = open_list.top();
      open_list.pop(); // remove the element from the open list
      if( (minState->b)->solved() ){
         // walk back to _solution using (*PuzzleMove).prev.tileMove
         while(minState->tileMove != 0){
            _solution.push_front(minState->tileMove);
            minState = minState->prev;
         }
         delete _board;
         if(_solution.size() == 0){
            break;
         }
         cout << "Try this sequence:" << endl;
         for(int i = 0; i < int(_solution.size()); i++){
            cout << _solution[i] << " ";
         }
         cout << endl;
         cout << "(Expansions = " << _expansions << ")" << endl;
         break;
      }
      // generates a map of potential moves, int keys and Board values
      map<int, Board*> Pot_Moves = (minState->b)->potentialMoves();
      for(map<int, Board*>::iterator bit = Pot_Moves.begin();
         bit != Pot_Moves.end(); ++bit){
         // dynamically allocate a puzzle move
         PuzzleMove* s = new PuzzleMove((bit->first),(bit->second),minState);
         // determine if s is not in the closed list
         PuzzleMoveSet::iterator it = closed_list.find(s);
         if(it != closed_list.end()){
            delete s;
         }
         else{
            s->score(_ph);
            open_list.push(s);
            closed_list.insert(s);
            _expansions++;
         }
      }
      for(map<int, Board*>::iterator ix = Pot_Moves.begin();
         ix != Pot_Moves.end(); ++ix){
         delete ix->second;
      }
   }
   // cleanup and return appropriate values
   for(PuzzleMoveSet::iterator sit = closed_list.begin();
   sit != closed_list.end(); ++sit){
      // cout << "deleting leftover closed-list moves" << endl;
      delete *sit;
   }
}

deque<int> PuzzleSolver::getSolution(){
   return _solution;
}

int PuzzleSolver::getNumExpansions(){
   return _expansions;
}
