#include "KVStore.hpp"
#include <cassert>
#include <iostream>

void testBasicSetGet() {
    KVStore kv(3);
    kv.set("a", 1);
    kv.set("b", 2);
    kv.set("c", 3);

    assert(kv.get("a").value() == 1);
    assert(kv.get("b").value() == 2);
    assert(kv.get("c").value() == 3);
    std::cout << "✅ testBasicSetGet passed.\n";
}

void testEviction() {
    KVStore kv(2);
    kv.set("x", 10);
    kv.set("y", 20);
    kv.get("x"); // Make x MRU
    kv.set("z", 30); // Should evict y

    assert(kv.get("x").has_value());
    assert(!kv.get("y").has_value());
    assert(kv.get("z").value() == 30);
    std::cout << "✅ testEviction passed.\n";
}

void testDelete() {
    KVStore kv;
    kv.set("delete_me", 99);
    assert(kv.get("delete_me").value() == 99);
    kv.del("delete_me");
    assert(!kv.get("delete_me").has_value());
    std::cout << "✅ testDelete passed.\n";
}

void testDumpAndLoad() {
    KVStore kv1;
    kv1.set("one", 1);
    kv1.set("two", 2);
    kv1.dumpToFile("store.txt");

    KVStore kv2;
    kv2.loadFromFile("store.txt");

    assert(kv2.get("one").value() == 1);
    assert(kv2.get("two").value() == 2);
    std::cout << "✅ testDumpAndLoad passed.\n";
}

int main() {
    testBasicSetGet();
    testEviction();
    testDelete();
    testDumpAndLoad();
    std::cout << "🎉 All tests passed!\n";
    return 0;
}
