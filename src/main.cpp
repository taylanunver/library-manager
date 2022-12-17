#include <iostream>
#include <string>
#include <vector>
#include "libraryControl.h"

int main() {
    std::string filename = "test.lmdb";
    std::vector<Library*> libraries;
    if (libraryControl::loadLibraries(filename, libraries)) {
        std::cout << "Error loading libraries" << std::endl;
        return 1;
    }
    for (auto library : libraries) {
        std::cout << "Library: " << library->getName() << std::endl;
        std::cout << "Address: " << library->getAddress() << std::endl;
        std::cout << "Phone: " << library->getPhone() << std::endl;
        std::cout << "ID: " << library->getId() << std::endl;
        library->listResources();
        std::cout << std::endl;
    }
    return 0;
}