#include "KVStore.hpp"
#include <iostream>
#include <sstream>

int main() {
    KVStore store(100); // default capacity = 100
    std::string line;

    std::cout << "Welcome to KVStore CLI. Commands: SET, GET, DEL, DUMP, LOAD, EXIT\n";

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);
        std::istringstream iss(line);

        std::string command;
        iss >> command;

        if (command == "EXIT") {
            break;
        } else if (command == "SET") {
            std::string key;
            int value;
            if (iss >> key >> value) {
                store.set(key, value);
                std::cout << "OK\n";
            } else {
                std::cout << "Usage: SET <key> <int_value>\n";
            }
        } else if (command == "GET") {
            std::string key;
            if (iss >> key) {
                auto result = store.get(key);
                if (result.has_value()) {
                    std::cout << result.value() << "\n";
                } else {
                    std::cout << "Key not found\n";
                }
            } else {
                std::cout << "Usage: GET <key>\n";
            }
        } else if (command == "DEL") {
            std::string key;
            if (iss >> key) {
                if (store.del(key)) {
                    std::cout << "Deleted\n";
                } else {
                    std::cout << "Key not found\n";
                }
            } else {
                std::cout << "Usage: DEL <key>\n";
            }
        } else if (command == "DUMP") {
            store.dumpToFile("store.txt");
            std::cout << "Store saved to store.txt\n";
        } else if (command == "LOAD") {
            store.loadFromFile("store.txt");
            std::cout << "Store loaded from store.txt\n";
        } else {
            std::cout << "Unknown command: " << command << "\n";
        }
    }

    std::cout << "Goodbye!\n";
    return 0;
}
