/********************************************
* Marlin Rodriguez & Jonathan Rodriguez
* vlg_parser_man.cpp
* PA7
********************************************/
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "design.h"
#include "gates.h"
#include "net.h"
#include "vlg_parser.h"
#include "vlg_parser_man.h"

using namespace std;

// defines specific types of gates using token
#define GATECHECK (token == "and") | (token == "or") | (token == "nand") | (token == "nor") | (token == "xor") | (token == "not")

// create an array of strings for distinct types of gates
string gates[6] = {"and", "or", "nand", "nor", "xor", "not"};

VlgParserMan::VlgParserMan() { }

Design* VlgParserMan::parse(char *in_file) {
	int line_number = 0; // initialize number of lines to zero
	
	//set all pointers to NULL initially to check for a valid instantiation
	Design* _pDesign = NULL; Net* _currNet = NULL; Gate* _currGate = NULL;
	
	vector<string> portlist;
	bool parse_error = false; // initialize flag for detecting error
	stringstream port_ss; stringstream ss2;
	
	ifstream ifile(in_file);
	if(ifile.fail()) {
		cout << "Unable to open file. Exiting program..." << endl;
		ifile.close();
		return NULL;
	} // end if
	string text_line;
	// continue reading while we have not reached the end of .v file
	while(!ifile.eof()) {
		getline(ifile, text_line);
		line_number++;
		stringstream ss(text_line);
		string token; string next_item; string port_list;
		char is_ss2 = '\0'; // set initial value to NULL
		ss 	>> token;
		// determines if the current line is empty
		if (token.empty()) {
			continue;
		}
		// if the current item extracted is the string "module"
		if(token == "module") {
			getline(ss, next_item, '(');
			string getmodule;
			stringstream getmodule_ss(next_item);
			getmodule_ss >> getmodule; 
			// declare and pass it to the module name
			_pDesign = new Design(getmodule);
			getline(ss, port_list, ')');
			parse_port_list(port_ss, port_list, parse_error);
			
			getline(ss, port_list);
			ss2.str(port_list); ss2 >> is_ss2;
			// if there is syntax error, including semicolon, return an error
			if(parse_error || is_ss2 != ';') {
				cerr << "Syntax error at line: " << line_number << endl;
				ifile.close();
				return NULL; // return NULL address
			} // end if
		} // end if
		// if the current item extracted is the string "input"
		else if (token == "input") {
			if (!_pDesign) {
				cerr << "Invalid input at line: " << line_number << endl;
				ifile.close();
				return NULL; // return NULL address
			} // end if
			ss >> next_item;
			if (*(next_item.end()-1) != ';') {
				cerr << "Missing semicolon at line: " << line_number << endl;
				ifile.close();
				return NULL; // return NULL address
			} // end if
			// this line helps erase the semicolon for code analysis
			next_item.erase(next_item.end()-1);
			_pDesign->addPI(next_item);
		} // end else if
		// if the current item extracted is the string "output"
		else if(token == "output") {
			// if a valid address has not been instantiated, return error msg.
			if(!_pDesign) {
				cerr << "Invalid output at line: " << line_number << endl;
				ifile.close();
				return NULL;
			} // end if
			ss >> next_item;
			if(*(next_item.end()-1) != ';') {
				cerr << "Missing semicolon at line: " << line_number << endl;
				ifile.close();
				return NULL;
			} // end if
			next_item.erase(next_item.end()-1);
			_pDesign->addPO(next_item);
		} // end else if
		// if the current item extracted is the string "wire"
		else if(token == "wire") {
			if (!_pDesign) {
				cerr << "Invalid input at line: " << line_number << endl;
				ifile.close();
				return NULL;
			} // end if
			ss >> next_item;
			if (*(next_item.end()-1) != ';') {
				cerr << "Missing semicolon at line: " << line_number << endl;
				ifile.close();
				return NULL;
			} // end if
			next_item.erase(next_item.end()-1);
			_currNet = _pDesign->addFindNet(next_item);	
		} // end else if
		// checks the gates that come up
		else if(GATECHECK) {
			if(!_pDesign) {
				cerr << "Invalid input at line: " << line_number << endl;
				ifile.close();
				return NULL;
			} // end if
			int gtype = 0;
			// selects which gate to use from the array
			for(int i = 0; i < 6; i++) {
				if (token == gates[i]) {
					gtype = i;
					break;
				}
			} // end for
			ss >> next_item;
			// initialize the delay to a certain value
			int delay = -1;
			string gate_name; stringstream gate_ss;
			if (next_item[0] == '#') {
				next_item.erase(0,1);
				delay = atoi(next_item.c_str());
				ss >> next_item;
				gate_ss.clear(); gate_ss.str(next_item);
				getline(gate_ss, gate_name, '(');
			} // end if
			else {
				delay = 1; gate_ss.clear();
				gate_ss.str(next_item);
				getline(gate_ss, gate_name, '(');
			} // end else
			ss.str(text_line); //reassign text_line to ss.
			getline(ss, next_item, '(');
			_currGate = _pDesign->addFindGate(gtype, gate_name, delay);
			getline(ss, port_list, ')');
			portlist = parse_port_list(port_ss, port_list, parse_error);
			if(portlist.size() < 2) {
				cerr << "Not enough I/O for " << gate_name << " on line: " << line_number << endl;
				ifile.close(); return NULL;
			} // end if
			_currNet = _pDesign->addFindNet(portlist[0]);
			_currGate->addOutput(_currNet);
			_currNet->addDriver(_currGate);
			vector<string>::iterator it;
			for(it = (portlist.begin() + 1); it != portlist.end(); ++it) {
				_currNet = _pDesign->addFindNet(*it);
				_currGate->addInput(_currNet);
				_currNet->addLoad(_currGate);
			} // end for
			getline(ss, port_list);
			ss2.clear();
			ss2.str(port_list);
			ss2 >> is_ss2;
			if (parse_error || (is_ss2 != ';')) {
				cerr << "Syntax error at line: " << line_number << ". Now Exiting..." << endl;
				ifile.close();
				return NULL;
			} // end if			
		} // end else if
		else if (token == "endmodule") {
			break;
		}
		// does not take to account comments
		else if(token == "//") {
			continue;
		} // end else if
		else {
			cerr << "Syntax error at line: " << line_number << ". Now Exiting..." << endl;
			ifile.close();
			return NULL;
		} // end else
	} // end while
	ifile.close();
	cout << "Parse Successful!" << endl;
	return _pDesign;
} // end function

vector<string> VlgParserMan::parse_port_list(stringstream &ss_stream, string &parse_message, bool &parse_err) {
	vector<string> design_ports;
	ss_stream.clear(); ss_stream.str(parse_message);
	stringstream next_item;
	string temp_item = "initial";
	string new_item;
	while(getline(ss_stream, temp_item, ',')) {
		next_item.str(temp_item);
		next_item >> new_item;
		string comma_checker;
		next_item >> comma_checker;
		design_ports.push_back(new_item);
		if(comma_checker != "") {
			cout << "Misplaced comma." << endl;
			parse_err = true;
		}
		next_item.clear();
	} // end while
	return design_ports;
} // end function



