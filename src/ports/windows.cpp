#include <eio/eio>
#include <windows.h>
#include <fileapi.h>

namespace eio
{

FileOutput out{GetStdHandle(STD_OUTPUT_HANDLE)};

FileOutput::FileOutput(void* File)
: _file(File)
{

}

FileOutput::FileOutput(std::string_view FilePath)
: _file(CreateFileA(FilePath.data(), GENERIC_WRITE, FILE_SHARE_READ, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr))
, _managePointer(true)
{

}
FileOutput::~FileOutput()
{
    if (_managePointer)
    {
        CloseHandle(_file);
        _file = nullptr;
    }
}
void FileOutput::print(std::string_view format)
{
    WriteFile(_file, format.data(),format.size(), nullptr, nullptr);
}

}//eio