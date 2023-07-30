#include <eio/string_emitter>
#include <eio/output>
#include <gtest/gtest.h>

TEST(Output, CanOutputString)
{
    std::string output("");
    eio::string_emitter ose(output);
    eio::output uut(ose);
    std::string_view vec1("Hello World!");
    uut.print(vec1);
    ASSERT_EQ(vec1.length(), output.size());
    ASSERT_STREQ(std::string(vec1).c_str(), output.c_str());

}

TEST(Output, CanOutputBraces)
{
    {
        std::string output("");
        eio::string_emitter ose(output);
        eio::output uut(ose);
        std::string_view vec("Hello{{ World!");
        std::string_view ret("Hello{ World!");
        uut.print(vec);
        EXPECT_EQ(ret.length(), output.size());
        EXPECT_STREQ(std::string(ret).c_str(), output.c_str()) << output;
    }
    {
        std::string output("");
        eio::string_emitter ose(output);
        eio::output uut(ose);
        std::string_view vec("Hello}} World!");
        std::string_view ret("Hello} World!");
        uut.print(vec);
        EXPECT_EQ(ret.length(), output.size());
        EXPECT_STREQ(std::string(ret).c_str(), output.c_str()) << output;
    }
}

TEST(Output, CanOutputParams)
{
    {
        std::string output("");
        eio::string_emitter ose(output);
        eio::output uut(ose);
        int value{5};
        uut.val(value);
        std::string_view vec("Hello{} World!");
        std::string_view ret("Hello5 World!");
        uut.print(vec);
        EXPECT_EQ(ret.length(), output.size());
        EXPECT_STREQ(std::string(ret).c_str(), output.c_str());
    }
}