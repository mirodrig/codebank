#ifndef SHAPES_H
#define SHAPES_H

#include <cmath>
#include <string>

class Shape{								// defines parent shape object
public:
	virtual ~Shape(){}
	virtual double getArea() = 0;			// all shapes have an area
	virtual double getPerimeter() = 0;		// all shapes have perimeter
	virtual std::string getType() = 0;		// all shapes have name
};

class RightTri : public Shape{				// defines child right triangle object
public:
	RightTri(double w, double h):_w(w), _h(h){}	// constr. w/ spec. width & height
	~RightTri(){}							// destructor
	double getArea(){						// computes area of right triangle
		return 0.5 * _w * _h;
	}
	double getPerimeter(){					// computes perimeter of right tri
		return std::sqrt(_w*_w + _h*_h) + _h + _w;
	}
	std::string getType(){					// returns the name of the shape
		return "Right Triangle";
	}
private:
	double _w, _h;							// private variables are base & height
};

class Rectangle : public Shape{				// defines child rectangle object
public:
	Rectangle(double w, double h):_w(w), _h(h){}	// constr. w/ base & height
	~Rectangle(){}
	double getArea(){
		return _w * _h;
	}
	double getPerimeter(){
		return 2*_w + 2*_h;
	}
	std::string getType(){
		return "Retcangle";
	}
private:
	double _w, _h;
};

class Square : public Shape{				// defines child square object
public:
	Square(double w):_w(w){}
	~Square(){}
	double getArea(){
		return _w * _w;
	}
	double getPerimeter(){
		return 4*_w;
	}
	std::string getType(){
		return "Square";
	}
private:
	double _w;
};

class Circle : public Shape{				// defines child circle object
public:
	Circle(double r):_r(r){}
	~Circle(){}
	double getArea(){
		return 3.14159*_r*_r;
	}
	double getPerimeter(){
		return 2*3.14159*_r;
	}
	std::string getType(){
		return "Circle";
	}
private:
	double _r;	
};


#endif