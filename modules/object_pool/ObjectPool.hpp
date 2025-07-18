//
// Created by Nydus0 on 21/06/2025.
//

#pragma once

#include <concepts>
#include <map>
#include <memory>
#include <stack>
#include <vector>

template<typename T>
concept has_reset = requires(T t) { { t.reset() } -> std::same_as<void>; };

template<typename Key, has_reset T>
class ObjectPool {
    /** @brief Object pool class can be used for large objects.
       The pool avoids calls to many constructions and deletions of large objects.

       Instead, the pool resets the already constructed objects and places them in
       a free objects stack for later use.
       As a result type T of the objects of the pool must have a reset() function.

       Key type is the type of the map key, allowing for efficient pool search: it
       must be defined when constructing the pool.

       This object pool is RAII : unique_ptr are moved between both pool containers
       _freeObjects and _storedObjects.
       **/
public:
    explicit ObjectPool(const size_t poolSize) : _maxPoolSize(poolSize) {}

    [[nodiscard]] T *acquire(const Key &key) {

        if (_storedObjects.size() + _freeObjects.size() >= _maxPoolSize && _freeObjects.empty()) {
            return nullptr;
        }

        std::unique_ptr<T> obj;
        if (!_freeObjects.empty()) {
            obj = std::move(_freeObjects.top());
            _freeObjects.pop();
        } else {
            obj = std::make_unique<T>();
        }

        T* resultPtr = obj.get();
        _storedObjects.emplace(key, std::move(obj));
        return resultPtr;
    }

    [[nodiscard]] T *get(const Key &key) {
        auto it = _storedObjects.find(key);
        if (it != _storedObjects.end()) {
            return it->second.get();
        }
        return nullptr;
    }

    std::vector<T *> getObjects() {
        std::vector<T *> vec;
        vec.reserve(_storedObjects.size());
        for (auto& [key, obj] : _storedObjects) {
            vec.push_back(obj.get());
        }
        return vec;
    }

    void release(const Key &key) {
        auto it = _storedObjects.find(key);
        if (it != _storedObjects.end() && it->second) {
            it->second->reset();
            _freeObjects.push(std::move(it->second)); //transfer ownership to free objects stack
            _storedObjects.erase(it); //erase element from map
        }
    }

    void releaseAll() {
        for (auto &it: _storedObjects) {
            it.second.reset();
            _freeObjects.push(std::move(it.second));
        }
        _storedObjects.clear();
    }

    [[nodiscard]] bool isAtCapacity() const {
        return _storedObjects.size() >= _maxPoolSize;
    }

private:
    size_t _maxPoolSize {0};
    std::map<Key, std::unique_ptr<T> > _storedObjects;
    std::stack<std::unique_ptr<T> > _freeObjects;
};
