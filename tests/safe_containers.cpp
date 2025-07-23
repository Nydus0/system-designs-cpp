//
// Created by Nydus0 on 23/07/2025.
//

#include "modules/safe_containers/vector.hpp"

#include <gtest/gtest.h>
#include <string>

#include "modules/safe_containers/fifo.hpp"

class Object {
public:
    explicit Object(std::string name) : _name(move(name)) {}
    std::string name() { return _name; }
    void setName(const std::string& name) { _name = name; }

private:
    std::string _name;
    std::array<std::string, 10000> _arr;
};

TEST(safe_containers, vector) {

    Object obj1("obj1"); Object obj2("obj2"); Object obj3("obj3");
    std::vector int_list {0,1,2,3};
    std::vector int_list2 {4,5,6};

    safe::vector<int> vec_int;
    safe::vector<Object> vec_Object;
    safe::vector<std::vector<int>> vec_vec_int;

    vec_int.push_back(1); vec_int.push_back(2); vec_int.push_back(3);
    vec_Object.push_back(obj1); vec_Object.push_back(obj2); vec_Object.push_back(obj3);
    vec_Object.erase(1);
    vec_vec_int.push_back(int_list); vec_vec_int.push_back(int_list2);

    //add
    EXPECT_EQ(vec_int[0], 1); EXPECT_EQ(vec_int[1], 2); EXPECT_EQ(vec_int[2], 3);
    //erase
    EXPECT_EQ(vec_Object[0].name(), obj1.name()); EXPECT_EQ(vec_Object[1].name(), obj3.name());
    //at
    EXPECT_EQ(vec_int.at(0), 1);
    EXPECT_THROW(vec_Object.at(3), std::out_of_range);
    //size
    EXPECT_EQ(vec_vec_int.size(), 2);
    //clear & empty
    EXPECT_EQ(vec_Object.empty(), false);
    vec_Object.clear();
    EXPECT_EQ(vec_Object.size(), 0);
    EXPECT_EQ(vec_Object.empty(), true);
}

TEST(safe_containers, fifo) {

    Object obj1("obj1"); Object obj2("obj2"); Object obj3("obj3");

    safe::fifo<int> fifo1;
    safe::fifo<Object> fifo2;

    //push
    fifo1.push(1); fifo1.push(2); fifo1.push(3);
    fifo2.push(obj1);  fifo2.push(obj2);  fifo2.push(obj3);
    EXPECT_EQ(fifo1.size(), 3); EXPECT_EQ(fifo2.size(), 3);
    //front
    EXPECT_EQ(fifo1.front(), 1);
}


