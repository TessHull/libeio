#include <eio/eio>
#include <windows.h>
#include <fileapi.h>

namespace eio
{

FileOutput out{GetStdHandle(STD_OUTPUT_HANDLE)};

file_emitter::file_emitter(void* File)
: _file(File)
{

}
file_emitter::file_emitter(std::string_view FilePath)
: _file(CreateFileA(FilePath.data(), GENERIC_WRITE, FILE_SHARE_READ, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr))
, _managePointer(true)
{

}
file_emitter::~file_emitter()
{
    if (_managePointer)
    {
        CloseHandle(_file);
        _file = nullptr;
    }
}
bool file_emitter::emit(uint8_t arg)
{
    WriteFile(_file, &arg, 1, nullptr, nullptr);
    return true;
}
bool file_emitter::emit(string_view arg)
{
    WriteFile(_file, arg.data(), arg.size(), nullptr, nullptr);
    return true;
}
bool file_emitter::emit_span(cspan arg)
{
    WriteFile(_file, arg.data(), arg.size(), nullptr, nullptr);
    return true;
}

}//eio