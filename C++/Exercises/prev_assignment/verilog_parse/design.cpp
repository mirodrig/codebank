/****************************************************
* Marlin Rodriguez & Jonathan Rodriguez
* Programming Assignment 6
* design.cpp
****************************************************/
#include "design.h"
#include <set>
#include <iostream>
#include <vector>

using namespace std;

Design::Design(string n) {
	desname = n;
}

string Design::name() {
	return desname;
}

void Design::addPI(string n) {
	pis.push_back(n);
}

void Design::addPO(string n) {
	pos.push_back(n);
}

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
	for (ix == designNets.begin(); ix != designNets.end(); ix++) {
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
/*
vector<Net *> Design::toposort() {
	return NULL;
} */

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