#ifndef VLGPARSER_H
#define VLGPARSER_H

// forward declaration
class Design;

class VlgParser {					// parent class for VlgParser
public:
	virtual Design *parse(char *filename) = 0;
};

#endif
