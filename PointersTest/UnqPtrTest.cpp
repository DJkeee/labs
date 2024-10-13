#include <gtest/gtest.h>
#include <stdexcept>
#include "../Pointers/UnqPtr.h"

class TestClass {
public:
    TestClass(int value) : value(value) {}
    int getValue() const { return value; }
private:
    int value;
};

TEST(UnqPtrTest, ConstructionAndDestruction) {
    UnqPtr<TestClass> ptr = makeUnq<TestClass>(42);
    EXPECT_EQ(ptr->getValue(), 42);
}

TEST(UnqPtrTest, MoveConstructor) {
    UnqPtr<TestClass> ptr1 = makeUnq<TestClass>(10);
    UnqPtr<TestClass> ptr2 = std::move(ptr1);

    EXPECT_EQ(ptr2->getValue(), 10);
    EXPECT_EQ(ptr1.get(), nullptr);
}

TEST(UnqPtrTest, MoveAssignment) {
    UnqPtr<TestClass> ptr1 = makeUnq<TestClass>(20);
    UnqPtr<TestClass> ptr2 = makeUnq<TestClass>(30);

    ptr2 = std::move(ptr1);

    EXPECT_EQ(ptr2->getValue(), 20);
    EXPECT_EQ(ptr1.get(), nullptr);
}

TEST(UnqPtrTest, NullPointer) {
    UnqPtr<TestClass> ptr(nullptr);
    EXPECT_EQ(ptr.get(), nullptr);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
