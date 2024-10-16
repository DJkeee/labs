#include <gtest/gtest.h> // Make sure to include the Google Test header
#include "../Pointers/smartPtr.h"

class MyClass {
public:
    int value;

    MyClass(int val) : value(val) {
    }
};

TEST(SmartPtrTest, CreateAndUse) {
    SmartPtr<MyClass> ptr1 = makeSmart<MyClass>(10);
    EXPECT_EQ(ptr1->value, 10);
}

TEST(SmartPtrTest, CopyConstructor) {
    SmartPtr<MyClass> ptr1 = makeSmart<MyClass>(20);
    SmartPtr<MyClass> ptr2 = ptr1;

    EXPECT_EQ(ptr1->value, 20);
    EXPECT_EQ(ptr2->value, 20);
    EXPECT_EQ(ptr1.getCount(), 2);
}

TEST(SmartPtrTest, CopyAssignment) {
    SmartPtr<MyClass> ptr1 = makeSmart<MyClass>(30);
    SmartPtr<MyClass> ptr2 = ptr1;

    EXPECT_EQ(ptr1->value, 30);
    EXPECT_EQ(ptr2->value, 30);
    EXPECT_EQ(ptr1.getCount(), 2);
}

TEST(SmartPtrTest, MoveConstructor) {
    SmartPtr<MyClass> ptr1 = makeSmart<MyClass>(40);
    SmartPtr<MyClass> ptr2 = std::move(ptr1);

    EXPECT_EQ(ptr2->value, 40);
    EXPECT_EQ(ptr2.getCount(), 1);
}

TEST(SmartPtrTest, MoveAssignment) {
    SmartPtr<MyClass> ptr1 = makeSmart<MyClass>(50);
    SmartPtr<MyClass> ptr2 = std::move(ptr1);

    EXPECT_EQ(ptr2->value, 50);
    EXPECT_EQ(ptr2.getCount(), 1);
}

TEST(SmartPtrTest, SelfAssignment) {
    SmartPtr<MyClass> ptr1 = makeSmart<MyClass>(60);

    ptr1 = ptr1;

    EXPECT_EQ(ptr1->value, 60);
}

TEST(SmartPtrTest, DestructorDecreasesCount) {
    {
        SmartPtr<MyClass> ptr1 = makeSmart<MyClass>(70);
        EXPECT_EQ(ptr1.getCount(), 1);
        {
            SmartPtr<MyClass> ptr2 = ptr1;
            EXPECT_EQ(ptr1.getCount(), 2);
        }

        EXPECT_EQ(ptr1.getCount(), 1);
    }
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
