#include <gtest/gtest.h>
#include "../src/MyString.h"
// #include <gmock/gmock.h>

TEST(MyString, capacity)
{
    // Arrange
    MyString a;
    const size_t capacity_size = 17;
    const size_t textlen_size = 0;

    // Act
    a.ExtendCapacity2TimesThanNeed();

    // Assert
    GTEST_ASSERT_EQ(a.capacity(), capacity_size);
    GTEST_ASSERT_EQ(a.size(), textlen_size);
}


int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}