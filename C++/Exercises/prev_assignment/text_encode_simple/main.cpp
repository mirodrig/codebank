#include <iostream>
#include "caesarlib.h"
#include "crack.h"

int main(int argc, char* argv[]){
	if(argc != 2){
		std::cout << "Wrong number of arguments.\n";
		std::cout << "Usage: ./crack textfile\n";
		return 1;
	}
	int shift = 0;					// initialize shift & score to 0
	double scorekeeper = 0;

	// go through every possible value of shift to determine best score
	for(int i=0; i<26; i++){
		if(fileScore(argv[1], i) > scorekeeper){
			scorekeeper = fileScore(argv[1], i);
			shift = i;
		}
	}

	int res = printFileImage(argv[1], shift);

	if(res != 0){					// make sure input file exists
		std::cout << "The input file does not exist.\n";
		return 1;
	}
	return 0;
}