---
title: eio - an embedded i/o library
author: Tess Hull
abstract: |
  embedded io without streams, locale, or anything else in the interfaces that touches either.
  This library is designed for embedded logging in a type-safe manner without going to the 
  code space cost of using a library that can touch std::locale
output:
  pdf_document:
    path: tmp/eio.pdf
---

# Why Another I/O Library

My background is embedded software on arm cortex-m profile micro-controllers in C++.  C++ lacks a good IO library.

What is good? Good is...

- Type Safe
- Only pay for what you use

I don't feel that any of the standard libraries (std::streams, std::format, printf) meet all of these requirements.


## existing libraries

### printf

Printf is the past, it is history. It is not type safe.
every print to it using the implementations in our available libc results in parameters being cast to known safe and working types, making it very verbose in the code. It has been a source of many a stack corruption.

Printf is also small.

Printf is the current defacto standard in the embedded world I work in, because the space it uses is affordable, unlike its competitors.

### iostreams

iostreams *is* typesafe! it is also fairly easy to use.
It is *not* easy to write/implement translations for, but that isn't an issue that concerns me muchly.

However, the inability to really use for translations makes the next point inexcusable:

- iostreams requires and brings in std::locale to your code image
  - This adds a signifficant degree of bloat to your code image.

Supposedly, the concept of locales is supposed to reduce work when porting to support other languages and cultures, giving clues to formatting dates, numbers and other elements.  But in my space, the only person or people who have to read the logs that the io is being used for are me and my colleagues... and if the logs could be generated in other human languages... I would be unable to read and process them, thus negating their use.

Therefore the cost of std::locale is a burden of no benefit and significant pain.

### libfmt/std::format

I want to like std::format - and the libfmt that it originates from - but it too seems to have been infected with std::locale and all I have said for streams on it. std::format inspires characteristics of this library.

## another take

This library is an attempt at another take, an attempt to created an io library suitable for embedded applications that is typesafe and suitable for creating logging and other porcelain formats that don't require translation and locale formatting information.

libeio's design goals are

- not going to be achieved immediately
  - it is more important to prove the core concepts than to reimplement details to begin with
- to not include std::locale
- to be at-least 50% smaller in size than including iostreams
  - This is a failure bound. Smaller still is desired, but if I can't achieve 50% smaller, then this work will be abandoned as not worth the cost.
- provide portability, so that the library can be used on embedded environments and on tooling around a project on host computers to allow for code re-use
  - Planned Targets:
    - MSYS2 g++/x86_64
    - ubuntu linux 22.04
    - gcc-arm-none-eabi/newlib/cortex-m
- provide modularity, so that if you don't need floating point, you don't have floating point taking up space in your code
- provide for printing custom types

# Building libeio

libeio is being worked on as a home project. the default environment in these early stages is MSYS2.

To build the library (such as it is) and the benchmarks and unittests, from an MSYS2 prompt, run `./task all`

# eio layout concepts

```cpp
#include <eio/eio.hpp>

void example1()
{
    eio::output stdout;
    stdout.println("Hello World!");
}

void example2(int a, float b, std::string_view c)
{
    eio::formatter fmtr;
    fmtr.param(a).param(b);
    fmtr.param(c);
    auto argcount{fmtr.args()};
    fmtr.param(a * b).format("With values a ({}), b ({}), and function c ({}), the result is {}");
    auto postEmitArgs{fmtr.args()};
    fmtr.param(argcount).param(postEmitArgs).param(fmtr.args() + 1);
    fmtr.append("\nWe have {2} args. Before the first format line we had {0} args, after the format, we had {1}.");
    eio::output stdout;
    stdout.println(fmtr.str());
}

struct aStruct
{
    uint16_t a{0x1234};
    uint32_t b{0x12345678};
};

void example3()
{
    aStruct foo;
    eio::output out;
    out.param(foo).println("{}");
    out.param(foo, "table").println("{}");
    out.param(foo).println("{:table,4}");
    out.param(foo).println("{:tableW,1}");
}

struct bStruct : eio::printable
{
    uint16_t a{0x1234};
    uint32_t b{0x12345678};
    std::string print([[maybe_unused]]std::string_view format) const override
    {
        eio::formatter fmtr;
        fmtr.param(a).param(b).format("bStruct: a = {}, b = {}");
        return fmtr.str();
    }
};

void example4()
{
    bStruct foo;
    eio::output out;
    out.param(foo).println("{}");
}

int main()
{
    example1();
    example2(2, 3.14, "Radians");
    example3();
    example4();
}
```

Output:
```
Hello World!
With the values a (2), b (3.14), and function c (Radians), the result is 6.28
We have 3 args. Before the first format line we had 3 args, after the format, we had 0.
[hex: 35 12 00 00 78 56 34 12 (8 bytes)]
  \ 00 01 02 03 04 05 06 07
000 35 12 00 00 78 56 34 12
  \ 00 01 02 03
000 35 12 00 00
004 78 56 34 12
  \        0
000 00001234
004 12345678
bStruct: a = 4669, b = 305419896

```