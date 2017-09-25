/****************************************************
* Marlin Rodriguez & Jonathan Rodriguez
* gsim.cpp
* PA7
****************************************************/
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>

#include "vlg_parser.h"
#ifdef AUTOPARSE
#include "vlg_parser_auto.h"
#else
#include "vlg_parser_man.h"
#endif

#include "logicsim.h"
#include "design.h"
#include "gates.h"
#include "net.h"


using namespace std;

int main(int argc, char *argv[]){
  if(argc < 4){
    cerr << "Usage ./gsim infile.v insim.sim output.v" << endl;
    return 1;
  }
  
  #ifdef AUTOPARSE
    VlgParser *parser = new VlgParserAuto();
  #else
    VlgParser *parser = new VlgParserMan();
  #endif

  string imfile(argv[1]); // input file
  string simfile(argv[2]); // simulation file
  string outfile(argv[3]); // output file

  Design *d;
  try {
    d = parser->parse(argv[1]);
    vector<Net *> ordered_nodes = d->toposort();
    LogicSim sim(simfile, d);
    sim.run_simulation(ordered_nodes);
    sim.file_dump(outfile, d);
  } // end try
  catch(runtime_error &error) {
    stringstream ss;
    ss << "Reason: " << error.what();
    cerr << ss.str() << endl;
    return 1;
  }


  //Design *d = parser->parse(argv[1]);
  //ofstream ofile(argv[3]);
  //d->dump(ofile);
  //ofile.close();
  // delete d;
  delete parser;
  return 0;
}