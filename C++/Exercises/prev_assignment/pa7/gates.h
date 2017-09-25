/****************************************************
* Marlin Rodriguez & Jonathan Rodriguez
* gates.h
* PA7
****************************************************/
#ifndef GATE_H
#define GATE_H
#include <vector>
#include <string>
#include "net.h"

using namespace std;

class Net; // forward declaration

 /* Enumeration to indicate gate type
 *  AND=0, OR=1, etc. */
enum {AND, OR, NAND, NOR, XOR, NOT};

/* This class models a Gate object */
class Gate {
 public:
   // Constructor (default)
  Gate(string n);
   // Constructor (name and delay)
  Gate(string n, int d);
  // virtual Destructor
  virtual ~Gate() { }
   // Returns the name of this Gate
  string name() const;
   // Returns the delay of this gate
  int getDelay() const;
   /* Pure virtual function that should be 
   * overridden for specific gate types
   * Evaluates the value the gate will attempt
   *  to prdoduce based on the input net values
   * return Value the gate attempts to produce:
   *         '0','1','X' */
  virtual char eval() = 0;
   /* Pure virtual function that should be 
   * overridden for specific gate types
   * Evaluates the value the gate will attempt
   *  to prdoduce based on the input net values
   * @param[in] os ostream to dump the Verilog 
   *                description of this gate */  
  virtual void dump(ostream &os) = 0;
   // Adds an input net to this gate
  void addInput(Net *n);
   /* Returns a new dynamically allocated
   *          list of the input nets */
  vector<Net *> *getInputs();
   // Sets the output net of this gate
  void addOutput(Net *n);
   /* Returns the output Net of this gate
   * @return Pointer to the output net of this Gate */
  Net* getOutput() const;
   // Returns the number of inputs
  int getNumInputs() const;
 protected:
  vector<Net *> *inputs; // vector of net pointers
  Net *output; // output is a ptr to a net
  string inst_name; // each gate has a name
  int delay; // each gate has a amount of delay
};

// AND gate class
class And : public Gate {
 public:
  And(string n, int d);
  ~And();
  char eval();
  void dump(ostream &os);
};

// OR gate class
class Or : public Gate {
 public:
  Or(string n, int d);
  ~Or();
  char eval();
  void dump(ostream &os);
};
// NOR gate class
class Nor : public Gate {
 public:
  Nor(string n, int d);
  ~Nor();
  char eval();
  void dump(ostream &os);
};
// NAND gate class
class Nand : public Gate {
 public:
  Nand(string n, int d);
  ~Nand();
  char eval();
  void dump(ostream &os);
};
// XOR gate class
class Xor : public Gate {
 public:
  Xor(string n, int d);
  ~Xor();
  char eval();
  void dump(ostream &os);
};
// NOT gate class
class Not : public Gate {
 public:
  Not(string n, int d);
  ~Not();
  char eval();
  void dump(ostream &os);
};

#endif
