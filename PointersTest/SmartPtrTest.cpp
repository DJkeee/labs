#include "../Pointers/SharedPtr.h"
#include "gtest/gtest.h"

class MyClass {
public:
    int value;

    MyClass(int val) : value(val) {
    }
};

TEST(ShrdPtrTest, CreateAndUse) {
    SharedPtr<MyClass> ptr1 = makeShrd<MyClass>(10);
    EXPECT_EQ(ptr1->value, 10);
}

TEST(ShrdPtrTest, CopyConstructor) {
    SharedPtr<MyClass> ptr1 = makeShrd<MyClass>(20);
    SharedPtr<MyClass> ptr2 = ptr1;

    EXPECT_EQ(ptr1->value, 20);
    EXPECT_EQ(ptr2->value, 20);
    EXPECT_EQ(ptr1.getCount(), 2);
}

TEST(ShrdPtrTest, CopyAssignment) {
    SharedPtr<MyClass> ptr1 = makeShrd<MyClass>(30);
    SharedPtr<MyClass> ptr2 = ptr1;

    EXPECT_EQ(ptr1->value, 30);
    EXPECT_EQ(ptr2->value, 30);
    EXPECT_EQ(ptr1.getCount(), 2);
}

TEST(ShrdPtrTest, MoveConstructor) {
    SharedPtr<MyClass> ptr1 = makeShrd<MyClass>(40);
    SharedPtr<MyClass> ptr2 = std::move(ptr1);

    EXPECT_EQ(ptr2->value, 40);
    EXPECT_EQ(ptr2.getCount(), 1);
}

TEST(ShrdPtrTest, MoveAssignment) {
    SharedPtr<MyClass> ptr1 = makeShrd<MyClass>(50);


    SharedPtr<MyClass> ptr2 = std::move(ptr1);
    EXPECT_EQ(ptr2->value, 50);
    EXPECT_EQ(ptr2.getCount(), 1);
}

TEST(ShrdPtrTest, SelfAssignment) {
    SharedPtr<MyClass> ptr1 = makeShrd<MyClass>(60);

    ptr1 = ptr1;

    EXPECT_EQ(ptr1->value, 60);
}

TEST(ShrdPtrTest, DestructorDecreasesCount) {
    {
        SharedPtr<MyClass> ptr1 = makeShrd<MyClass>(70);
        EXPECT_EQ(ptr1.getCount(), 1); {
            SharedPtr<MyClass> ptr2 = ptr1;
            EXPECT_EQ(ptr1.getCount(), 2);
        }

        EXPECT_EQ(ptr1.getCount(), 1);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

