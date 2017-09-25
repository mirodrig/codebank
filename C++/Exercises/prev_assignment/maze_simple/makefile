# set compiler for g++
CXX = g++

# builds main executable file
all: queue.o mazeio.o main

# builds the queue object file
queue.o: queue.cpp
	$(CXX) -c queue.cpp -o queue.o

# builds the mazeio object file
mazeio.o: mazeio.cpp
	$(CXX) -c mazeio.cpp -o mazeio.o

# builds the main executable
main: main.cpp
	$(CXX) queue.o mazeio.o main.cpp -o main
	rm -f queue.o mazeio.o