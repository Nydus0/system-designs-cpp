//
// Created by Nydus0 on 24/07/2025.
//

#pragma once

#include <algorithm>
#include <map>

struct Simple {}; struct Multi {};

template<typename Key, typename Value, typename Tag = Simple>
    requires std::totally_ordered<Key> && std::totally_ordered<Value>
class BiMap;

template <typename Key, typename Value>
class BiMap<Key, Value, Simple> {

public:
    void insert(const Key& key, const Value& value) {
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

    void remove(const Key& key) {
        auto it = _originMap.find(key);
        if (it != _originMap.end()) {
            _reverseMap.erase(it->second);
        }
        _originMap.erase(key);
    }

    void remove(const Value& value) {
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

    Value get_match(const Key& key) { return _originMap.at(key); }
    Key get_match(const Value& value) { return _reverseMap.at(value); }

    bool empty() { return _originMap.empty(); }
    size_t size() { return _originMap.size(); }

private:
    std::map<Key, Value> _originMap;
    std::map<Value, Key> _reverseMap;
};

template <typename Key, typename Value>
class BiMap<Key, Value, Multi> {
public:
    void insert(const Key& key, const Value& value) {
        auto it = _originMap.find(key);
        auto it2 = _reverseMap.find(value);

        const bool key_exists = it != _originMap.end();
        const bool value_exists = it2 != _reverseMap.end();

        if (key_exists && value_exists) {
            //do nothing
        } else {
            _originMap.insert({key, value});
            _reverseMap.insert({value, key});
        }
    }

    void remove(const Key &key) {
        auto range = _originMap.equal_range(key);
        for (auto [it, end_range] = _originMap.equal_range(key);
             it != end_range; ++it) {
            auto range2 = _reverseMap.equal_range(it->second);
            auto it2 = std::find_if(range2.first, range2.second, [&](const auto &pair) {
                return pair.second == key;
            });
            if (it2 != range2.second) {
                _reverseMap.erase(it2);/**/
            }
        }
        _originMap.erase(key);
    }

    void remove(const Value &value) {
        auto range = _reverseMap.equal_range(value);
        for (auto [it, end_range] = _reverseMap.equal_range(value);
             it != end_range; ++it) {
            auto range2 = _originMap.equal_range(it->second);
            auto it2 = std::find_if(range2.first, range2.second, [&](const auto &pair) {
                return pair.second == value;
            });
            if (it2 != range2.second) {
                _originMap.erase(it2);
            }
        }
        _reverseMap.erase(value);
    }

    void remove(const Key &key, const Value &value) {
        auto range = _originMap.equal_range(key);
        auto it = std::find_if(range.first, range.second, [&](const auto &pair) {
            return pair.second == value;
        });
        if (it != range.second) {
            _originMap.erase(it);
        }

        auto range2 = _reverseMap.equal_range(value);
        auto it2 = std::find_if(range2.first, range2.second, [&](const auto &pair) {
            return pair.second == key;
        });
        if (it2 != range2.second) {
            _reverseMap.erase(it2);
        }
    }

    auto get_match_equal_range(const Key& key) { return _originMap.equal_range(key); }
    auto get_match_equal_range(const Value& value) { return _reverseMap.equal_range(value); }

    bool empty() { return _originMap.empty(); }
    size_t size() { return _originMap.size(); }

private:
    std::multimap<Key, Value> _originMap;
    std::multimap<Value, Key> _reverseMap;

};