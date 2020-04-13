cmake_minimum_required(VERSION 3.9)

# set the project name and version
project(news_block_chain VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add lib
add_subdirectory(ext)
link_libraries(ws2_32 wsock32)
include_directories(ext/rapidjson/include)
include_directories(ext/cpp-httplib)
link_libraries(Dbghelp Dbghelp)

# add src
file(GLOB_RECURSE src_files "src/*.c" "src/*.cc" "src/*.cpp" "src/*.h" "src/*.hpp")
list(REMOVE_ITEM src_files "${CMAKE_SOURCE_DIR}/src/main.cpp")
add_executable(news_block_chain src/main.cpp ${src_files})
target_include_directories(news_block_chain PUBLIC src)

# test
#add_coverage(news_block_chain)

enable_testing()
option(BUILD_TEST "unit tests" ON)
if(BUILD_TEST)
    add_subdirectory(test)
endif()

# evaluate coverage
#coverage_evaluate()