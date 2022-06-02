cmake_minimum_required(VERSION 3.16)
project(TOg_TXT_Generator)

set(CMAKE_CXX_STANDARD 14)

FILE(GLOB_RECURSE SRC_FILES "src/*.h" "src/*.cpp" "src/*.hpp")
add_executable(${PROJECT_NAME} ${SRC_FILES})