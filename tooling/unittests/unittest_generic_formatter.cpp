#include <eio/formatters>
#include <eio/string_emitter>
#include <gtest/gtest.h>

TEST(GenericFormatter, UnsignedInt)
{
    uint32_t cTestValue{0x01020304};
    eio::generic_formatter UUT(std::span(reinterpret_cast<uint8_t*>(&cTestValue), sizeof(cTestValue)));
    std::string Result("");
    eio::string_emitter _emit(Result);
    auto retval{UUT.emit(_emit)};
    EXPECT_TRUE(retval);
    EXPECT_STREQ(Result.c_str(), "[hex: 04 03 02 01 (4 bytes)]");
}