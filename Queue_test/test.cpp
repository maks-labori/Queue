#include "pch.h"
#include "queue.h"
#include <utility>
TEST(TestQueue, TestDefaultConstructor) {
    Queue<int> res;
    EXPECT_EQ(res.size(), 0);
    EXPECT_EQ(res.count(), 0);
    EXPECT_THROW(res.front(), std::logic_error);
    EXPECT_THROW(res.back(), std::logic_error);
}

TEST(TestQueue, TestSizeConstructor) {
    Queue<int> res(10);
    EXPECT_EQ(res.size(), 10);
    EXPECT_EQ(res.count(), 0);
    EXPECT_THROW(res.front(), std::logic_error);
    EXPECT_THROW(res.back(), std::logic_error);
}

TEST(TestQueue, TestCopyConstructor) {
    Queue<int> res(10);
    res.push(1);
    Queue<int> res2(res);
    EXPECT_EQ(res.size(), res2.size());
    EXPECT_EQ(res.count(), res2.count());

    EXPECT_NO_THROW(res2.pop());
    EXPECT_NE(res.count(), res2.count());
    EXPECT_EQ(res.front(), 1);
    EXPECT_THROW(res2.front(), std::logic_error);
}

TEST(TestQueue, TestMoveConstructor) {
    Queue<int> res(10);
    res.push(1);
    res.push(2);
    res.push(3);

    Queue<int> res2(std::move(res));
    EXPECT_EQ(res2.size(),10);
    EXPECT_EQ(res2.count(), 3);
    EXPECT_EQ(res2.pop(), 1);
    EXPECT_EQ(res2.pop(), 2);
    EXPECT_EQ(res2.pop(), 3);
}

TEST(TestQueue, TestIsFull) {
    Queue<int> res(3);
    EXPECT_FALSE(res.isFull());
    res.push(1);
    EXPECT_FALSE(res.isFull());
    res.push(2);
    EXPECT_FALSE(res.isFull());
    res.push(3);
    EXPECT_TRUE(res.isFull());
    res.pop();
    EXPECT_FALSE(res.isFull());
}

TEST(TestQueue, TestIsEmpty) {
    Queue<int> res(3);
    EXPECT_TRUE(res.isEmpty());
    res.push(1);
    EXPECT_FALSE(res.isEmpty());
    res.pop();
    EXPECT_TRUE(res.isEmpty());
}

TEST(TestQueue, TestAssigment) {
    Queue<int> res(3);
    res.push(1);
    Queue<int> res2(10);
    res2 = res;
    EXPECT_EQ(res2.size(), 3);
    EXPECT_EQ(res2.count(), 1);
    EXPECT_EQ(res2.pop(), 1);
}

TEST(TestQueue, TestMoveAssigment) {
    Queue<int> res(3);
    res.push(1);
    Queue<int> res2(10);
    res2 = std::move(res);
    EXPECT_EQ(res2.size(), 3);
    EXPECT_EQ(res2.count(), 1);
    EXPECT_EQ(res2.pop(), 1);
}
 
TEST(TestQueue, TestPush) {
    Queue<int> res(5);
    EXPECT_EQ(res.count(), 0);
    res.push(10);
    EXPECT_EQ(res.count(), 1);
    res.push(20);
    EXPECT_EQ(res.count(), 2);
}

TEST(TestQueue, TestPop) {
    Queue<int> res(5);
    res.push(100);
    res.push(200);
    res.push(300);
    EXPECT_EQ(res.count(), 3);
    EXPECT_EQ(res.pop(), 100);
    EXPECT_EQ(res.count(), 2);
    EXPECT_EQ(res.pop(), 200);
    EXPECT_EQ(res.count(), 1);
    EXPECT_EQ(res.pop(), 300);
    EXPECT_EQ(res.count(), 0);
}

TEST(TestQueue, TestThrowPushPop) {
    Queue<int> res2(2);
    res2.push(10);
    res2.push(20);
    EXPECT_THROW(res2.push(30), std::logic_error);

    Queue<int> res(5);
    EXPECT_THROW(res.pop(), std::logic_error);
}

TEST(TestQueue, TestCircularBuffer) {
    Queue<int> res(3);
    res.push(1);
    res.push(2);
    res.push(3);

    EXPECT_EQ(res.pop(), 1);
    EXPECT_EQ(res.pop(), 2);
    EXPECT_NO_THROW(res.push(4));
    EXPECT_NO_THROW(res.push(5));
    EXPECT_EQ(res.pop(), 3);
    EXPECT_EQ(res.pop(), 4);
    EXPECT_EQ(res.pop(), 5);
    EXPECT_EQ(res.count(), 0);
}

TEST(TestQueue, TestWorkWithString) {
    Queue<std::string> q(3);
    q.push("Hello");
    q.push("World");
    EXPECT_EQ(q.pop(), "Hello");
    EXPECT_EQ(q.pop(), "World");
}