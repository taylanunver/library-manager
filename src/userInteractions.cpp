#include "userInteractions.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int askUser(std::string question, std::vector<std::string>& options, bool addBack) {
    system("cls");
    if (addBack) {
        options.push_back("Back");
    }
    for (unsigned long long i = 0; i < options.size(); i++) {
        std::cerr << '[' << i + 1 << "] " << options[i] << std::endl;
    }
    std::cerr << "====================";
    std::cerr << std::endl;
    std::cerr << question << std::endl;
    std::cerr << "Enter your choice: ";
    std::string choice;
    while (true) {
        std::getline(std::cin, choice);
        try {
            size_t choiceNum = std::stoull(choice);
            if (choiceNum >= 1 && choiceNum <= options.size()) {
                break;
            }
        } catch (const std::invalid_argument& e) {
            // do nothing, just continue the loop
        } catch (const std::out_of_range& e) {
            // do nothing, just continue the loop
        }
        std::cerr << "Invalid choice. Please try again: ";
    }
    if (addBack && std::stoull(choice) == options.size()) {
        options.clear();
        system("cls");
        return BACK;
    }
    options.clear();
    system("cls");
    return std::stoi(choice) - 1;
}