#ifndef STUDENT_H
#define STUDENT_H

#include <vector>
#include <string>

class Student{						// object for each individual student
public:
	Student(){}						// default constructor
	Student(std::string name){		// constructor with init str value
		name_ = name;
	}
	std::string getName(){			// returns string value for data storage
		return name_;
	}
	void addGrade(int score){		// appends int value to vector
		grades_.push_back(score);
	}
	void updateGrade(int index, int score){
		grades_[index] = score;		// updates element in vector
	}
	int getGrade(int index){		// returns specified element
		return grades_[index];
	}
	std::vector<int> &getGrade(){	// returns data array structure
		return grades_;
	}
private:
	std::string name_;				// string key - name of the Student
	std::vector<int> grades_;		// vector storing grades for each Student
};

#endif