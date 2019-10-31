all : client

client : src/client.cc
	g++ -Wall -g -std=c++11 -o build/client src/client.cc

clean : 
	-rm *.o