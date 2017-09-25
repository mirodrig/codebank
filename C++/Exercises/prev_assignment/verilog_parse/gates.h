/****************************************************
* Marlin Rodriguez & Jonathan Rodriguez
* Programming Assignment 6
* gates.h
****************************************************/
#ifndef GATE_H
#define GATE_H
#include <vector>
#include <string>
#include "net.h"

using namespace std;

class Net;                           // forward declaration
 /* Enumeration to indicate gate type: AND=0, OR=1, etc. */
enum {AND, OR, NAND, NOR, XOR, NOT};

class Gate {                         // class for gate object
public:
  Gate(string n);                    // default constructor
  Gate(string n, int d);             // constructor w/ name and delay
  virtual ~Gate() { }                // destructor: applies to all gates
  string name() const;               // returns the name of the gate
  int getDelay() const;              // returns the delay of the gate

  /* Pure virtual function that should be overridden for specific gate types
  * Evaluates the value the gate will attempt to prdoduce based on the input
  net values. @return Value the gate attempts to produce: '0','1','X' */
  virtual char eval() = 0;           // to be evaluated in specific gates

   /* Pure virtual function that should be overridden for specific gate types
   * Evaluates the value the gate will attempt to prdoduce based on the input
   net values @param[in] os ostream to dump the Verilog description of this gate */  
  virtual void dump(ostream &os) = 0;
  void addInput(Net *n);             // adds input net to the current gate
  vector<Net *> *getInputs();        // return dynamically alloc. list of input nets
  void addOutput(Net *n);            // sets the output net of the gate

   /* Returns the output Net of this gate @return Pointer to the output net of this Gate */
  Net* getOutput() const;
  int getNumInputs() const;          // return the number of inputs

protected:
  vector<Net *> *inputs;             // vector of net pointers
  Net *output;                       // output is a ptr to a net
  string inst_name;                  // each gate has a name
  int delay;                         // each gate has a amount of delay
};

class And : public Gate {            // AND gate class
 public:
  And(string n, int d);
  ~And();
  char eval();
  void dump(ostream &os);
};

class Or : public Gate {             // OR gate class
 public:
  Or(string n, int d);
  ~Or();
  char eval();
  void dump(ostream &os);
};

class Nor : public Gate {            // NOR gate class
 public:
  Nor(string n, int d);
  ~Nor();
  char eval();
  void dump(ostream &os);
};

class Nand : public Gate {           // NAND gate class
 public:
  Nand(string n, int d);
  ~Nand();
  char eval();
  void dump(ostream &os);
};

class Xor : public Gate {            // XOR gate class
 public:
  Xor(string n, int d);
  ~Xor();
  char eval();
  void dump(ostream &os);
};

class Not : public Gate {            // NOT gate class
 public:
  Not(string n, int d);
  ~Not();
  char eval();
  void dump(ostream &os);
};

#endif
