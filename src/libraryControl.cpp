#include "libraryControl.h"
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "userInteractions.h"

#define LIBRARY 101
#define BOOK 102
#define PERIODICAL 103
#define MULTIMEDIA 104

namespace libraryControl {

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
                                    currentBook->setTitle(token);
                                    break;
                                case 2:
                                    currentBook->setAuthor(token);
                                    break;
                                case 3:
                                    currentBook->setPublisher(token);
                                    break;
                                case 4:
                                    currentBook->setDescription(token);
                                    break;
                                case 5:
                                    currentBook->addUnits(std::stoi(token));
                                    break;
                                case 6:
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

int saveLibraries(std::string& filename, std::vector<Library*>& libraries) {
    std::ofstream file;
    file.open(filename);
    if (file) {
        for (auto library : libraries) {
            file << "LIBRARY|" << library->id << "|" << library->name << "|" << library->address << "|" << library->phone << std::endl;
            for (auto resource : library->resources) {
                resource->save(file);
            }
        }
        file.close();
        return 0;
    }
    file.close();
    return 1;
}

std::vector<LibraryResource*> searchResources(std::string& keyword, Library* library) {
    std::vector<LibraryResource*> results;
    std::string keywordLower = keyword;
    std::transform(keywordLower.begin(), keywordLower.end(), keywordLower.begin(), std::bind(std::tolower<char>, std::placeholders::_1, std::locale()));
    for (auto resource : library->resources) {
        std::string titleLower = resource->getTitle();
        std::transform(titleLower.begin(), titleLower.end(), titleLower.begin(), std::bind(std::tolower<char>, std::placeholders::_1, std::locale()));
        if (titleLower.find(keywordLower) != std::string::npos) {
            results.push_back(resource);
        }
    }
    return results;
}

// LibraryResource constructors

LibraryResource::LibraryResource() {
    this->availableUnits = 0;
    this->totalUnits = 0;
}

LibraryResource::~LibraryResource() {}

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

void LibraryResource::addUnits(int units) {
    this->totalUnits += units;
    this->availableUnits += units;
}

void LibraryResource::setAvailableUnits(int units) {
    this->availableUnits = units;
}

int LibraryResource::checkOut() {
    if (availableUnits > 0) {
        availableUnits--;
        return 0;
    }
    return 1;
}

void LibraryResource::returnResource() {
    if (availableUnits < totalUnits) {
        availableUnits++;
    } else {
        std::cout << "All units are available" << std::endl;
        std::cin.ignore();
    }
}

int askUserResource(LibraryResource* resource) {
    if (resource == nullptr) {
        return BACK_2;
    }
    std::vector<std::string> options;
    options.push_back("Borrow");
    options.push_back("Return");
    options.push_back("Details");
    int choice = askUser(resource->getTitle(), options);
    switch (choice) {
        case 0:
            resource->checkOut();
            break;
        case 1:
            resource->returnResource();
            break;
        case 2:
            resource->getDetails();
            break;
        case BACK:
            return BACK;
    }
    return 0;
}

// Book constructors

Book::Book() {
    this->title = "";
    this->author = "";
    this->publisher = "";
    this->description = "";
}

Book::~Book() {}

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
    std::cin.ignore();
}

void Book::save(std::ofstream& file) {
    file << "BOOK|" << title << "|" << author << "|" << publisher << "|" << description << "|" << totalUnits << "|" << availableUnits << std::endl;
}

// Library constructors

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

std::vector<std::string> Library::getResourceTitles() {
    std::vector<std::string> titles;
    for (auto resource : resources) {
        titles.push_back(resource->getTitle());
    }
    return titles;
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
    resources.push_back(resource);
}

void Library::addResource() {
    std::string title;
    std::string author;
    std::string publisher;
    std::string description;
    int units;
    std::cout << "Enter title: ";
    std::getline(std::cin, title);
    std::cout << "Enter author: ";
    std::getline(std::cin, author);
    std::cout << "Enter publisher: ";
    std::getline(std::cin, publisher);
    std::cout << "Enter description: ";
    std::getline(std::cin, description);
    std::cout << "Enter units: ";
    std::cin >> units;
    Book* book = new Book();
    book->setTitle(title);
    book->setAuthor(author);
    book->setPublisher(publisher);
    book->setDescription(description);
    book->addUnits(units);
    book->setAvailableUnits(units);
    resources.push_back(book);
}

void Library::listResources() {
    system("cls");
    std::cout << name << std::endl;
    std::cout << "====================" << std::endl;
    for (auto resource : resources) {
        std::cout << resource->getTitle() << std::endl;
    }
}

LibraryResource* Library::getResource(unsigned long long int index) {
    if (index >= resources.size()) {
        return nullptr;
    }
    return resources[index];
}
void addLibrary(std::vector<Library*>& libraries) {
    std::string name;
    std::string address;
    std::string phone;
    std::cout << "Enter name: ";
    std::getline(std::cin, name);
    std::cout << "Enter address: ";
    std::getline(std::cin, address);
    std::cout << "Enter phone: ";
    std::getline(std::cin, phone);
    Library* library = new Library();
    library->setName(name);
    library->setAddress(address);
    library->setPhone(phone);
    library->setId(libraries.size());
    libraries.push_back(library);
}
}  // namespace libraryControl