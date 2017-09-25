#include <iostream>
#include <map>
#include "student.h"

void printMsg();

int main(){
	int input;									// user input
	std::map<std::string, Student> stuList_; 	// map of student objects
	printMsg();
	std::cin >> input;

	while(input != 7){						// modify data while not terminated
		if(input == 1){						// add student to map (by name)
			std::cout << "First name: ";
			std::string name;
			std::cin >> name;				// initialize student object
			Student stu(name);				// append to student map
			stuList_.insert(std::pair<std::string, Student>(name, stu));
		}
		else if(input == 2){				// remove student from map
			std::cout << "First name: ";
			std::string name;
			std::cin >> name;

			// iterate through map to find specified key
			for(std::map<std::string, Student>::iterator it = stuList_.begin();
				it != stuList_.end(); ++it){
				if(stuList_.find(name) != stuList_.end()){	// key is found
					stuList_.erase(name);
					std::cout << name << " is removed\n";
				}
				else										// key not found
					std::cout << name << " cannot be found\n";
			}
		}
		else if(input == 3){				// add val of 0 to all keys
			for(std::map<std::string, Student>::iterator it = stuList_.begin();
				it != stuList_.end(); ++it){
				(it->second).addGrade(0);
			}
		}
		else if(input == 4){				// update val of specified key
			std::cout << "Enter student's name, index & new score: ";
			std::string name;				// initialize variables
			int index, score;
			std::cin >> name >> index >> score;	// stream as std input
			bool noName_ = false;

			// create an iterator based on .find()
			std::map<std::string, Student>::iterator it = stuList_.find(name);

			// iterate through all of the keys in the map
			for(std::map<std::string, Student>::iterator ix = stuList_.begin();
				ix != stuList_.end(); ++ix){
				// case if the specified name does not exist in the map
				if(stuList_.find(name) == stuList_.end()){
					noName_ = true;
					std::cout << "name cannot be found.\n";
					break;
				}
				// case if the name exists in the map
				if(noName_ == false){
					if((it->first) == name){
						// case if the student object has no scores
						if(index > int(((it->second).getGrade()).size()) - 1){
							(it->second).addGrade(score);
							std::cout << "score is added\n";
							break;
						}
						// case if student object has scores associated with it
						else{
							(it->second).updateGrade(index, score);
							std::cout << name << "'s score is updated\n";
						}
					}
					else
						std::cout << "name cannot be found\n";
				}
			}
		}
		else if(input == 5){			// compute avg score for given student
			std::cout << "Enter index of scores to get average: ";
			int index;
			std::cin >> index;
			double gradeSum = 0;		// sum of scores for computing avg

			// iterate through all of the keys of the map
			for(std::map<std::string, Student>::iterator it = stuList_.begin();
				it != stuList_.end(); ++it){

				// determine if index doesn't pass dimensions of the vector
				if(index > int(((it->second).getGrade()).size()) - 1){
					std::cout << "index passes the dimensions of the vector\n";
					break;
				}
				gradeSum += (it->second).getGrade(index);
			}
			std::cout<<"average is "<<double(gradeSum/stuList_.size()) << "\n";
		}
		else if(input == 6){			// prints student's names and scores
			// iterate through the keys of the map
			for(std::map<std::string, Student>::iterator it = stuList_.begin();
				it != stuList_.end(); ++it){

				std::cout << (it->first) << ": ";
				// iterate through the score vector associated w/ each student
				for(std::vector<int>::iterator ix = ((it->second).getGrade()).begin();
					ix != ((it->second).getGrade()).end(); ++ix){

					std::cout << *ix << "\n";
				}
			}
		}
		std::cout << "Select an option: ";
		std::cin >> input;
	}
	std::cout << "Goodbye\n";
	return 0;
}

// prints the operator prompts for creating student data
// parameters: nothing
// return: nothing
void printMsg(){
	std::cout << "Select one of the following options.\n";
	std::cout << "1 = add a new student\n";
	std::cout << "2 = remove a student (by name)\n";
	std::cout << "3 = add a score of 0 to all students\n";
	std::cout << "4 = update score for (i) student\n";
	std::cout << "5 = calculate the average score @ index i\n";
	std::cout << "6 = prints all students' names & scores\n";
	std::cout << "7 = terminate program\n";
}