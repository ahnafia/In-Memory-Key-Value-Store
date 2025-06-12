#pragma once

#include <list>
#include <unordered_map>
#include <vector>
#include <optional>

template<typename Key, typename Value>
class LRUCache {
private:
    size_t m_capacity;
    std::list<Key> usageOrder;
    std::unordered_map<Key, std::pair<Value, typename std::list<Key>::iterator>> cache;

public:
    LRUCache(size_t cap);

    void put(const Key& key, const Value& value);
    std::optional<Value> get(const Key& key);
    void remove(const Key& key);
    bool contains(const Key& key) const;
    size_t size() const;
    void clear();
    std::vector<std::pair<Key, Value>> dumpAll() const;
};


template <typename Key, typename Value>
LRUCache<Key, Value>::LRUCache(size_t cap)
    : m_capacity(cap) {}


template <typename Key, typename Value>
void LRUCache<Key, Value>::put(const Key& key, const Value& value) {
    auto it = cache.find(key);

    if (it != cache.end()) {
        it->second.first = value;
        usageOrder.erase(it->second.second);
        usageOrder.push_front(key);
        it->second.second = usageOrder.begin();
    } else {
        if (cache.size() == m_capacity) {
            Key lruKey = usageOrder.back();
            usageOrder.pop_back();
            cache.erase(lruKey);
        }
        usageOrder.push_front(key);
        cache[key] = { value, usageOrder.begin() };
    }
}

template <typename Key, typename Value>
std::optional<Value> LRUCache<Key, Value>::get(const Key& key) {
    auto it = cache.find(key);
    if (it == cache.end()) {
        return std::nullopt;
    }

    usageOrder.erase(it->second.second);
    usageOrder.push_front(key);
    it->second.second = usageOrder.begin();
    return it->second.first;
}

template <typename Key, typename Value>
void LRUCache<Key, Value>::remove(const Key& key) {
    auto it = cache.find(key);
    if (it != cache.end()) {
        usageOrder.erase(it->second.second);
        cache.erase(it);
    }
}

template <typename Key, typename Value>
bool LRUCache<Key, Value>::contains(const Key& key) const {
    return cache.find(key) != cache.end();
}

template <typename Key, typename Value>
size_t LRUCache<Key, Value>::size() const {
    return cache.size();
}

template <typename Key, typename Value>
void LRUCache<Key, Value>::clear() {
    usageOrder.clear();
    cache.clear();
}

template <typename Key, typename Value>
std::vector<std::pair<Key, Value>> LRUCache<Key, Value>::dumpAll() const {
    std::vector<std::pair<Key, Value>> result;
    for (const Key& key : usageOrder) {
        auto it = cache.find(key);
        if (it != cache.end()) {
            result.emplace_back(key, it->second.first);
        }
    }
    return result;
}
