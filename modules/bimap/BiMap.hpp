//
// Created by Nydus0 on 24/07/2025.
//

#pragma once

#include <map>

#include <iostream>

template <typename Key, typename Value>
requires std::totally_ordered<Key> && std::totally_ordered<Value>
class BiMap {

public:
    void insert(Key key, Value value) {
        auto it = _originMap.find(key);
        auto it2 = _reverseMap.find(value);

        const bool key_exists = it != _originMap.end();
        const bool value_exists = it2 != _reverseMap.end();

        if (key_exists && value_exists) {
            //do nothing
        } else if (key_exists) {
            _reverseMap.erase(it->second);
            _originMap[key] = value;
        } else if (value_exists) {
            _originMap.erase(it2->second);
            _reverseMap[value] = key;
        } else {
            _originMap[key] = value;
            _reverseMap[value] = key;
        }
    }

    void remove(Key key) {
        auto it = _originMap.find(key);
        if (it != _originMap.end()) {
            _reverseMap.erase(it->second);
        }
        _originMap.erase(key);
    }

    void remove(Value value) {
        auto it = _reverseMap.find(value);
        if (it != _reverseMap.end()) {
            _originMap.erase(it->second);
        }
        _reverseMap.erase(value);
    }

    void clear() {
        _originMap.clear();
        _reverseMap.clear();
    }

    Value getMatch(const Key& key) { return _originMap.at(key); }
    Key getMatch(const Value& value) { return _reverseMap.at(value); }

    bool empty() { return _originMap.empty(); }
    size_t size() { return _originMap.size(); }

private:
    std::map<Key, Value> _originMap;
    std::map<Value, Key> _reverseMap;
};