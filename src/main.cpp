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
librarySelection:
    system("cls");
    static std::vector<std::string> options;
    options.push_back("Add library");
    options.push_back("Save & Exit");
    for (auto library : libraries) {
        options.push_back(library->getName());
    }
    int selectedLibraryIndex = askUser("Select a library", options, false);
    switch (selectedLibraryIndex) {
        case 0:
            libraryControl::addLibrary(libraries);
            goto librarySelection;
            break;
        case 1:
            goto saveAndExit;
        default:
            selectedLibraryIndex -= 2;
            break;
    }
    Library* selectedLibrary = libraries[selectedLibraryIndex];

// Ask user to select a function
insideLibrary:
    options.push_back("Add resource");
    options.push_back("List resources");
    options.push_back("Search resources");

    switch (askUser("Select a function", options)) {
        case 0:
            selectedLibrary->addResource();
            goto insideLibrary;
        case 1:
        listResources:
            for (auto resource : selectedLibrary->getResourceTitles()) {
                options.push_back(resource);
            }
            if (askUserResource(selectedLibrary->getResource(askUser("Select a resource", options))) == BACK_2) {
                std::cerr << "Back" << std::endl;
                goto insideLibrary;
            }
            goto listResources;
        case 2:
            system("cls");
            static std::string keyword;
            std::cout << "Enter keyword: ";
            std::getline(std::cin, keyword);
            static auto results = libraryControl::searchResources(keyword, selectedLibrary);
            for (auto resource : results) {
                options.push_back(resource->getTitle());
            }
            askUser("Select a resource", options);
            break;
        case BACK:
            goto librarySelection;
    }
saveAndExit:
    if (libraryControl::saveLibraries(filename, libraries)) {
        std::cout << "Error saving libraries" << std::endl;
        return 1;
    }
    return 0;
}