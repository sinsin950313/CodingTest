cmake_minimum_required(VERSION 3.0.0)
project(CodingTest VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(TestName CACHE STRING "Test Name")
add_executable(CodingTest main.cpp ${TestName}/${TestName}.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
