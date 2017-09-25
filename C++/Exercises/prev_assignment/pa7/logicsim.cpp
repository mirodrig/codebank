/****************************************************
* Marlin Rodriguez & Jonathan Rodriguez
* logicsim.cpp
* PA7
****************************************************/
#include "logicsim.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream> // using string stream
#include <vector>
#include <stdexcept> // calling exceptions
#include <algorithm>
#include <map>

using namespace std;

// constructor with string and design parameters
LogicSim::LogicSim(string input_file, Design *d){
	/* use c_str() to utilize a pointer to a string since we
		agrv[2] will be passed as *char[] */
	line_number = 0;
	ifstream ifile(input_file.c_str());
	while(!ifile.fail()){
		line_number++; // increment line number to first line
		string current_line; // current line (for string stream parsing)
		getline(ifile, current_line); // current_line takes file input
		// create a string stream variable for the current line. We'll take it apart
		stringstream ss(current_line);

		// declare a string to be a line in input file then input to string stream
		string firstLine;
		ss >> firstLine;
		try{
			switch(line_define(firstLine)){
				// checks the inputs for the file
				case INPUTNET: {
					sorted_PI.push_back(firstLine);
					unique_PI.insert(firstLine);
					// check to see if the inputs are part of the design
					
					// grabbing a vector of Net*'s from the design
					if(d->findNet(firstLine) == NULL){
					// if((d->allNets())->find(firstLine) == d->allNets().end()){
						cout << firstLine << endl;
						throw runtime_error("A specified PI on the first line does not exist in the design 1");
					} // end if
					while(ss.good()){
						string dummy;
						ss >> dummy;
						sorted_PI.push_back(dummy);
						unique_PI.insert(dummy);
						if(d->findNet(dummy) == NULL) {
						// if(d->allNets().find(dummy) == d->allNets().end()){
							cout << dummy << endl;
							throw runtime_error("A specified PI on the first line does not exist in the design 2");
						}
					} // end while
					
					// cout << d->getPINets().size() << endl; // test the size -> 3 inputs total
					// function clearly gets the outputs...
					// cout << d->getPONets().size() << endl; // test to see size of outputs

					if(d->getPINets().size() != unique_PI.size()){
						throw runtime_error("number of input values doesn't match PI count on first line");
					}
					break;
				} // end INPUT case
				// check the values of the extracted data
				case NETVALUES: {
					map<string, char> select_line; // map with string keys and char values
					int count = 0;
					select_line[sorted_PI.at(count)] = firstLine[0];
					// check if the values contain '0' '1' or 'X'
					if(!(firstLine[0] == '1' || firstLine[0] == '0' || firstLine[0] == 'X')){
						throw runtime_error("input is not in set {0, 1, X}");
					}
					while(ss.good()){
						count++;
						char temp;
						ss >> temp;
						if(ss.fail()){
							break;
						}
						// while we keep extracting input values, check for correct formatting
						if(!(temp == '1' || temp == '0' || temp == 'X')){
							throw runtime_error("input is not in set {0, 1, X}");
						}
						if(count < int(sorted_PI.size())){
							select_line[sorted_PI.at(count)] = temp;
						} // end if
						else{
							stringstream ss1;
							ss1 << "Number of input values is not equal to the number of PI's on the first line";
							throw runtime_error(ss1.str());
						} // end else
					} // end while
					// check the size of the current line
					if(select_line.size() != sorted_PI.size()){
						stringstream ss1;
						ss1 << "Number of input values is not equal to the number of PI's on the first line";
						throw runtime_error(ss1.str());
					} // end if
					input_value.push_back(select_line);
					break;
				} // end VALUES case
				// case for the blank spaces
				case BLANKSPACE: {
					break; // if there is a blank space, continue reading
				}
				default: {
					throw runtime_error("syntax error");
					break;
				}
			} // end switch statement
		} // end try exception
		catch(runtime_error &error){
			string line_current;
			stringstream ss2;
			ss2 << line_number;
			line_current = ss2.str();
			throw runtime_error("On line " + line_current + " " + error.what());
		} // end catch
	} // end while
} // end constructor

// input_value is a vector containing maps with string keys with char values
void LogicSim::run_simulation(vector<Net* >topolist){
	vector<map<string, char> >::iterator ix;
	for(ix = input_value.begin(); ix != input_value.end(); ix++){
		map<string, char> trial_input = *ix;
		map<string, char> trial_result;
		vector<Net *>::iterator jx;
		// iterate through all of the Nets of the topological list
		for(jx = topolist.begin(); jx != topolist.end(); jx++){
			Net* curr_net = *jx; // current net
			string net_name = curr_net->name();

			// if the net does not exist in the input_value set
			if(unique_PI.find(net_name) == unique_PI.end()){
				trial_result[net_name] = curr_net->computeVal();
			}
			else{
				curr_net->setVal(trial_input[net_name]);
			}
		}
		test_results.push_back(trial_result);
	}

	/*********** test to see what is present in the results ***************/
	
	/*vector<map<string, char> >::iterator ip;
	for(ip = test_results.begin(); ip != test_results.end(); ip++){
		// find a way to iterate through each of the subsequent maps
		for(map<string, char>::iterator pp = (*ip).begin(); pp != (*ip).end(); pp++){
			// *ip returns a map with string and char
			// *pp returns
			cout << pp->first << " followed by: " << pp->second << endl;
		}
	}*/
} // end run simulation

void LogicSim::file_dump(string output_file, Design *d){
  ofstream ofile(output_file.c_str());
  /*************** output file header *****************/
  vector<string>::iterator ix;
  for(ix = sorted_PI.begin(); ix != sorted_PI.end(); ix++){
  	ofile << *ix << " ";
  } // end for
  
  ofile << "=> ";
  vector<Net *> outNets = d->getPONets();
  vector<Net *>::iterator mx;
  
  for(mx = outNets.begin(); mx != outNets.end(); mx++){
  	ofile << (*mx)->name() << " ";
  } // end for
  ofile << endl;
  /***************** end header display ****************/

  /************ for each line of the file output ***************/
  int line_index = 0;
  for(vector<map<string, char> >::iterator kt = input_value.begin(); kt != input_value.end(); kt++){
  	map<string, char> input_values = *kt;
  	vector<string>::iterator mt;
  	for(mt = sorted_PI.begin(); mt != sorted_PI.end(); mt++){
  		ofile << input_values[*mt] << " ";
  	} // end for
  	ofile << "=> ";
  	
  	///////////////// display the output information ////////////////////

  	vector<Net *> POS = d->getPONets();
  	vector<Net *>::iterator jt; // iterates through POS

  	// iterating through all of the outputs of the Design
  	for(jt = POS.begin(); jt != POS.end(); jt++){
  		// test_results type map. test_results.at(line_index) gives
  		// something wrong with test_results, not getting any values
  		
  		// line_index returns an integer
  		// map.at(int)[stirng]

  		// ofile << test_results.at(line_index);
  		ofile << test_results.at(line_index)[(*jt)->name()];
  		ofile << "@" << (*jt)->computeDelay() << " ";
  	}

  	line_index++;
  	ofile << endl;
  
  } // end for
  ofile.close();
} // end dump function

int line_define(string identification){
	if((identification == "0") || (identification == "1")){
		return NETVALUES;
	}
	else if(isalpha(identification.c_str()[0])){
		return INPUTNET;
	}
	//else {
	else if((identification == " ") || (identification == "\n") || (identification == "\t") || (identification == "")){
		return BLANKSPACE;
	}
} // end function