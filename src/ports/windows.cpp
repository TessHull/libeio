#include <eio/eio>
#include <windows.h>
#include <fileapi.h>

namespace eio
{

FileOutput out{GetStdHandle(STD_OUTPUT_HANDLE)};

concrete_file_emitter::concrete_file_emitter(void* File)
: _file(File)
{

}
concrete_file_emitter::concrete_file_emitter(std::string_view FilePath)
: _file(CreateFileA(FilePath.data(), GENERIC_WRITE, FILE_SHARE_READ, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr))
, _managePointer(true)
{

}
concrete_file_emitter::~concrete_file_emitter()
{
    if (_managePointer)
    {
        CloseHandle(_file);
        _file = nullptr;
    }
}
bool concrete_file_emitter::emit(uint8_t arg)
{
    WriteFile(_file, &arg, 1, nullptr, nullptr);
    return true;
}
bool concrete_file_emitter::emit(std::span<uint8_t const> arg)
{
    WriteFile(_file, arg.data(), arg.size(), nullptr, nullptr);
    return true;
}

}//eio