gtest_src = [
    'googletest/googletest/src/gtest-all.cc',
    'googletest/googletest/src/gtest_main.cc',
]
gtest_include = ['googletest/googletest/include']
gtest_srcinc = ['googletest/googletest']
gtest_lib = static_library('gtest', sources: [gtest_src], include_directories: [gtest_include, gtest_srcinc])


test_src = [
    'unittest_convert.cpp',
    'unittest_int_formatter.cpp',
    'unittest_FileOutput.cpp',
    'unittest_float_formatter.cpp',
    'unittest_generic_formatter.cpp',
]
testrunner = executable('testrunner', sources: [test_src], link_with: [libeio, gtest_lib], include_directories: [libeio_Incs, gtest_include])
test('unit tests', testrunner)