#ifndef USERINTERACTIONS_H
#define USERINTERACTIONS_H

#define BACK 808
#define BACK_2 809

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int askUser(std::string question, std::vector<std::string>& options, bool addBack = true);

#endif  // USERINTERACTIONS_H