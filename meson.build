project('libeio', 'cpp', default_options: ['optimization=g', 'warning_level=3', 'werror=true', 'b_staticpic=false', 'cpp_std=c++20', 'cpp_args=-ggdb -ffunction-sections -fdata-sections',])

CommonSrc = [

]
WindowsSrc = [
    'src/ports/windows.cpp',
]

libeio_src = [CommonSrc, WindowsSrc]
libeio_Incs = include_directories([
    'include'
])
test = ['tooling/benchmarks/helloworld/eio.cpp']

libeio = static_library('eio', sources: [libeio_src], include_directories: libeio_Incs, install: true)

subdir('tooling/unittests')