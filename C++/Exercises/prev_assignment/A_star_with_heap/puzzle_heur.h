#ifndef PUZZLE_HEUR_H
#define PUZZLE_HEUR_H

#include <cmath>
#include "board.h"

class PuzzleHeuristic{								// parent object for heuristic
public:
	virtual ~PuzzleHeuristic(){ }					// all children have destructors
  	virtual int compute(const Board& b) = 0;		// all children compute heuristic
};

class PuzzleManhattanHeuristic : public PuzzleHeuristic {
public:
	int compute(const Board& b);
};

class PuzzleOutOfPlaceHeuristic : public PuzzleHeuristic {
	public:
	int compute(const Board& b);
};

class PuzzleBFSHeuristic : public PuzzleHeuristic {
	public:
	int compute(const Board& b);
};

#endif