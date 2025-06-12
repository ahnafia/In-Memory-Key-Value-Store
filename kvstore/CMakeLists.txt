cmake_minimum_required(VERSION 3.12)
project(KVStore)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(kvstore
    src/main.cpp
    src/KVStore.cpp
    src/LRUCache.cpp
    src/Serializer.cpp
)

add_executable(test_kvstore tests/test_kvstore.cpp src/KVStore.cpp src/LRUCache.cpp src/Serializer.cpp)
