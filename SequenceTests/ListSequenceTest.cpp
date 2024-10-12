
#include <gtest/gtest.h>
#include "../Sequence/ListSequence.h" // Предполагается, что ваш класс ListSequence находится в этом заголовочном файле

class ListSequenceTest : public ::testing::Test {
protected:
    ListSequence<int>* seq;

    void SetUp() override {
        int* arr = new int[5]{1, 2, 3, 4, 5};
        seq =new ListSequence<int>(arr, 5);
    }
};

TEST_F(ListSequenceTest, GetFirst) {
    EXPECT_EQ(seq->getFirst(), 1);
}

TEST_F(ListSequenceTest, GetLast) {
    EXPECT_EQ(seq->getLast(), 5);
}

TEST_F(ListSequenceTest, GetSize) {
    EXPECT_EQ(seq->getSize(), 5);
}

TEST_F(ListSequenceTest, GetElement) {
    EXPECT_EQ(seq->get(2), 3);
}

TEST_F(ListSequenceTest, SetElement) {
    seq->set(10, 1);
    EXPECT_EQ(seq->get(1), 10);
}

TEST_F(ListSequenceTest, AppendElement) {
    seq->append(6);
    EXPECT_EQ(seq->getLast(), 6);
    EXPECT_EQ(seq->getSize(), 6);
}

TEST_F(ListSequenceTest, PrependElement) {
    seq->prepend(0);
    EXPECT_EQ(seq->getFirst(), 0);
    EXPECT_EQ(seq->getSize(), 6);
}

TEST_F(ListSequenceTest, InsertAtElement) {
    seq->insertAt(7, 2);
    EXPECT_EQ(seq->get(2), 7);
    EXPECT_EQ(seq->getSize(), 6);
}

TEST_F(ListSequenceTest, StreamOutput) {
    std::ostringstream os;
    os << *seq;
    EXPECT_EQ(os.str(), "1 2 3 4 5 ");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
