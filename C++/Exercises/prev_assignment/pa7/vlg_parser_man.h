/*********************************************
* Marlin Rodriguez & Jonathan Rodriguez
* vlg_parser_man.h
* PA7
*********************************************/
#ifndef VLGPARSERMAN_H
#define VLGPARSERMAN_H
#include "design.h"
#include "vlg_parser.h"

// this function inherits from vlg parser
// VlgParserMan only has access to the public member functions of VlgParser
class VlgParserMan : public VlgParser {
 public: // public member functions
  VlgParserMan();
  Design *parse(char *in_file);
 private: // private member functions
  vector<string> parse_port_list(stringstream &ss_stream, string &parsemsg, bool &parse_err);
};

#endif
