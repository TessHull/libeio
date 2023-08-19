#include <eio/string_emitter>
#include <gtest/gtest.h>

TEST(StringEmitter, CanPopulateAString)
{
    std::string output("");
    eio::string_emitter UUT(output);
    UUT.emit('H');
    ASSERT_STREQ("H", output.c_str());
    eio::character str[]{"ello"};
    UUT.emit(str);
    ASSERT_STREQ("Hello", output.c_str());
    auto &fetchedString{UUT.str()};
    ASSERT_EQ(&output, &fetchedString);
}

TEST(SpanEmitter, CanPopulateBuffer)
{
    eio::character buffer[128]{""};
    eio::span_emitter UUT{eio::span(buffer)};
    UUT.emit('H');
    ASSERT_EQ(1u, UUT.size());
    std::string_view FirstComp(reinterpret_cast<char *> (buffer), UUT.size());
    ASSERT_EQ(0, FirstComp.compare("H"));
    eio::character str[]{"ello"};
    UUT.emit(str);
    ASSERT_EQ(5u, UUT.size());
    std::string_view SecondComp(reinterpret_cast<char *> (UUT.data()), UUT.size());
    std::string_view SCTarg("Hello");
    ASSERT_EQ(0, SecondComp.compare(SCTarg)) << buffer << ":" << SecondComp.data() << "(" << SecondComp.size() << ":" << SCTarg.size() << ")";
    ASSERT_EQ(128u, UUT.capacity());
    ASSERT_EQ(buffer, UUT.data());
    auto retspan{UUT.span()};
    ASSERT_EQ(buffer, retspan.data());
    ASSERT_EQ(5u, retspan.size());
}