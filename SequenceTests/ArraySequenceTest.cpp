#include "gtest/gtest.h"
#include "../Sequence/ArraySequence.h"


class ArraySequenceTest : public ::testing::Test {
protected:
    ArraySequence<int>* seq;

    void SetUp() override {
        int* items = new int[3]{1, 2, 3};
        seq = new ArraySequence<int>(items, 3);
    }
};

TEST_F(ArraySequenceTest, GetFirst) {
    EXPECT_EQ(seq->getFirst(), 1);
}

TEST_F(ArraySequenceTest, GetLast) {
    EXPECT_EQ(seq->getLast(), 3);
}

TEST_F(ArraySequenceTest, GetSize) {
    EXPECT_EQ(seq->getSize(), 3);
}

TEST_F(ArraySequenceTest, Append) {
    seq->append(4);
    EXPECT_EQ(seq->getSize(), 4);
    EXPECT_EQ(seq->getLast(), 4);
}

TEST_F(ArraySequenceTest, Prepend) {
    seq->prepend(0);
    EXPECT_EQ(seq->getSize(), 4);
    EXPECT_EQ(seq->getFirst(), 0);
}

TEST_F(ArraySequenceTest, InsertAt) {
    seq->insertAt(5, 1);
    EXPECT_EQ(seq->getSize(), 4);
    EXPECT_EQ(seq->get(1), 5);
}

TEST_F(ArraySequenceTest, Set) {
    seq->set(10, 1);
    EXPECT_EQ(seq->get(1), 10);
}

TEST_F(ArraySequenceTest, OutOfRangeGet) {
    EXPECT_THROW(seq->get(5), std::out_of_range);
}

TEST_F(ArraySequenceTest, OutOfRangeSet) {
    EXPECT_THROW(seq->set(10, 5), std::out_of_range);
}

TEST_F(ArraySequenceTest, OutOfRangeInsertAt) {
    EXPECT_THROW(seq->insertAt(10, 5), std::out_of_range);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
