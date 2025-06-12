#include "KVStore.hpp"
#include "LRUCache.hpp"
#include "Serializer.hpp"


KVStore::KVStore(size_t capacity)
    : capacity(capacity), cache(std::make_unique<LRUCache<std::string, int>>(capacity)) {}


    void KVStore::set(const std::string& key, int value){
        cache->put(key, value);
    }

    std::optional<int> KVStore::get(const std::string& key) const{
        return cache->get(key);
    }

    bool KVStore::del(const std::string& key) const{
        if (cache->contains(key)){
            cache->remove(key);
            return true;
        }
        return false;
    }

    void KVStore::dumpToFile(const std::string& filename) const{
        auto data = cache->dumpAll();
        Serializer::save(filename, data);
    }

    void KVStore::loadFromFile(const std::string& filename){
        cache->clear();
        auto data = Serializer::load(filename);
        for (const auto& [key, value]: data){
            cache-> put(key, value);
        }
    }

    size_t KVStore::size() const{
        return cache->size();
    }

    



