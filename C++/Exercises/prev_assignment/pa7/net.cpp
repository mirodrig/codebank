/****************************************************
* Marlin Rodriguez & Jonathan Rodriguez
* net.cpp
* PA7
****************************************************/
#include <vector>
#include <string>
#include "net.h"
#include "gates.h"
#include <iostream>
#include <algorithm>

using namespace std;

Net::Net(string n) {
  netname = n;
  delay = 1;
  val = 'X';
  drivers = new vector<Gate *>;
  loads = new vector<Gate *>;
  color = WHITE;
}

Net::~Net() {
  delete [] drivers;
  delete [] loads;
} // end Destructor

string Net::name() const{ return netname; }

void Net::addDriver(Gate *g) { drivers->push_back(g); }

void Net::addLoad(Gate *g) { loads->push_back(g); }

vector<Gate *> * Net::getLoads() { return loads; }

vector<Gate *> * Net::getDrivers() { return drivers; }

/* Looks at the driver gates and input nets to those
   *  gates to compute and return the value on this net
   * @return Value produced on this net: '0','1','X' */
char Net::computeVal(){
	char _value;
	// if there is only one driver for the net
	if(int(drivers->size()) == 1){
		_value = drivers->front()->eval();
	}
	// if there are more than one driver
	else {
		vector<char> temp_values; // stores temporary values evaluated
		char temp; // temporary variable
		vector<Gate *>::iterator it;
		for(it = drivers->begin(); it != drivers->end(); it++){
			// fill the temp vector with dummy values
			temp_values.push_back((*it)->eval());
		} // end for
		temp = temp_values[0]; // set temp equal to the first input pin
		// iterate through the vector to determine if there's bus contention
		vector<char>::iterator mt;
		for(mt = temp_values.begin(); mt != temp_values.end(); mt++){
			if(*mt == temp){
				_value = temp;
			} // end if
			else{
				_value = 'X';
			} // end else
		} // end for
	} // end else
		// vector<Gate *>::iterator it = drivers->begin();
		// _value = (*it)->eval(); // current driver
		// it++; // we can now go ahead to the next driver
		// while not all of the drivers have been tested
		// while(it != drivers->end()){
			// if there is bus contention, output is X
			// if((*it)->eval() != _value){
				// _value = 'X';
			// }
			// it++; // increment to next input
		// } // end while
	// } // end else
	return _value;
}

/* Looks at the driver gates and input nets to those
*  gates to compute and return the time when this
*  net's value will be resolved */
// This function to be worked for part 2
int Net::computeDelay(){
	if(drivers->size() == 0){
		return 0;
	}
	int net_delay = 0; // delay value to be returned
	vector<Gate *>::iterator it;
	for(it = drivers->begin(); it != drivers->end(); it++){
		Gate *curr_gate = *it;
		int temp_delay = 0;
		vector<Net *>::iterator jt;
		for(jt = curr_gate->getInputs()->begin();
			jt != curr_gate->getInputs()->end(); jt++){
			temp_delay = max(temp_delay, (*jt)->computeDelay());
		}
		net_delay = max(net_delay, temp_delay + curr_gate->getDelay());
	}
	return net_delay;
}

char Net::getVal() const { return val; }

void Net::setVal(char v) { val = v; }

int Net::getDelay() const { return delay; }

void Net::setDelay(int d) { delay = d; }

/* Debug function you can use to verify 
* your code. Prints the drivers and loads.*/
void Net::printDriversLoads() {
	cout << "Drivers: ";
	vector<Gate *>::iterator it;
	for(it = drivers->begin(); it != drivers->end(); it++){
		cout << (*it)->name() << " ";
	}
	cout << endl;
	cout << "Loads: ";
	for(it = loads->begin(); it != loads->end(); it++){
		cout << (*it)->name() << " ";
	}
	cout << endl;
}