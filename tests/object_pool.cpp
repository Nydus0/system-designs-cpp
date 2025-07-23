//
// Created by Nydus0 on 19/07/2025.
//

#include "modules/object_pool/ObjectPool.hpp"

#include <gtest/gtest.h>

constexpr size_t poolSize = 100;

class LargeObject {
public:
    void reset() { _arr.fill(""); }
    std::string name() { return _name; }
    void setName(const std::string& name) { _name = name; }

private:
    std::string _name;
    std::array<std::string, 10000> _arr;
};

TEST(object_pool, acquire) {

    ObjectPool<std::string, LargeObject> objectPool(poolSize);

    EXPECT_NO_THROW({
        LargeObject* obj = objectPool.acquire("obj");
        obj->setName("obj2");
        EXPECT_EQ(obj->name(), "obj2");
    });

}

TEST(object_pool, release) {

    ObjectPool<std::string, LargeObject> objectPool(poolSize);

    EXPECT_NO_THROW({
        LargeObject* obj1 = objectPool.acquire("obj1");
        LargeObject* obj2 = objectPool.acquire("obj2");
        objectPool.release("obj1");

        EXPECT_TRUE(objectPool.get("obj1") == nullptr);
        EXPECT_TRUE(objectPool.get("obj2") != nullptr);
    });

}
