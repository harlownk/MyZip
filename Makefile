all : ./build/client

./build/client.o : src/client.cc src/client.h | ./build
	g++ -Wall -g -std=c++11 -o $@ -c src/client.cc

./build/ByteInventory.o : src/ByteInventory.cc src/ByteInventory.h | ./build
	g++ -Wall -g -std=c++11 -o $@ -c src/ByteInventory.cc

./build/client : ./build/ByteInventory.o ./build/client.o | ./build
	g++ -Wall -g -std=c++11 -o $@ ./build/ByteInventory.o ./build/client.o

./build : 
	mkdir $@

clean : 
	@rm -fr ./build
