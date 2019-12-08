all : ./build/client

./build/client.o : ./src/client.cc ./src/client.h ./src/ByteInventory.h ./src/HuffmanTree.h  | ./build
	g++ -Wall -g -std=c++11 -o $@ -c src/client.cc

./build/ByteInventory.o : ./src/ByteInventory.cc ./src/ByteInventory.h | ./build
	g++ -Wall -g -std=c++11 -o $@ -c src/ByteInventory.cc

./build/HuffmanTree.o : ./src/HuffmanTree.cc ./src/HuffmanTree.h | ./build 
	g++ -Wall -g -std=c++11 -o $@ -c src/HuffmanTree.cc

./build/client : ./build/ByteInventory.o  ./build/HuffmanTree.o ./build/client.o | ./build
	g++ -Wall -g -std=c++11 -o $@ ./build/ByteInventory.o ./build/client.o ./build/HuffmanTree.o

# Test File build.
./build/test.o : ./src/test.cc | ./build
	g++ -Wall -g -std=c++11 -o $@ -c src/test.cc

./build/test : ./build/ByteInventory.o ./build/test.o | ./build
	g++ -Wall -g -std=c++11 -o $@ ./build/ByteInventory.o ./build/test.o


./build : 
	mkdir $@

clean : 
	@rm -fr ./build
