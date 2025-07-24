//
// Created by Nydus0 on 24/07/2025.
//

#include "modules/bimap/BiMap.hpp"

#include <gtest/gtest.h>

TEST(bimap, insert) {
    BiMap<std::string, int> map;
    map.insert("obj1", 1);
    map.insert("obj2", 2);
    map.insert("obj3", 3);
    EXPECT_EQ(map.size(), 3);
}

TEST(bimap, remove) {
    BiMap<std::string, int> map;
    map.insert("obj1", 1);
    map.insert("obj2", 2);
    map.insert("obj3", 3);
    map.remove("obj2");
    map.remove(3);
    EXPECT_EQ(map.size(), 1);
}

TEST (bimap, clear) {
    BiMap<std::string, int> map;
    map.insert("obj1", 1);
    map.insert("obj2", 2);
    map.insert("obj3", 3);
    map.clear();
    EXPECT_EQ(map.size(), 0);
}

TEST (bimap, getMatch) {
    BiMap<std::string, int> map;
    map.insert("obj1", 1);
    map.insert("obj2", 2);

    EXPECT_EQ(map.getMatch("obj1"), 1);
    EXPECT_EQ(map.getMatch(1), "obj1");
    EXPECT_EQ(map.getMatch("obj2"), 2);
    EXPECT_EQ(map.getMatch(2), "obj2");
}

