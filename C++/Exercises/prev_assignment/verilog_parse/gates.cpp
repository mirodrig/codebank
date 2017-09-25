/****************************************************
* Marlin Rodriguez & Jonathan Rodriguez
* Programming Assignment 6
* gates.cpp
****************************************************/
#include <iostream>
#include <vector>
#include <ostream>
#include "net.h"
#include "gates.h"

using namespace std;

Gate::Gate(string n) {
	inst_name = n;
	delay = 0;
	inputs = new vector<Net *>();
	output = NULL;
}

Gate::Gate(string n, int d) {
	inst_name = n;
	delay = d;
	inputs = new vector<Net *>();
	output = NULL;
}

string Gate::name() const { return inst_name; }

int Gate::getDelay() const {
	if(delay == 0){
		return 1;
	}
	else{
		return delay;
	}
}

void Gate::addInput(Net* n){ inputs->push_back(n); }

vector<Net *>* Gate::getInputs() { return inputs; }

void Gate::addOutput(Net *n) { output = n; }

Net* Gate::getOutput() const { return output; }

int Gate::getNumInputs() const {
	return static_cast<int>(inputs->size());
}

/*********** Functions for the AND gate ***************/
And::And(string n, int d) : Gate(n, d) {
	inst_name = n;
	delay = d;
}

And::~And() {
	delete [] inputs;
	delete output;
}

char And::eval() {
	char value;
	// if input size is one
	if(static_cast<int>(inputs->size()) == 1) {
		value = '0';
	}
	// if there is more than one input
	else {
		vector<Net *>::iterator ix = inputs->begin();
		value = (*ix)->getVal();
		ix++;
		while(ix != inputs->end()){
			if((*ix)->getVal() == 'X'){
				// if value == 'X', then value is unchanged
				if(value == '1'){
					value = 'X';
				}
				else if(value == '0'){
					value = '0';
				}
			}
			if((*ix)->getVal() == '0'){
				value = '0';
			}
			// if (*ix)->getVal() == 1 then value is unchanged
			ix++;
		} // end while
	} // end else
	return value;
}

void And::dump(ostream &os){
	// display information onto the screen
	os << "and" << " ";
	if(delay != 1 && delay != 0){
		os << "#" << delay << " ";	
	}
	os << inst_name << "(" << output->name() << ", ";
	vector<Net *>::iterator it;
	for(it = inputs->begin(); it != inputs->end(); it++){
		os << (*it)->name();
		if(it == inputs->end() - 1){
			os << ");";
			break;
		}
		else{
			os << ", ";
		}
	}
	os << endl;
}

/************* Functions for OR gate *****************/
Or::Or(string n, int d) : Gate(n, d) {
	inst_name = n;
	delay = d;
}

Or::~Or() {
	delete [] inputs;
	delete output;
}

char Or::eval() {
	char value;
	// if input size is one
	if(static_cast<int>(inputs->size()) == 1){
		value = inputs->front()->getVal();
	}
	// if there are more than one input
	else{
		vector<Net *>::iterator ix = inputs->begin();
		value = (*ix)->getVal();
		ix++;
		while(ix != inputs->end()){
			if((*ix)->getVal() == 'X'){
				if(value == '0'){
					value = 'X';
				}
			}
			if((*ix)->getVal() == '1'){
				value = '1';
			}
			// if (*ix)->getVal() == '0' then value remains unchanged
			ix++;
		} // end while
	} // end else
	return value;
}
void Or::dump(ostream &os){
	// display information onto the screen
	os << "or" << " ";
	if(delay != 1 && delay != 0){
		os << "#" << delay << " ";	
	}
	os << inst_name << "(" << output->name() << ", ";
	vector<Net *>::iterator it;
	for(it = inputs->begin(); it != inputs->end(); it++){
		os << (*it)->name();
		if(it == inputs->end() - 1){
			os << ");";
			break;
		}
		else{
			os << ", ";
		}
	}
	os << endl;
}

/*************** Functions for NOR gate *****************/
Nor::Nor(string n, int d) : Gate(n, d) {
	inst_name = n;
	delay = d;
}

Nor::~Nor() {
	delete [] inputs;
	delete output;
}

char Nor::eval() {
	char value;
	// if input size is one
	if(static_cast<int>(inputs->size()) == 1){
		if(inputs->front()->getVal() == 'X') {
			value = 'X';
		}
		else if(inputs->front()->getVal() == '0') {
			value = '1';
		}
		else if(inputs->front()->getVal() == '1') {
			value = '0';
		}
	}
	else{ // more than 1 input
		vector<Net *>::iterator ix = inputs->begin();
		value = (*ix)->getVal();
		ix++;
		while(ix != inputs->end()){
			if((*ix)->getVal() == 'X'){
				// if (*ix)->getVal() == 'X', value is unchanged
				if(value == '0'){
					value = 'X';
				}
				else if(value == '1'){
					value = '0';
				}
			} // end if
			if((*ix)->getVal() == '0'){			
				if(value == '0'){
					value = '1';
				}
				else if(value == '1'){
					value = '0';
				}
			} // end if
			if((*ix)->getVal() == '1'){
				value = '0';
			} // end if
			ix++;
		} // end while
	} // end else
	return value;
}
void Nor::dump(ostream &os){
	// display information onto the screen
	os << "nor" << " ";
	if(delay != 1 && delay != 0){
		os << "#" << delay << " ";	
	}
	os << inst_name << "(" << output->name() << ", ";
	vector<Net *>::iterator it;
	for(it = inputs->begin(); it != inputs->end(); it++){
		os << (*it)->name();
		if(it == inputs->end() - 1){
			os << ");";
			break;
		}
		else{
			os << ", ";
		}
	}
	os << endl;
}

/************** Functions for NAND gate *****************/
Nand::Nand(string n, int d) : Gate(n, d) {
	inst_name = n;
	delay = d;
}

Nand::~Nand() {
	delete [] inputs;
	delete output;
}

char Nand::eval() {
	char value;
	// if input size is one
	if(static_cast<int>(inputs->size()) == 1){
		if(inputs->front()->getVal() == 'X') {
			value = 'X';
		}
		else if(inputs->front()->getVal() == '0') {
			value = '1';
		}
		else if(inputs->front()->getVal() == '1') {
			value = '0';
		}
	}
	else{ // more than 1 input
		vector<Net *>::iterator ix = inputs->begin();
		value = (*ix)->getVal();
		ix++;
		while(ix != inputs->end()){
			if((*ix)->getVal() == 'X'){
				if(value == '1'){
					value = 'X';
				}
				else if(value == '0'){
					value = '1';
				}
			} // end if
			if((*ix)->getVal() == '0'){				
				value = '1';
			} // end if
			if((*ix)->getVal() == '1'){
				// value is unchanged if equal to 'X'
				if(value == '0'){
					value = '1';
				}
				else if(value == '1'){
					value = '0';
				}
			} // end if
			ix++;
		} // end while
	} // end else
	return value;
}
void Nand::dump(ostream &os){
	// display information onto the screen
	os << "nand" << " ";
	if(delay != 1 && delay != 0){
		os << "#" << delay << " ";	
	}
	os << inst_name << "(" << output->name() << ", ";
	vector<Net *>::iterator it;
	for(it = inputs->begin(); it != inputs->end(); it++){
		os << (*it)->name();
		if(it == inputs->end() - 1){
			os << ");";
			break;
		}
		else{
			os << ", ";
		}
	}
	os << endl;
}

/*************** Functions for XOR gate ****************/
Xor::Xor(string n, int d) : Gate(n, d) {
	inst_name = n;
	delay = d;
}

Xor::~Xor() {
	delete [] inputs;
	delete output;
}

char Xor::eval() {
	char value;
	// if input size is one
	if(static_cast<int>(inputs->size()) == 1){
		if(inputs->front()->getVal() == 'X') {
			value = 'X';
		}
		else if(inputs->front()->getVal() == '0') {
			value = '0';
		}
		else if(inputs->front()->getVal() == '1') {
			value = '1';
		}
	} // end if
	// if there are more than one input
	else {
		vector<Net *>::iterator ix = inputs->begin();
		value = (*ix)->getVal();
		ix++;
		while(ix != inputs->end()){
			// if (*ix)->getVal() == 'X', value is unchanged
			// if (*ix)->getVal() == '0', value is unchanged
			if((*ix)->getVal() == '1'){
				if(value == '0'){
					value = '1';
				}
				else if(value == '1'){
					value = '0';
				}
			} // end if
			ix++;
		} // end while
	} // end else
	return value;
}
void Xor::dump(ostream &os){
	// display information onto the screen
	os << "xor" << " ";
	if(delay != 1 && delay != 0){
		os << "#" << delay << " ";	
	}
	os << inst_name << "(" << output->name() << ", ";
	vector<Net *>::iterator it;
	for(it = inputs->begin(); it != inputs->end(); it++){
		os << (*it)->name();
		if(it == inputs->end() - 1){
			os << ");";
			break;
		}
		else{
			os << ", ";
		}
	}
	os << endl;
}

/*************** Functions for NOT gate ****************/
Not::Not(string n, int d) : Gate(n, d) {
	inst_name = n;
	delay = d;
}

Not::~Not() {
	delete [] inputs;
	delete output;
}

char Not::eval() {
	char value;
	// if input size is one
	if(static_cast<int>(inputs->size()) == 1){
		if(inputs->front()->getVal() == 'X') {
			value = 'X';
		}
		else if(inputs->front()->getVal() == '0') {
			value = '1';
		}
		else if(inputs->front()->getVal() == '1') {
			value = '0';
		}
	} // end if
	return value;
}
void Not::dump(ostream &os){
	// display information onto the screen
	os << "not" << " ";
	if(delay != 1 && delay != 0){
		os << "#" << delay << " ";	
	}
	os << inst_name << "(" << output->name() << ", ";
	vector<Net *>::iterator it;
	for(it = inputs->begin(); it != inputs->end(); it++){
		os << (*it)->name();
		if(it == inputs->end() - 1){
			os << ");";
			break;
		}
		else{
			os << ", ";
		}
	}
	os << endl;
}