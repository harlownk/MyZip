all : ./build/client

./build/client : src/client.cc src/client.h ./build
	g++ -Wall -g -std=c++11 -o ./build/client src/client.cc

./build : 
	mkdir $@

clean : 
	@rm -fr ./build
