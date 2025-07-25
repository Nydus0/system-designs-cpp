//
// Created by Nydus0 on 24/07/2025.
//

#include "modules/bimap/BiMap.hpp"

#include <gtest/gtest.h>

TEST(bimap, simple_insert) {
    BiMap<std::string, int> map;

    map.insert("obj1", 1);
    map.insert("obj2", 2);
    map.insert("obj3", 3);
    EXPECT_EQ(map.size(), 3);
}

TEST(bimap, simple_remove) {
    BiMap<std::string, int> map;

    map.insert("obj1", 1);
    map.insert("obj2", 2);
    map.insert("obj3", 3);
    map.remove("obj2");
    map.remove(3);
    EXPECT_EQ(map.size(), 1);
}

TEST (bimap, simple_clear) {
    BiMap<std::string, int> map;

    map.insert("obj1", 1);
    map.insert("obj2", 2);
    map.insert("obj3", 3);
    map.clear();
}

TEST (bimap, simple_empty) {
    BiMap<std::string, int> map;

    EXPECT_EQ(map.empty(), true);
    map.insert("obj1", 1);
    EXPECT_EQ(map.empty(), false);
    map.insert("obj2", 2);
    EXPECT_EQ(map.empty(), false);
    map.clear();
    EXPECT_EQ(map.empty(), true);
}

TEST (bimap, simple_get_match) {
    BiMap<std::string, int> map;

    map.insert("obj1", 1);
    map.insert("obj2", 2);
    EXPECT_EQ(map.get_match("obj1"), 1);
    EXPECT_EQ(map.get_match(1), "obj1");
    EXPECT_EQ(map.get_match("obj2"), 2);
    EXPECT_EQ(map.get_match(2), "obj2");
}

TEST (bimap, multi_insert) {
    BiMap<std::string, int, Multi> bimap;

    bimap.insert("link11", 1);
    bimap.insert("link11", 2);
    EXPECT_EQ(bimap.size(), 2);
    bimap.insert("link22", 2);
    bimap.insert("link32", 2);
    EXPECT_EQ(bimap.size(), 4);
    bimap.insert("link22", 2);
    EXPECT_EQ(bimap.size(), 4);
    bimap.insert("link33", 3);
    EXPECT_EQ(bimap.size(), 5);
}

TEST (bimap, multi_remove_value) {
    BiMap<std::string, int, Multi> bimap;

    bimap.insert("link11", 1);
    bimap.insert("link11", 2);
    bimap.insert("link22", 2);
    bimap.insert("link32", 2);
    bimap.insert("link22", 2);
    bimap.insert("link33", 3);
    EXPECT_EQ(bimap.size(), 5);
    bimap.remove(2);
    EXPECT_EQ(bimap.size(), 2);
}

TEST (bimap, multi_remove_key) {
    BiMap<std::string, int, Multi> bimap;

    bimap.insert("link11", 1);
    bimap.insert("link11", 2);
    bimap.insert("link22", 2);
    bimap.insert("link32", 2);
    bimap.insert("link22", 4);
    bimap.insert("link33", 3);
    EXPECT_EQ(bimap.size(), 6);
    bimap.remove("link22");
    EXPECT_EQ(bimap.size(), 4);
}

TEST (bimap, multi_remove_pair) {
    BiMap<std::string, int, Multi> bimap;

    bimap.insert("link11", 1);
    bimap.insert("link11", 2);
    bimap.insert("link22", 2);
    bimap.insert("link32", 2);
    bimap.insert("link33", 3);
    EXPECT_EQ(bimap.size(), 5);
    bimap.remove("link22", 2);
    EXPECT_EQ(bimap.size(), 4);
}

TEST (bimap, multi_get_match_equal_range) {
    BiMap<std::string, int, Multi> bimap;
    bimap.insert("link11", 1);
    bimap.insert("link11", 2);
    bimap.insert("link22", 2);
    bimap.insert("link32", 2);
    bimap.insert("link33", 3);

    auto [it_begin, it_end] = bimap.get_match_equal_range("link11");
    EXPECT_EQ(it_begin->second, 1);
    EXPECT_EQ(std::next(it_begin, 1)->second, 2);
    auto [it_begin2, it_end2] = bimap.get_match_equal_range(2);
    EXPECT_EQ(it_begin2->second, "link11");
    EXPECT_EQ(std::next(it_begin2, 1)->second, "link22");
    EXPECT_EQ(std::next(it_begin2, 2)->second, "link32");
}


