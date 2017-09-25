/****************************************************
* Marlin Rodriguez & Jonathan Rodriguez
* logicsim.h
* PA7
****************************************************/
#ifndef LOGICSIM_H
#define LOGICSIM_H
#include "design.h"
#include "gates.h"
#include "net.h"
#include <string>
#include <deque>
#include <set>
#include <map>

using namespace std;

enum {INPUTNET, NETVALUES, BLANKSPACE};

// function prototype
int line_define(string identification);

class LogicSim {
 public:
 	// constructor with string and Design parameters
 	LogicSim(string input_file, Design *d);
 	// initializes the topological search which will occur once in program
 	void run_simulation(vector<Net* > topolist);
 	// dumps the simulation file to an output file
 	void file_dump(string output_file, Design *d);

 	// member variables
 	vector<map<string, char> > input_value; // map with input name and different values
 	vector<map<string, char> > test_results; // map with output pins and result values 
 	int line_number; // line number (for parsing and error detection)
 	vector<string> sorted_PI; // vector with names of ordered PI
 	set<string> unique_PI; // set for unique identifier of PI
};

#endif