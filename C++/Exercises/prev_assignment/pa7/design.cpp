/****************************************************
* Marlin Rodriguez & Jonathan Rodriguez
* design.cpp
* PA7
****************************************************/
#include "design.h"
#include <set>
#include <iostream>
#include <vector>

using namespace std;

Design::Design(string n) { desname = n; }

string Design::name() { return desname; }

void Design::addPI(string n) { pis.push_back(n); }

void Design::addPO(string n) { pos.push_back(n); }

Net* Design::findNet(string net_name) {
	map<string, Net*>::iterator ix = designNets.find(net_name);
	if (ix == designNets.end()) {
		cout << "Net not found" << endl;
		(ix->second) = NULL;
		return (ix->second);
	}
	else { // net found
		return (ix->second);
	}
}

Gate* Design::findGate(string inst_name) {
	map<string, Gate*>::iterator ix = designGates.find(inst_name);
	if (ix == designGates.end()) {
		cout << "Gate not found" << endl;
		(ix->second) = NULL;
		return (ix->second);
	}
	else {
		return (ix->second);
	}
}

Net* Design::addFindNet(string n) {
	map<string, Net*>::iterator ix = designNets.find(n);
	if (ix != designNets.end()) { // already exists
		return (ix->second);
	}
	else { // create new net instance
		Net *netNew = new Net(n);
		designNets[n] = netNew;
		return netNew;
	}
}

Gate* Design::addFindGate(int gtype, string g) {
	map<string, Gate*>::iterator ix = designGates.find(g);
	if (ix != designGates.end()) { // net already exists
		return (ix->second);
	} 
	else {
		if (gtype == 0) { // gtype == AND
			And *gateNew = new And(g, 0);
			designGates[g] = gateNew;
			return gateNew;
		}
		else if (gtype == 1) { // gtype == OR
			Or *gateNew = new Or(g, 0);
			designGates[g] = gateNew;
			return gateNew;
		}
		else if (gtype == 2) { // gtype == NAND
			Nand *gateNew = new Nand(g, 0);
			designGates[g] = gateNew;
			return gateNew;
		}
		else if (gtype == 3) { // gtype == NOR
			Nor *gateNew = new Nor(g, 0);
			designGates[g] = gateNew;
			return gateNew;
		}
		else if (gtype == 4) { // gtype == XOR
			Xor *gateNew = new Xor(g, 0);
			designGates[g] = gateNew;
			return gateNew;
		}
		else if (gtype == 5) { // gtype == NOT
			Not *gateNew = new Not(g, 0);
			designGates[g] = gateNew;
			return gateNew;
		}
		else {
			cout << "Invalid gate type" << endl;
			return NULL;
		}
	} 
}

Gate* Design::addFindGate(int gtype, string g, int d) {
	map<string, Gate*>::iterator ix = designGates.find(g);
	if (ix != designGates.end()) { // net already exists
		return (ix->second);
	}
	else {
		if (gtype == 0) { // gtype == AND
			And *gateNew = new And(g, d);
			designGates[g] = gateNew;
			return gateNew;
		}
		else if (gtype == 1) { // gtype == OR
			Or *gateNew = new Or(g, d);
			designGates[g] = gateNew;
			return gateNew;
		}
		else if (gtype == 2) { // gtype == NAND
			Nand *gateNew = new Nand(g, d);
			designGates[g] = gateNew;
			return gateNew;
		}
		else if (gtype == 3) { // gtype == NOR
			Nor *gateNew = new Nor(g, d);
			designGates[g] = gateNew;
			return gateNew;
		}
		else if (gtype == 4) { // gtype == XOR
			Xor *gateNew = new Xor(g, d);
			designGates[g] = gateNew;
			return gateNew;
		}
		else if (gtype == 5) { // gtype == NOT
			Not *gateNew = new Not(g, d);
			designGates[g] = gateNew;
			return gateNew;
		}
		else {
			cout << "Invalid gate type" << endl;
			return NULL;
		}
	}
}

vector<Net *> Design::getPINets() {
	vector<string>::iterator netName;
	map<string, Net*>::iterator netFind;
	vector<Net*> pisNew;
	for (netName = pis.begin(); netName != pis.end(); netName++) {
		netFind = designNets.find(*netName);
		if (netFind != designNets.end()) { // PI found
			pisNew.push_back(netFind->second);
		}
		else {
		}
	}
	return pisNew;
}

vector<Net *> Design::getPONets() {
	vector<string>::iterator netName;
	map<string, Net*>::iterator netFind;
	vector<Net*> posNew; 
	for (netName = pos.begin(); netName != pos.end(); netName++) {
		netFind = designNets.find(*netName);
		if (netFind != designNets.end()) { // PO found
			posNew.push_back(netFind->second);
		}
		else {
		}
	}
	return posNew;
}

vector<Net *> Design::getWireNets() {
	set<string> PIO; // set of inputs/ outputs
	// made for results being more readily available
	vector<string>::iterator ix;
	for (ix = pos.begin(); ix != pos.end(); ix++) {
		PIO.insert(*ix); // insert outputs
	}
	vector<string>::iterator ip;
	for (ip = pis.begin(); ip != pis.end(); ip++) {
		PIO.insert(*ip); // insert inputs
	}

	vector<Net*> wire;
	map<string, Net*>::iterator iy;
	for (iy = designNets.begin(); iy != designNets.end(); iy++) {
		// if neither input nor output
		if (PIO.find(iy->second->name()) == PIO.end()) {
			wire.push_back(iy->second);
		}
		else {
			cout << "Skipping " << iy->second->name();
		}
	}
	return wire;
}

vector<Net *> Design::allNets() {
	map<string, Net*>::iterator ix;
	vector<Net*> allNets;
	for (ix = designNets.begin(); ix != designNets.end(); ix++) {
		allNets.push_back(ix->second);
	}
	return allNets;
}

vector<Gate *> Design::allGates() {
	map<string, Gate*>::iterator ix;
	vector<Gate*> allGates;
	for (ix = designGates.begin(); ix != designGates.end(); ix++) {
		allGates.push_back(ix->second);
	}
	return allGates;
}

  /**
   * Performs a topological sorting of the nets in the design
   *  and returns a dynamically allocated vector with pointers
   *  to Net objects in a satisfactory topological order
   *
   * @return Pointer to a new vector storing Net pointers
   */

// returns a dynamically allocated vector storing Net pointers
vector<Net *> Design::toposort() {
	// for toposort, I am not including the output value

	// enum {WHITE, GREY, BLACk} => 0, 1, 2
	sortedNodes = vector<Net *>(); // dynamically allocate a vector
	vector<Net *> pin_node = getPONets(); // call primary outputs

	// create an iterator to iterate through primary outputs
	vector<Net *>::iterator it;
	for(it = pin_node.begin(); it != pin_node.end(); it++){
		// cout << (*it)->name() << endl;

		// if the node is WHITE, then perform the DFS search
		if((*it)->color == WHITE){
			(*it)->color = GREY; // make the color grey after initializing the DFS
			colorMap[(*it)->name()] = WHITE; // sets the current node to WHITE			
			(*this).dfs_visit(*it, &sortedNodes, colorMap);	
		}
		sortedNodes.push_back(*it); // must include the outermost output node
	}

	// there is something not correct about the DFS search algorithm...
	
	/*for(vector<Net* >::iterator nt = sortedNodes.begin(); nt != sortedNodes.end(); nt++){
		cout << (*nt)->name() << ", ";
	}
	cout << endl; */
	
	// return dynamically allocated vector storing pointers to Net objects
	return sortedNodes;
}

  /* Recursive helper function to perform the depth-first search of nets
   * @param[in] n Pointer to the current Net on which the DFS is visiting 
   * @param[out] flist Stores the Nets as they are finished...this is the
   *                   ordering after the topological sort finishes
   * @param[inout] colormap Maps the net name to its visited color  */
void Design::dfs_visit(Net *n, vector<Net *> *flist, map<string, int> &colormap){
	colormap[n->name()] = GREY; // change the node from WHITE to GREY
	// iterate through the drivers of the current node
	
	vector<Gate *>::iterator kt;
	for(kt = n->getDrivers()->begin(); kt != n->getDrivers()->end(); kt++){
		// display the names of each of the gates being checked
		
		// iterate through the input nets for the driver gates
		vector<Net *>::iterator lt;

		for(lt = (*kt)->getInputs()->begin(); lt != (*kt)->getInputs()->end(); lt++){
			// if the current node is white, then perform the iteration again
			if((*lt)->color == WHITE){
				(*this).dfs_visit(*lt, flist, colormap);
			}
			
			// cout << (*lt)->name() << endl;
			(*lt)->color = BLACK; // if the node is not WHITE, make it BLACK
			colormap[(*lt)->name()] = BLACK;
			// append the finished node to the sorted node vector
			flist->push_back((*lt));
		}
	}
}

void Design::dump(ostream &os) {
	os << "module " << this->name() << "(";
	vector<Net*> piNet = this->getPINets();
	for (vector<Net*>::iterator ix = piNet.begin(); 
		ix != piNet.end(); ix++) {
		os << (*ix)->name() << ", ";
	}
	vector<Net*> poNet = this->getPONets();
	for (vector<Net*>::iterator ix = poNet.begin(); 
		ix != poNet.end(); ix++) {
		os << (*ix)->name();
		if (ix + 1 != poNet.end()) {
			os << ", ";
		}
	}
	os << ");" << endl;

	for (vector<Net*>::iterator ix = piNet.begin(); 
		ix != piNet.end(); ix++) {
		os << "   input " << (*ix)->name() << ";" << endl;
	}
	for (vector<Net*>::iterator ix = poNet.begin(); 
		ix != poNet.end(); ix++) {
		os << "   output " << (*ix)->name() << ";" << endl;
	}
	vector<Net*> wireNet = this->getWireNets();
	for (vector<Net*>::iterator ix = wireNet.begin(); 
		ix != wireNet.end(); ix++) {
		os << "   wire   " << (*ix)->name() << ";" << endl;
	}
	os << endl;

	vector<Gate*> allGates = this->allGates();
	for (vector<Gate*>::iterator ix = allGates.begin(); 
		ix != allGates.end(); ix++) {
		os << "   ";
		(*ix)->dump(os);
	}
	os << "endmodule" << endl;
}

bool Design::isPI(Net *n) {
	return true;
}

bool Design::isPO(Net *n) {
	return true;
}