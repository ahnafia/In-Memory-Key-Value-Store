#pragma once

#include <string>
#include <optional>
#include <memory>

template<typename Key, typename Value>
class LRUCache;

class Serializer;

class KVStore{
    public:
        KVStore(size_t capacity=100);

        void set(const std::string& key, int value);
        std::optional<int> get(const std::string& key) const;
        bool del(std::string& key) const;
        void dumpToFile(std::string& filename) const;
        void loadFromFile(std::string& filename) const;
        size_t size() const;

    private:
        size_t capacity;
        std::unique_ptr<LRUCache<std::string, int>> cache;
};

