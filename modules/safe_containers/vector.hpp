//
// Created by Nydus0 on 23/07/2025.
//

#pragma once

#include <functional>
#include <mutex>
#include <optional>
#include <shared_mutex>
#include <vector>

namespace safe {

    template<typename T> class vector {
    public:

        //write access methods
        template<typename U> void push_back(U&& value) {
            std::unique_lock lock(_mutex);
            _data.push_back(std::forward<U>(value));
        }
        void erase(size_t index) { std::unique_lock lock(_mutex); _data.erase(_data.begin() + index); }
        void clear() { std::unique_lock lock(_mutex); _data.clear(); }

        //read access methods
        auto operator[](size_t index) const {
            std::shared_lock lock(_mutex);
            return _data[index];
        }
        size_t size() const { std::shared_lock lock(_mutex); return _data.size(); }
        bool empty() const { std::shared_lock lock(_mutex); return _data.empty(); }

    private:
        mutable std::shared_mutex _mutex;
        std::vector<T> _data;
    };

} // namespace safe
