
#include <cstdlib>
#include <iostream>
#include <string>

#include "ByteInventory.h"

int main() {

    ByteInventory bi;
    bi.addByte(0, 100);
    bi.addByte(5, 5);
    bi.addByte(255, 123);

    std::cout << bi.toString() << std::endl;

    return EXIT_SUCCESS;
}