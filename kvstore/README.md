# C++ In-Memory Key-Value Store with LRU Eviction and Persistence

A lightweight, single-threaded in-memory key-value store written in modern C++. It supports basic operations, least-recently-used (LRU) cache eviction, and file-based persistence.

## Features

- SET key value: Insert or update a key with an integer value
- GET key: Retrieve a value by key
- DEL key: Delete a key
- DUMP: Save the current state to `store.txt`
- LOAD: Load state from `store.txt`
- LRU eviction policy when cache capacity is exceeded