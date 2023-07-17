#include <eio/eio>
#include <gtest/gtest.h>

TEST(FloatFormatter, UnsignedInt)
{
    float cTestValue{1024.2048};
    eio::float_formatter UUT(cTestValue);
    std::string Result("");
    auto retval{UUT.emit(Result)};
    EXPECT_TRUE(retval);
    EXPECT_STREQ(Result.c_str(), "1024.204833");//the test vector is not precisely representable as a float and this is the rounding error
}

TEST(FloatFormatter, smallfloat)
{
    float cTestValue{1};
    eio::float_formatter UUT(cTestValue);
    std::string Result("");
    auto retval{UUT.emit(Result)};
    EXPECT_TRUE(retval);
    EXPECT_STREQ(Result.c_str(), "1.000000");
}

TEST(FloatFormatter, zerofloat)
{
    float cTestValue{0};
    eio::float_formatter UUT(cTestValue);
    std::string Result("");
    auto retval{UUT.emit(Result)};
    EXPECT_TRUE(retval);
    EXPECT_STREQ(Result.c_str(), "0.000000");
}

TEST(FloatFormatter, negfloat)
{
    float cTestValue{-1};
    eio::float_formatter UUT(cTestValue);
    std::string Result("");
    auto retval{UUT.emit(Result)};
    EXPECT_TRUE(retval);
    EXPECT_STREQ(Result.c_str(), "-1.000000");
}