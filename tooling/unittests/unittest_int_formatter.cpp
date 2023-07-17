#include <eio/eio>
#include <gtest/gtest.h>

TEST(IntFormatter, UnsignedInt)
{
    uint32_t cTestValue{0x01020304};
    eio::int_formatter UUT(cTestValue);
    std::string Result("");
    auto retval{UUT.emit(Result)};
    EXPECT_TRUE(retval);
    EXPECT_STREQ(Result.c_str(), "16909060");
}

TEST(IntFormatter, smallint)
{
    int cTestValue{1};
    eio::int_formatter UUT(cTestValue);
    std::string Result("");
    auto retval{UUT.emit(Result)};
    EXPECT_TRUE(retval);
    EXPECT_STREQ(Result.c_str(), "1");
}

TEST(IntFormatter, zeroint)
{
    int cTestValue{0};
    eio::int_formatter UUT(cTestValue);
    std::string Result("");
    auto retval{UUT.emit(Result)};
    EXPECT_TRUE(retval);
    EXPECT_STREQ(Result.c_str(), "0");
}

TEST(IntFormatter, negint)
{
    int cTestValue{-1};
    eio::int_formatter UUT(cTestValue);
    std::string Result("");
    auto retval{UUT.emit(Result)};
    EXPECT_TRUE(retval);
    EXPECT_STREQ(Result.c_str(), "-1");
}

TEST(IntFormatter, neguint)
{
    unsigned cTestValue{static_cast<unsigned>(-1)};
    eio::int_formatter UUT(cTestValue);
    std::string Result("");
    auto retval{UUT.emit(Result)};
    EXPECT_TRUE(retval);
    EXPECT_STREQ(Result.c_str(), "4294967296");
}