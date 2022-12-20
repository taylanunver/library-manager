#include <iostream>
#include <string>
#include <vector>
#include "libraryControl.h"
#include "userInteractions.h"

using libraryControl::Library;

int main(int argc, char* argv[]) {
    // Get filename from command line or user input
    std::string filename;
    if (argc < 2) {
        std::cout << "Please provide a filename" << std::endl;
        std::getline(std::cin, filename);
    } else {
        filename = argv[1];
    }

    // Load libraries from file
    std::vector<Library*> libraries;
    if (libraryControl::loadLibraries(filename, libraries)) {
        std::cout << "Error loading libraries" << std::endl;
        return 1;
    }

    // Ask user to select a library
    std::vector<std::string> options;
    for (auto library : libraries) {
        options.push_back(library->getName());
    }
    Library* selectedLibrary = libraries[askUser("Select a library", options)];
    options.clear();

    // Ask user to select a function
    options.push_back("Add resource");
    options.push_back("List resources");
    options.push_back("Search resources");

    switch (askUser("Select a function", options)) {
        case 0:
            selectedLibrary->addResource();
            break;
        case 1:
            selectedLibrary->listResources();
            break;
        case 2:
            std::string keyword;
            std::cout << "Enter keyword: ";
            std::getline(std::cin, keyword);
            options.clear();
            auto results = libraryControl::searchResources(keyword, selectedLibrary);
            for (auto resource : results) {
                options.push_back(resource->getTitle());
            }
            askUser("Select a resource", options);
            break;
    }
    return 0;
}