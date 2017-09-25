/****************************************************
* Marlin Rodriguez & Jonathan Rodriguez
* Programming Assignment 6
* net.h
****************************************************/
#ifndef NET_H
#define NET_H
#include <vector>
#include <string>
using namespace std;

class Gate;                        // forward declaration
class Net {                        // class for a net object
public:
  Net(string n);                   // constructor to initialize Net
  ~Net();                          // Destructor
  string name() const;             // returns name of the net
  void addDriver(Gate *g);         // adds given gate to list of drivers
  void addLoad(Gate *g);           // adds given gate for list of loads
  vector<Gate *> *getLoads();      // return dynamically alloc. list of load gates
  vector<Gate *> *getDrivers();    // return dynamically alloc. list of driver gates

   /* Looks at the driver gates and input nets to those gates to compute and return
   * the value on this net. @return Value produced on this net: '0','1','X' */
  char computeVal();

   /* Looks at the driver gates and input nets to those gates to compute and return
   * the time when this net's value will be resolved @return Time when this net's
   value is resolved */
   //int computeDelay();

  char getVal() const;              // accessor to val data member. Retur '0', '1', 'X'
  void setVal(char v);              // mutator for val data member. Sets val of net '0', '1', 'X'
  int getDelay() const;             // accessor to delay data member
  void setDelay(int d);             // mutator for delay data member. Param: value assigned to delay
  void printDriversLoads();         // prints drivers and loads. For debugging

 private:
  vector<Gate *> *drivers;          // gates that output to the net
  vector<Gate *> *loads;            // gates that the net outputs value to
  char val;                         // digital signal being carried
  string netname;                   // name of the net
  int delay;                        // delay time
};

#endif