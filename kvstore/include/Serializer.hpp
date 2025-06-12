#pragma once

#include <string>
#include <vector>
#include <utility>

class Serializer {
public:
    static void save(const std::string& filename, const std::vector<std::pair<std::string, int>>& data);

    static std::vector<std::pair<std::string, int>> load(const std::string& filename);
};
