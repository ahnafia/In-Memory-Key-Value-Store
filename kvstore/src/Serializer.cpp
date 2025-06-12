#include "Serializer.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

void Serializer::save(const std::string& filename, const std::vector<std::pair<std::string, int>>& data) {
    std::ofstream outFile(filename);

    if (!outFile) {
        std::cerr << "Error: Could not open file for writing: " << filename << "\n";
        return;
    }

    for (const auto& [key, value] : data) {
        outFile << key << " " << value << "\n";
    }

    outFile.close();
}

std::vector<std::pair<std::string, int>> Serializer::load(const std::string& filename) {
    std::ifstream inFile(filename);
    std::vector<std::pair<std::string, int>> result;

    if (!inFile) {
        std::cerr << "Error: Could not open file for reading: " << filename << "\n";
        return result;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string key;
        int value;

        if (iss >> key >> value) {
            result.emplace_back(key, value);
        }
    }

    inFile.close();
    return result;
}
