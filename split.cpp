#include <vector>
#include <sstream>
#include <iostream>

std::vector<std::string> split(const std::string str, char delim = ' ')
{
    std::istringstream split(str);      // creates splittable version of a string
    std::vector<std::string> tokens;    // creates a vector of strings called tokens

    // tokenises string
    for (std::string each; getline(split, each, delim); tokens.push_back(each));

    return tokens;
}