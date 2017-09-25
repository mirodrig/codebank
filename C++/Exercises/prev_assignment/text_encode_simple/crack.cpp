#include <fstream>
#include <cstring>
#include "caesarlib.h"
#include "crack.h"

// frequencies of letters in large sample of English text
const double enfreq[26] = {0.0793, 0.0191, 0.0392, 0.0351, 0.1093,
   0.0131, 0.0279, 0.0238, 0.0824, 0.0024, 0.0103, 0.0506, 0.0277,
   0.0703, 0.0602, 0.0274, 0.0019, 0.0705, 0.1109, 0.0652, 0.0321,
   0.0098, 0.0093, 0.0026, 0.0156, 0.0040};

// database for upper and lower case letters
char upperLetter[26] = {'A','B','C','D','E','F','G','H','I','J','K',
	'L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
char lowerLetter[26] = {'a','b','c','d','e','f','g','h','i','j','k','l',
	'm','n','o','p','q','r','s','t','u','v','w','x','y','z'};

// returns score when input char is shited (if result is letter)
// parameters: char ch and int shift
// return: double score
double charScore(char ch, int shift){
	int n = 0;							// array index
	char newLetter = image(ch, shift);	// create shifted letter

	if(!isLetter(newLetter))			// determine if newLetter is letter
		return 0;
	// scan through letter freq. array to determine frequency
	for(int i=0; i<26; i++){
		if(newLetter == upperLetter[i] || newLetter == lowerLetter[i])
			break;
		else
			n++;
	}
	return enfreq[n];
}

// returns score when contents of entire file are shifted
// parameters: char array with filename, int shift
// return: double score
double fileScore(const char filename[], int shift){
	char message[100];
	double totalScore = 0;
	std::ifstream ifile(filename);

	if(!ifile.good())					// determine if file exists
		return 1;
	ifile.getline(message, 100);		// get a line of text from file

	while(ifile.good()){
		int n = 0;
		for(; n<strlen(message); n++){	// the iterate thru each line of text
			totalScore += charScore(message[n], shift);
		}
		ifile.getline(message, 100);	// get another line of text from file
	}
	ifile.close();
	return totalScore;
}