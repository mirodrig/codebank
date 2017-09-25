/****************************************************
* Marlin Rodriguez & Jonathan Rodriguez
* Programming Assignment 6
* gsim.cpp
****************************************************/
#include <iostream>
#include <fstream>

#include "vlg_parser.h"
#ifdef AUTOPARSE
#include "vlg_parser_auto.h"
#else
#include "vlg_parser_man.h"
#endif

#include "design.h"
#include "gates.h"
#include "net.h"


using namespace std;

int main(int argc, char *argv[]){
  if(argc < 3){
    cerr << "Usage ./gsim infile.v outfile.v" << endl;
    return 1;
  }
  #ifdef AUTOPARSE
  VlgParser *parser = new VlgParserAuto();
  #else
  VlgParser *parser = new VlgParserMan();
  #endif
  Design *d = parser->parse(argv[1]); // based on input file (mux21.v)
  
  // Add more of your code here to simply dump the design back
  // out to a file named output.v 
  ofstream ofile(argv[2]);
  d->dump(ofile);
  ofile.close();
  delete parser;
  return 0;
}