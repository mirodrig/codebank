#ifndef _CAESARLIB_H
#define _CAESARLIB_H

// determines if given char is an Engligh letter
// parameter: char
// return: boolean
bool isLetter(char ch);

// returns shifted char (if letter) of input char
// parameter: char, int steps
// return: character after shifting
char image(char ch, int steps);

// shifts all characters in the file and prints it to console
// parameter: char array filename, number of steps
int printFileImage(const char filename[], int steps);

#endif