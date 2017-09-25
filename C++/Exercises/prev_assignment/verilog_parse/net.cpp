/****************************************************
* Marlin Rodriguez & Jonathan Rodriguez
* Programming Assignment 6
* net.cpp
****************************************************/
#include <vector>
#include <string>
#include "net.h"
#include "gates.h"

using namespace std;

Net::Net(string n) {
  netname = n;
  delay = 1;
  val = 'X';
  drivers = new vector<Gate *>;
  loads = new vector<Gate *>;
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
	char value;
	// when there is only one driver
	if(static_cast<int>(drivers->size()) == 1){
		value = drivers->front()->eval();
	}
	// when there are more than one driver
	else {
		// create an iterator for the drivers
		vector<Gate *>::iterator it = drivers->begin();
		value = (*it)->eval();
		it++;
		while(it != drivers->end()) {
			// case when (*it)->eval() == 'X'
			if((*it)->eval() == 'X'){
				value = 'X';
			} // end if
			if((*it)->eval() == '0'){
				if(value != '0'){
					value = 'X';
				}
			} // end if
			if((*it)->eval() == '1'){
				if(value != '1'){
					value = 'X';
				}
			} // end if
		} // end while
	} // end else
	return value;
}

/* Looks at the driver gates and input nets to those
*  gates to compute and return the time when this
*  net's value will be resolved */
// This function to be worked for part 2
/*int Net::computeDelay(){
	int resolved_time = 0; // delay to be computed
	return resolved_time;
} */

char Net::getVal() const { return val; }

void Net::setVal(char v) { val = v; }

int Net::getDelay() const { return delay; }

void Net::setDelay(int d) { delay = d; }

/* Debug function you can use to verify 
* your code. Prints the drivers and loads.*/
void Net::printDriversLoads() {

}