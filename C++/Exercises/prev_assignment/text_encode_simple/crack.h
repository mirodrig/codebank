#ifndef _CRACK_H
#define _CRACK_H

// returns score when input char is shited (if result is letter)
// parameters: char ch and int shift
// return: double score
double charScore(char ch, int shift);

// returns score when contents of entire file are shifted
// parameters: char array with filename, int shift
// return: double score
double fileScore(const char filename[], int shift);

#endif