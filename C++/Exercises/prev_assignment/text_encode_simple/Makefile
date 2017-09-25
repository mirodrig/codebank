# set compiler for g++
CXX = g++

# performs all of the make operations w/ one command
all: caesarlib.o crack.o main

clean:
	rm -f caesarlib.o crack.o

# create caesarlib object file
caesarlib.o: caesarlib.cpp
	$(CXX) -c caesarlib.cpp -o caesarlib.o

# create crack object file
crack.o: crack.cpp
	$(CXX) -c crack.cpp -o crack.o

# create executable from object files
main: main.cpp
	$(CXX) caesarlib.o crack.o main.cpp -o main

