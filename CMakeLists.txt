cmake_minimum_required (VERSION 3.8)

project(clw-03)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX") # CMake already contains W3 in its flags
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra-semi -O1 -g -fsanitize=address -fno-omit-frame-pointer")
endif()

 add_executable(task-1-test src/task1/smoke_test.cpp src/task1/typeset.hpp)
 add_executable(task-2-test src/task2/smoke_test.cpp src/task2/pretty_print.hpp)
 add_executable(task-3-test src/task3/smoke_test.cpp src/task3/projections.hpp)
