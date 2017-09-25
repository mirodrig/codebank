/****************************************************
* Marlin Rodriguez & Jonathan Rodriguez
* Programming Assignment 6
* design.h
****************************************************/
#ifndef DESIGN_H
#define DESIGN_H
#include <iostream>
#include <ostream>
#include <vector>
#include <map>
#include <string>
#include "gates.h"
#include "net.h"

using namespace std;

class Design {
public:
  Design(string n);                   // constructor
  ~Design() {                         // destructor
    for (map<string, Net*>::iterator ix = designNets.begin();
      ix != designNets.end(); ++ix) {
      delete (ix->second);
    }
    for (map<string, Gate*>::iterator iy = designGates.begin();
      iy != designGates.end(); ++iy) {
      delete (iy->second);
    }
  }
  string name();                      // returns the name of design
  void addPI(string n);               // adds primary input to internal database
  void addPO(string n);               // adds primary output to database

  /* Returns a pointer to the net with the given name or NULL if that net
  doesn't exist return Pointer to a Net object or NULL */
  Net *findNet(string net_name);

  /* Returns a pointer to the gate with the given name or NULL if that gate
  doesn't exist return Pointer to a Gate object or NULL */
  Gate *findGate(string inst_name);

  /* Checks if a Net with the given name exists already, returning a pointer to
  it if it does.  It not, it creates a new Net object and returns a pointer to
  that new object
   * @param[in] n Name of the gate to find/create
   * @return Pointer to the Net object */
  Net* addFindNet(string n);

  /**
   * Checks if a gate with the given instance name
   *   exists already, returning a pointer to it if
   *   it does.  It not, it creates a new Gate object
   *   of the given type and name and returns a pointer
   *   to that new object
   * 
   * @param[in] gtype Integer/Enumeration value of the
   *                  type of gate to create
   * @param[in] g Instance name of the gate to find/create
   * @return Pointer to the Gate object
   */
  Gate* addFindGate(int gtype, string g);

  /**
   * Same as addFindGate above but if a gate is created
   *   the delay value provided will be used
   * 
   * @param[in] gtype Integer/Enumeration value of the
   *                  type of gate to create
   * @param[in] g Instance name of the gate to find/create
   * @param[in] d Delay value
   * @return Pointer to a Gate object
   */
  Gate* addFindGate(int gtype, string g, int d);

  /**
   * Dynamically allocates a new vector and adds
   * pointers to all Nets that correspond to primary
   * inputs into the vector and then returns a pointer to 
   * the vector
   *
   * @return Pointer to a new vector storing Net pointers
   */
  vector<Net *> getPINets();

  /**
   * Dynamically allocates a new vector and adds
   * pointers to all Nets that correspond to primary
   * outputs into the vector and then returns a pointer to 
   * the vector
   *
   * @return Pointer to a new vector storing Net pointers
   */
  vector<Net *> getPONets();

  /**
   * Dynamically allocates a new vector and adds
   * pointers to all Nets that correspond to internal 
   * wires into the vector and then returns a pointer to 
   * the vector
   *
   * @return Pointer to a new vector storing Net pointers
   */
  vector<Net *> getWireNets();

  /**
   * Dynamically allocates a new vector and adds
   * pointers to all Nets (PI, PO, internal wire) 
   * into the vector and then returns a pointer to 
   * the vector
   *
   * @return Pointer to a new vector storing Net pointers
   */
  vector<Net *> allNets();

  /**
   * Dynamically allocates a new vector and adds
   * pointers to all Gates into the vector and then 
   * returns a pointer to the vector
   *
   * @return Pointer to a new vector storing Gate pointers
   */
  vector<Gate *> allGates();

  /**
   * To be implemented in Part 2.  For Part 1 just return NULL
   * 
   * Performs a topological sorting of the nets in the design
   *  and returns a dynamically allocated vector with pointers
   *  to Net objects in a satisfactory topological order
   *
   * @return Pointer to a new vector storing Net pointers
   */
  //vector<Net *> toposort();

  /**
   * Recreates the Verilog description of the design dumping
   * it to the provided ostream
   *
   * @param[in] os Ostream representing a file, stdout, or stringstream
   *               to which the Verilog description should be output
   */
  void dump(ostream &os);

  /**
   * Checks if the given Net object represents a primary input
   * 
   * @param[in] n Pointer to the Net 
   * @return true if the Net is a primary input, false otherwise
   */
  bool isPI(Net *n);


  /**
   * Checks if the given Net object represents a primary output
   * 
   * @param[in] n Pointer to the Net 
   * @return true if the Net is a primary output, false otherwise
   */
  bool isPO(Net *n);
 private:

  /**
   * To be implemented in Part 2.  For Part 1 just return 
   *
   * Recursive helper function to perform the depth-first search
   * of nets
   * 
   * @param[in] n Pointer to the current Net on which the DFS is visiting 
   * @param[out] flist Stores the Nets as they are finished...this is the
   *                   ordering after the topological sort finishes
   * @param[inout] colormap Maps the net name to its visited color 
   */
  void dfs_visit(Net *n, vector<Net *> *flist, map<string, int> &colormap)
  {
  	return;
  }

 private:
  /* Data members */
  string desname;
  map<string, Net *> designNets;
  map<string, Gate *> designGates;
  vector<string> pis;
  vector<string> pos;

};

#endif
