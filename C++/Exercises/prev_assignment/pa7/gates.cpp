/****************************************************
* Marlin Rodriguez & Jonathan Rodriguez
* gates.cpp
* PA7
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
	output = new Net(n); // dynamically allocates a net
}

Gate::Gate(string n, int d) {
	inst_name = n;
	delay = d;
	inputs = new vector<Net *>();
	output = new Net(n); // dynamically allocates a net
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

void Gate::addInput(Net* n) { inputs->push_back(n); }

vector<Net *>* Gate::getInputs() { return inputs; }

void Gate::addOutput(Net *n) { output = n; }

Net* Gate::getOutput() const { return output; }

int Gate::getNumInputs() const {
	return static_cast<int>(inputs->size());
}

/*********** Functions for the AND gate ***************/
And::And(string n, int d) : Gate(n, d) { }

// deallocates dynamically created memory
And::~And() {
	delete [] inputs;
	delete output;
}

char And::eval() {
	char _value;
	// if there is only one valid input
	if(static_cast<int>(inputs->size()) == 1) {
		if(inputs->front()->getVal() == '0') {
			_value = '0';
		}
		else{
			_value = 'X';
		}
	} // end if
	else {
		vector<Net *>::iterator ix = inputs->begin();
		_value = (*ix)->getVal();
		ix++;
		while(ix != inputs->end()){
			// if the "second" input is 'X'
			// if 2nd value is 1, then value will not change
			if((*ix)->getVal() == 'X'){
				if(_value != '0'){
					_value = 'X';
				}
			}
			else if((*ix)->getVal() == '0'){
				_value = '0';
			}
			ix++; // increment the iterator
		} // end while
	} // end else
	return _value;
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
Or::Or(string n, int d) : Gate(n, d) { }

Or::~Or() {
	delete [] inputs;
	delete output;
}

char Or::eval() {
	char _value;
	// if input size is one
	if(static_cast<int>(inputs->size()) == 1){
		_value = inputs->front()->getVal();
		if(inputs->front()->getVal() == '1') {
			_value = '1';
		}
		else{
			_value = 'X';
		}
	} // end if
	else{
		vector<Net *>::iterator ix = inputs->begin();
		_value = (*ix)->getVal();
		ix++;
		while(ix != inputs->end()){
			if((*ix)->getVal() == 'X'){
				if(_value != '1'){
					_value = 'X';
				}
			}
			else if((*ix)->getVal() == '1'){
				_value = '1';
			}
			ix++;
		} // end while
	} // end else
	return _value;
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
Nor::Nor(string n, int d) : Gate(n, d) { }

Nor::~Nor() {
	delete [] inputs;
	delete output;
}

char Nor::eval() {
	char _value;
	// if input size is one
	if(static_cast<int>(inputs->size()) == 1){
		if(inputs->front()->getVal() == '1'){
			_value = '0';
		}
		else{
			_value = 'X';
		}
	}
	else{ // more than 1 input
		vector<Net *>::iterator ix = inputs->begin();
		_value = (*ix)->getVal();
		ix++;
		while(ix != inputs->end()){
			if((*ix)->getVal() == 'X'){
				if(_value == '1'){
					_value = '0';
				}
				else{
					_value = 'X';
				}
			} // end if
			else if((*ix)->getVal() == '0'){			
				if(_value == '0'){
					_value = '1';
				}
				else if(_value == '1'){
					_value = '0';
				}
			} // end if
			else if((*ix)->getVal() == '1'){
				_value = '0';
			} // end if
			ix++;
		} // end while
	} // end else
	return _value;
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
Nand::Nand(string n, int d) : Gate(n, d) { }

Nand::~Nand() {
	delete [] inputs;
	delete output;
}

char Nand::eval() {
	char _value;
	// if input size is one
	if(static_cast<int>(inputs->size()) == 1){
		if(inputs->front()->getVal() == '0') {
			_value = '1';
		}
		else{
			_value = 'X';
		}
	} // end if
	else{ // more than 1 input
		vector<Net *>::iterator ix = inputs->begin();
		_value = (*ix)->getVal();
		ix++;
		while(ix != inputs->end()){
			if((*ix)->getVal() == 'X'){
				if(_value == '0'){
					_value = '1';
				}
				else{
					_value = 'X';
				}
			} // end if
			else if((*ix)->getVal() == '0'){				
				_value = '1';
			} // end if
			else if((*ix)->getVal() == '1'){
				if(_value == '0'){
					_value = '1';
				}
				else if(_value == '1'){
					_value = '0';
				}
			} // end if
			ix++;
		} // end while
	} // end else
	return _value;
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
Xor::Xor(string n, int d) : Gate(n, d) { }

Xor::~Xor() {
	delete [] inputs;
	delete output;
}

char Xor::eval() {
	char _value;
	if(static_cast<int>(inputs->size()) == 1){
		_value = 'X';
	} // end if
	else {
		vector<Net *>::iterator ix = inputs->begin();
		_value = (*ix)->getVal();
		ix++;
		while(ix != inputs->end()){
			if((*ix)->getVal() == 'X'){
				_value = 'X';
			}
			else if((*ix)->getVal() == '1'){
				if(_value == '0'){
					_value = '1';
				}
				else if(_value == '1'){
					_value = '0';
				}
			} // end if
			ix++;
		} // end while
	} // end else
	return _value;
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
Not::Not(string n, int d) : Gate(n, d) { }

Not::~Not() {
	delete [] inputs;
	delete output;
}

char Not::eval() {
	char _value;
	if(static_cast<int>(inputs->size()) == 1){
		_value = 'X';
	} // end if
	else {
		vector<Net *>::iterator ix = inputs->begin();
		_value = (*ix)->getVal();
		ix++;
		while(ix != inputs->end()){
			if((*ix)->getVal() == 'X'){
				_value = 'X';
			} // end if
			else if((*ix)->getVal() == '0'){
				if(_value == '0'){
					_value = '1';
				}
			} // end if
			else if((*ix)->getVal() == '1'){
				if(_value == '1'){
					_value = '0';
				}
			} // end if
			ix++;
		} // end while
	} // end else
	return _value;
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