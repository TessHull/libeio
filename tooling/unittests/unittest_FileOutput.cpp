#include <eio/eio>
#include <gtest/gtest.h>
#include <iostream>
#include <fstream>



TEST(FileOut, CanOpenFileAndWrite)
{
    std::string_view cFileName{"tmp/CanOpenFileAndWrite.txt"};
    std::string_view cTestData{"Hello World!"};
    {
        eio::FileOutput UUT(cFileName);
        UUT.print(cTestData);
    }
    std::ifstream infile(cFileName.data());
    std::string DataFromFile("");
    while (not infile.eof())
    {
        char tmp;
        if (not infile.get(tmp).eof())
        {
            DataFromFile.push_back(tmp);
        }
    }
    EXPECT_STREQ(cTestData.data(), DataFromFile.c_str());
}

TEST(FileOut, CanHandleAreferenceType)
{
    std::string_view cFileName{"tmp/CanHandleAreferenceType.txt"};
    std::string_view cTestData{"Hello World!"};
    {
        eio::FileOutput UUT(cFileName);
        UUT.ref(5);
        UUT.print(cTestData);
    }
}