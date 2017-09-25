/****************************************************
* Marlin Rodriguez & Jonathan Rodriguez
* net.h
* PA7
****************************************************/
#ifndef NET_H
#define NET_H
#include <vector>
#include <string>
using namespace std;

/* Forward Declaration */
class Gate;

// numerations for color (topological sort)
enum {WHITE, GREY, BLACK};

/* This class models a net in the design */
class Net {
 public:
   // Constructor to initialize Net with given name
  Net(string n);
  // Destructor
  ~Net();
  // Returns the name of this Net
  string name() const;
   // Adds the given gate to the list of drivers 
  void addDriver(Gate *g);
   // Adds the given gate to the list of loads 
  void addLoad(Gate *g);
   /* Returns a new dynamically allocated
   *          list of the load gates */
  vector<Gate *> *getLoads();
   /* Returns a new dynamically allocated
   *          list of the driver gates */
  vector<Gate *> *getDrivers();
   /* Looks at the driver gates and input nets to those
   *  gates to compute and return the value on this net
   * @return Value produced on this net: '0','1','X' */
  char computeVal();
   /* Looks at the driver gates and input nets to those
   *  gates to compute and return the time when this
   *  net's value will be resolved
   * @return Time when this net's value is resolved */
  int computeDelay();
   /* Accessor to the val data member
   * @return Value of the net '0','1','X' */
  char getVal() const;
   /* Mutator for the val data member
   * @param[in] Sets the value of the net '0','1','X' */
  void setVal(char v);
   // Accessor to the delay data member
  int getDelay() const;
   /* Mutator for the delay data member
   * @param[in] Value to assign to the delay */
  void setDelay(int d);
   /* Debug function you can use to verify 
   * your code. Prints the drivers and loads.*/
  void printDriversLoads();
  int color; // color of the net (topological sort)

 private:
  vector<Gate *> *drivers; // gates "before" net
  vector<Gate *> *loads; // gates "after" net
  char val; // voltage being carried
  string netname; // name of the net
  int delay; // number of delay
};
#endif
