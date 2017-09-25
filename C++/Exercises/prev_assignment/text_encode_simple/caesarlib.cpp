#include <fstream>
#include <iostream>
#include <cstring>
#include "caesarlib.h"

// determines if given char is an Engligh letter
// parameter: char
// return: boolean
bool isLetter(char ch){
	// determine if input char is an ASCII letter
	if(ch > 64 && ch < 91){
		return true;
	}
	else if(ch > 96 && ch < 123){
		return true;
	}
	return false;
}

// returns shifted char (if letter) of input char
// parameter: char, int steps
// return: character after shifting
// assumes number of steps is 0 to 26
char image(char ch, int steps){
	if(ch > 64 && ch < 91){				// case for uppercase letters
		if(steps < 0){
			for(int i=0; i<steps; i++){
				ch--;
				if(ch < 65)
					ch = 90;			// when we get past A go to Z
			}
		}
		else{
			for(int i=0; i<steps; i++){
				ch++;
				if(ch > 90)
					ch = 65;			// we we get past Z go to A
			}
		}
	}
	else if(ch > 96 && ch < 123){		// case for lowercase letters
		if(steps < 0){
			for(int i=0; i<steps; i++){
				ch--;
				if(ch < 97)
					ch = 122;			// when we get to a go to z
			}
		}
		else{
			for(int i=0; i<steps; i++){
				ch++;
				if(ch > 122)
					ch = 97;			// if we get past z go to a
			}
		}
	}
	return ch;
}

// shifts all characters in the file and prints it to console
// parameter: char array filename, number of steps
int printFileImage(const char filename[], int steps){
	char message[100];					// char array for each line from textfile
	std::ifstream ifile(filename);

	if(!ifile.good())
		return 1;						// determine if the file exists
	ifile.getline(message, 100);		// input stream from textfile

	while(!ifile.fail()){
		int n=0;						// counter for elements of char array
		while(n < strlen(message)){
			message[n] = image(message[n], steps);
			std::cout << message[n];
			n++;
		}
		std::cout << "\n";
		ifile.getline(message, 100);
	}

	ifile.close();
	return 0;
}
