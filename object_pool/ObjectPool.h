//
// Created by Nydus0 on 21/06/2025.
//

#ifndef object_pool_ObjectPool_H
#define object_pool_ObjectPool_H

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
    explicit ObjectPool(size_t poolSize) : MAX_POOL_SIZE(poolSize) {
    }

    T *storeObject(Key key) {
        auto availableObject = move(_freeObjects.top());
        _freeObjects.pop();
        T *resultPtr = availableObject.get();
        _storedObjects.insert({key, move(availableObject)});
        return resultPtr;
    }

    T *acquire(const Key &key) {
        T *resultPtr;

        _currentSize = _storedObjects.size() + _freeObjects.size();

        if (_currentSize < MAX_POOL_SIZE) {
            //maximum object number has not yet been reached

            if (!_freeObjects.empty()) {
                //free objects are available => get one free object and add it to stored objects
                auto availableObject = move(_freeObjects.top());
                _freeObjects.pop();
                resultPtr = availableObject.get();
                _storedObjects.insert({key, move(availableObject)});
            } else {
                //no free objects available => construct and store directly in stored objects
                auto newObject = std::make_unique<T>();
                resultPtr = newObject.get();
                _storedObjects.insert({key, move(newObject)});
            }
        } else {
            //maximum object number is reached

            if (!_freeObjects.empty()) {
                //free objects are available => get one free object and add it to stored objects
                auto availableObj = move(_freeObjects.top());
                _freeObjects.pop();
                resultPtr = availableObj.get();
                _storedObjects.insert({key, move(availableObj)});
            } else {
                //no more free objects available
                resultPtr = nullptr;
            }
        }
        return resultPtr;
    }

    T *get(const Key &key) {
        auto it = _storedObjects.find(key);
        if (it != _storedObjects.end()) {
            return it->second.get();
        } else {
            return nullptr;
        }
    }

    std::vector<T *> getObjects() {
        std::vector<T *> vec;
        for (auto &it: _storedObjects) {
            vec.push_back(it.second.get());
        }
        return vec;
    }

    void release(const Key &key) {
        auto it = _storedObjects.find(key);
        if (it != _storedObjects.end()) {
            it->second->reset();
            _freeObjects.push(move(it->second)); //transfer ownership to free objects stack
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

    bool isAtCapacity() {
        return _storedObjects.size() >= MAX_POOL_SIZE;
    }

private:
    size_t MAX_POOL_SIZE{0};
    size_t _currentSize{0};
    std::map<Key, std::unique_ptr<T> > _storedObjects;
    std::stack<std::unique_ptr<T> > _freeObjects;
};


#endif
