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
        auto it = _forward.find(key);
        auto it2 = _reverse.find(value);

        const bool key_exists = it != _forward.end();
        const bool value_exists = it2 != _reverse.end();

        // remove old links if they exist
        if (key_exists) { _reverse.erase(it->second); }
        if (value_exists) { _forward.erase(it2->second); }

        // insert new links
        _forward[key] = value;
        _reverse[value] = key;
    }

    void remove(const Key& key) {
        auto it = _forward.find(key);
        if (it != _forward.end()) {
            _reverse.erase(it->second);
        }
        _forward.erase(key);
    }

    void remove(const Value& value) {
        auto it = _reverse.find(value);
        if (it != _reverse.end()) {
            _forward.erase(it->second);
        }
        _reverse.erase(value);
    }

    void clear() {
        _forward.clear();
        _reverse.clear();
    }

    Value get_match(const Key& key) { return _forward.at(key); }
    Key get_match(const Value& value) { return _reverse.at(value); }

    bool empty() { return _forward.empty(); }
    size_t size() { return _forward.size(); }

private:
    std::map<Key, Value> _forward;
    std::map<Value, Key> _reverse;
};

template <typename Key, typename Value>
class BiMap<Key, Value, Multi> {
public:
    void insert(const Key& key, const Value& value) {
        // Check if the exact (key, value) pair already exists in _forward
        auto range = _forward.equal_range(key);
        bool pair_exists = false;
        for (auto it = range.first; it != range.second; ++it) {
            if (it->second == value) {
                pair_exists = true;
                break;
            }
        }

        // if the pair does not exist, insert it into both maps
        if (!pair_exists) {
            _forward.insert({key, value});
            _reverse.insert({value, key});
        }
    }

    void remove(const Key &key) {
        auto [begin, end] = _forward.equal_range(key);
        for (auto it = begin; it != end; ++it) {
            // remove the corresponding (value, key) pair from _reverse
            auto [begin2, end2] = _reverse.equal_range(it->second);
            auto it2 = std::find_if(
                begin2,
                end2,
                [&key](const auto &pair) { return pair.second == key; }
            );
            if (it2 != end2) {
                _reverse.erase(it2);
            }
        }
        // remove all (key, value) pairs from _forward
        _forward.erase(begin, end);
    }

    void remove(const Value &value) {
        auto [begin, end] = _reverse.equal_range(value);
        for (auto it = begin; it != end; ++it) {
            // remove the corresponding (key, value) pair from _forward
            auto [begin2, end2] = _forward.equal_range(it->second);
            auto it2 = std::find_if(
                begin2,
                end2,
                [&value](const auto &pair) { return pair.second == value; }
            );
            if (it2 != end2) {
                _forward.erase(it2);
            }
        }
        // remove all (value, key) pairs from _reverse
        _reverse.erase(begin, end);
    }

    void remove(const Key &key, const Value &value) {
        // remove (key, value) from _forward
        auto [begin, end] = _forward.equal_range(key);
        auto it = std::find_if(
            begin,
            end,
            [&value](const auto &pair) { return pair.second == value; }
        );
        if (it != end) {
            _forward.erase(it);
        }

        // remove (value, key) from _reverse
        auto [begin2, end2] = _reverse.equal_range(value);
        auto it2 = std::find_if(
            begin2,
            end2,
            [&key](const auto &pair) { return pair.second == key; }
        );
        if (it2 != end2) {
            _reverse.erase(it2);
        }
    }

    void clear() {
        _forward.clear();
        _reverse.clear();
    }

    auto get_match_equal_range(const Key& key) { return _forward.equal_range(key); }
    auto get_match_equal_range(const Value& value) { return _reverse.equal_range(value); }

    bool empty() { return _forward.empty(); }
    size_t size() { return _forward.size(); }

private:
    std::multimap<Key, Value> _forward;
    std::multimap<Value, Key> _reverse;

};