#include <eio/convert>
#include <gtest/gtest.h>
#include <array>

TEST(itoa, SignedNothingAndMinus)
{
    std::array<char, 128> buf;
    EXPECT_EQ(2u, eio::itoa<eio::SignHandling::NothingAndMinus>(10, std::span<char>(buf)));
    EXPECT_STREQ("10", buf.data());
    EXPECT_EQ(7u, eio::itoa<eio::SignHandling::NothingAndMinus>(1234567, std::span<char>(buf)));
    EXPECT_STREQ("1234567", buf.data());
    EXPECT_EQ(8u, eio::itoa<eio::SignHandling::NothingAndMinus>(-1234567, std::span<char>(buf)));
    EXPECT_STREQ("-1234567", buf.data());
    EXPECT_EQ(11u, eio::itoa<eio::SignHandling::NothingAndMinus>(0xfffffffff, std::span<char>(buf)));
    EXPECT_STREQ("68719476735", buf.data());
    EXPECT_EQ(1u, eio::itoa<eio::SignHandling::NothingAndMinus>(0, std::span<char>(buf)));
    EXPECT_STREQ("0", buf.data());
    EXPECT_EQ(5u, eio::itoa<eio::SignHandling::NothingAndMinus>(65535, std::span<char>(buf)));
    EXPECT_STREQ("65535", buf.data());
    EXPECT_EQ(10u, eio::itoa<eio::SignHandling::NothingAndMinus>(0xffffffffll, std::span<char>(buf)));
    EXPECT_STREQ("4294967295", buf.data());
    EXPECT_EQ(2u, eio::itoa<eio::SignHandling::NothingAndMinus>((char)10, std::span<char>(buf)));
    EXPECT_STREQ("10", buf.data());
}