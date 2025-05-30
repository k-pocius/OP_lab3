// test_student.cpp

#include <gtest/gtest.h>
#include "lib.h"
#include "V1.5vect.h"

// Test default constructor
TEST(StudentTest, DefaultConstructor) {
    Student s;
    EXPECT_EQ(s.getName(), "");
    EXPECT_EQ(s.getSurn(), "");
    EXPECT_EQ(s.getEgz(), 0);
    EXPECT_EQ(s.getVid(), 0);
    EXPECT_TRUE(s.getNd().empty());
}

// Test setters and getters
TEST(StudentTest, SettersAndGetters) {
    Student s;
    std::string name = "Jonas";
    std::string surn = "Jonaitis";
    Vector<int> nd = {9, 8, 7};

    s.setName(name);
    s.setSurn(surn);
    s.setEgz(10);
    s.setNd(nd);
    s.setVid(9.0);

    EXPECT_EQ(s.getName(), "Jonas");
    EXPECT_EQ(s.getSurn(), "Jonaitis");
    EXPECT_EQ(s.getEgz(), 10);
    EXPECT_EQ(s.getVid(), 9.0);
    EXPECT_EQ(s.getNd(), nd);
}

// Test copy constructor
TEST(StudentTest, CopyConstructor) {
    Student s1;
    s1.setName("Jonas");
    s1.setSurn("Jonaitis");
    s1.setEgz(9);
    s1.setNd(Vector<int>{10, 9});
    s1.setVid(9.1);

    Student s2(s1); // Copy constructor

    EXPECT_EQ(s2.getName(), s1.getName());
    EXPECT_EQ(s2.getSurn(), s1.getSurn());
    EXPECT_EQ(s2.getEgz(), s1.getEgz());
    EXPECT_EQ(s2.getNd(), s1.getNd());
    EXPECT_EQ(s2.getVid(), s1.getVid());
}

// Test copy assignment operator
TEST(StudentTest, CopyAssignmentOperator) {
    Student s1;
    s1.setName("Jonas");
    s1.setSurn("Jonaitis");
    s1.setEgz(10);
    s1.setNd(Vector<int>{6, 7});
    s1.setVid(7.6);

    Student s2;
    s2 = s1; // Copy assignment operator

    EXPECT_EQ(s2.getName(), s1.getName());
    EXPECT_EQ(s2.getSurn(), s1.getSurn());
    EXPECT_EQ(s2.getEgz(), s1.getEgz());
    EXPECT_EQ(s2.getNd(), s1.getNd());
    EXPECT_EQ(s2.getVid(), s1.getVid());
}

// Test move constructor
TEST(StudentTest, MoveConstructor) {
    Student s1;
    s1.setName("Jonas");
    s1.setSurn("Jonaitis");
    s1.setEgz(9);
    s1.setNd(Vector<int>{10, 9});
    s1.setVid(9.1);

    Student s2(std::move(s1)); // Move constructor

    EXPECT_EQ(s2.getName(), "Jonas");
    EXPECT_EQ(s2.getSurn(), "Jonaitis");
    EXPECT_EQ(s2.getEgz(), 9);
    EXPECT_EQ(s2.getNd(), Vector<int>({10, 9}));
    EXPECT_EQ(s2.getVid(), 9.1);


    EXPECT_EQ(s1.getName(), "");
    EXPECT_EQ(s1.getSurn(), "");
    EXPECT_EQ(s1.getEgz(), 0);
    EXPECT_EQ(s1.getNd(), Vector<int>());
    EXPECT_EQ(s1.getVid(), 0.0);
}

// Test move assignment operator
TEST(StudentTest, MoveAssignmentOperator) {
    Student s1;
    s1.setName("Jonas");
    s1.setSurn("Jonaitis");
    s1.setEgz(8);
    s1.setNd(Vector<int>{5, 6, 7});
    s1.setVid(7.5);

    Student s2;
    s2 = std::move(s1); // Move assignment operator

    EXPECT_EQ(s2.getName(), "Jonas");
    EXPECT_EQ(s2.getSurn(), "Jonaitis");
    EXPECT_EQ(s2.getEgz(), 8);
    EXPECT_EQ(s2.getNd(), Vector<int>({5, 6, 7}));
    EXPECT_EQ(s2.getVid(), 7.5);


    EXPECT_EQ(s1.getName(), "");
    EXPECT_EQ(s1.getSurn(), "");
    EXPECT_EQ(s1.getEgz(), 0);
    EXPECT_EQ(s1.getNd(), Vector<int>());
    EXPECT_EQ(s1.getVid(), 0.0);
}

// Test default empty vector
TEST(Vector, DefaultEmpty) {
    Vector<int> v;
    EXPECT_EQ(v.getSize(), static_cast<size_t>(0)); 
}

// Test push_back and access
TEST(Vector, PushBackAndAccess) {
    Vector<int> v;
    v.push_back(42);
    EXPECT_EQ(v.getSize(), static_cast<size_t>(1)); 
}

// Test pop_back
TEST(Vector, PopBack) {
    Vector<int> v;
    v.push_back(1);
    v.pop_back();
    EXPECT_EQ(v.getSize(), static_cast<size_t>(0)); 
    v.pop_back(); 
    EXPECT_EQ(v.getSize(), static_cast<size_t>(0)); 
}

// Test resize grow
TEST(Vector, ResizeGrow) {
    Vector<int> v;
    v.push_back(5);
    v.resize(3);
    EXPECT_EQ(v.getSize(), static_cast<size_t>(3)); 
    EXPECT_EQ(v[1], 0); 
}

// Test resize shrink
TEST(Vector, ResizeShrink) {
    Vector<int> v = {1, 2, 3};
    v.resize(2);
    EXPECT_EQ(v.getSize(), static_cast<size_t>(2)); 
    EXPECT_EQ(v[1], 2);
}

TEST(VectorRuleOfFive, MoveConstructor) {
    Vector<int> v1 = {7, 8, 9};
    Vector<int> v2(std::move(v1));  // Move constructor

    EXPECT_EQ(v2.getSize(), static_cast<size_t>(3)); // Fix: Explicit cast
    EXPECT_EQ(v2[0], 7);
    EXPECT_EQ(v2[1], 8);
    EXPECT_EQ(v2[2], 9);

    EXPECT_EQ(v1.getSize(), static_cast<size_t>(0)); // Fix: Explicit cast
}

TEST(VectorRuleOfFive, CopyAssignment) {
    Vector<int> v1 = {4, 5, 6};
    Vector<int> v2;
    v2 = v1;  // Copy assignment

    EXPECT_EQ(v2.getSize(), v1.getSize());
    for (size_t i = 0; i < v1.getSize(); ++i) {
        EXPECT_EQ(v2[i], v1[i]);
    }
}

TEST(VectorRuleOfFive, MoveAssignment) {
    Vector<int> v1 = {10, 11, 12};
    Vector<int> v2;
    v2 = std::move(v1);  // Move assignment

    EXPECT_EQ(v2.getSize(), static_cast<size_t>(3));
    EXPECT_EQ(v2[0], 10);
    EXPECT_EQ(v2[1], 11);
    EXPECT_EQ(v2[2], 12);

    EXPECT_EQ(v1.getSize(), static_cast<size_t>(0));
}