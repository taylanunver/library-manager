#include "libraryControl.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define LIBRARY 101
#define BOOK 102
#define PERIODICAL 103
#define MULTIMEDIA 104

int getTokenType(std::string token) {
    if (token == "LIBRARY") {
        return LIBRARY;
    } else if (token == "BOOK") {
        return BOOK;
    } else if (token == "PERIODICAL") {
        return PERIODICAL;
    } else if (token == "MULTIMEDIA") {
        return MULTIMEDIA;
    } else {
        return 0;
    }
}

// LibraryResource constructors

LibraryResource::LibraryResource() {
    this->availableUnits = 0;
    this->totalUnits = 0;
    this->libraryId = 0;
}

// LibraryResource getters

std::string LibraryResource::getTitle() {
    return title;
}

int LibraryResource::getTotalUnits() {
    return totalUnits;
}

int LibraryResource::checkAvailability() {
    return availableUnits;
}

// LibraryResource setters

void LibraryResource::setTitle(std::string title) {
    this->title = title;
}

void LibraryResource::setLibraryId(int id) {
    this->libraryId = id;
}

void LibraryResource::addUnits(int units) {
    this->totalUnits += units;
    this->availableUnits += units;
}

void LibraryResource::setAvailableUnits(int units) {
    this->availableUnits = units;
}

// Book constructors

Book::Book() {
    this->title = "";
    this->author = "";
    this->publisher = "";
    this->description = "";
}

// Book setters

void Book::setAuthor(std::string author) {
    this->author = author;
}

void Book::setPublisher(std::string publisher) {
    this->publisher = publisher;
}

void Book::setDescription(std::string description) {
    this->description = description;
}

// Book methods

void Book::getDetails() {
    std::cout << "Title: " << title << std::endl;
    std::cout << "Author: " << author << std::endl;
    std::cout << "Publisher: " << publisher << std::endl;
    std::cout << "Description: " << description << std::endl;
}

LibraryResource::~LibraryResource() {}
Book::~Book() {}
Library::Library() {}
Library::~Library() {}

// Library getters

std::string Library::getName() {
    return name;
}

std::string Library::getAddress() {
    return address;
}

std::string Library::getPhone() {
    return phone;
}

int Library::getId() {
    return id;
}

// Library setters

void Library::setName(std::string name) {
    this->name = name;
}

void Library::setAddress(std::string address) {
    this->address = address;
}

void Library::setPhone(std::string phone) {
    this->phone = phone;
}

void Library::setId(int id) {
    this->id = id;
}

// Library methods

void Library::addResource(LibraryResource* resource) {
    resource->setLibraryId(this->id);
    resources.push_back(resource);
}

void Library::listResources() {
    for (auto resource : resources) {
        std::cout << resource->getTitle() << std::endl;
    }
}

namespace libraryControl {
int loadLibraries(std::string filename, std::vector<Library*>& libraries) {
    std::fstream file;

    // check if file exists and create if not
    file.open(filename, std::ios::in);
    if (!file) {
        file.open(filename, std::ios::out);
    }
    file.close();

    // read file and create libraries
    file.open(filename, std::ios::in);
    if (file) {
        std::string line;
        Library* currentLibrary;
        Book* currentBook;
        // Periodical* tempPeriodical;
        // Multimedia* tempMultimedia;
        while (std::getline(file, line)) {
            // sepeare line by delimiter
            std::stringstream ss(line);
            std::string token;
            int readMode;
            int column = 0;
            while (std::getline(ss, token, '|')) {
                if (column == 0) {
                    readMode = getTokenType(token);
                } else {
                    switch (readMode) {
                        case LIBRARY:
                            switch (column) {
                                case 1:
                                    currentLibrary = new Library();
                                    currentLibrary->setId(std::stoi(token));
                                    break;
                                case 2:
                                    currentLibrary->setName(token);
                                    break;
                                case 3:
                                    currentLibrary->setAddress(token);
                                    break;
                                case 4:
                                    currentLibrary->setPhone(token);
                                    libraries.push_back(currentLibrary);
                                    break;
                            }
                            break;
                        case BOOK:
                            switch (column) {
                                case 1:
                                    currentBook = new Book();
                                    currentBook->setLibraryId(std::stoi(token));
                                    break;
                                case 2:
                                    currentBook->setTitle(token);
                                    break;
                                case 3:
                                    currentBook->setAuthor(token);
                                    break;
                                case 4:
                                    currentBook->setPublisher(token);
                                    break;
                                case 5:
                                    currentBook->setDescription(token);
                                    break;
                                case 6:
                                    currentBook->addUnits(std::stoi(token));
                                    break;
                                case 7:
                                    currentBook->setAvailableUnits(std::stoi(token));
                                    currentLibrary->addResource(currentBook);
                                    break;
                            }
                    }
                }
                column++;
            }
        }
        file.close();
        return 0;
    }
    file.close();
    return 1;
}
}  // namespace libraryControl