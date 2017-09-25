#include <iostream>
#include <vector>
#include "shapes.h"

void printMsg();							// function prototype

int main(){
	std::vector<Shape*> list;				// initialize vector of shapes
	int sel = -1;
	printMsg();

	while(sel != 0){						// continue while prog not terminated
		std::cout << "> ";
		std::cin >> sel;

		if(sel == 1){						// adds a right tri w/ spec. param
			double w, h;
			std::cin >> w >> h;				// enter param. as std input
			list.push_back(new RightTri(w,h));
		}
		else if(sel == 2){					// adds a rectangle w/ spec. param
			double w, h;
			std::cin >> w >> h;
			list.push_back(new Rectangle(w,h));
		}
		else if(sel == 3){					// adds a square w/ spec. param
			double w;
			std::cin >> w;
			list.push_back(new Square(w));
		}
		else if(sel == 4){					// adds a circle w/ spec. param
			double r;
			std::cin >> r;
			list.push_back(new Circle(r));
		}
	}
	std::cout << "List is of size " << list.size() << "\n";

	// iterate through all elements of the vector (using iterators)
	for(std::vector<Shape*>::iterator it = list.begin();
		it != list.end(); ++it){

		Shape* s = *it;						// set var to current shape of vector
		std::cout << s->getType() << ": Area = " << s->getArea();
		std::cout << " Perimeter = " << s->getPerimeter() << "\n";
		delete s;
	}
	return 0;
}

// prints the operator prompt for user to modify shape objects
// parameter: nothing
// return: nothing
void printMsg(){
	std::cout << "Choose an option\n";
	std::cout << "========================\n";
	std::cout << "Enter '0' to terminate program\n";
	std::cout << "Enter '1 base height' for a right tri. w/ base & height\n";
	std::cout << "Enter '2 base height' for a rectangle w/ base & height\n";
	std::cout << "Enter '3 base' for a square w/ base\n";
	std::cout << "Enter '4 radius' for a circle w/ radius\n";
}