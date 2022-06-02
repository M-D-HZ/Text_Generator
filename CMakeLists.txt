cmake_minimum_required(VERSION 3.16)
project(TOg_TXT_Generator)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(SRC_FILES
        src/main.cpp
        src/MarkovChain.cpp src/MarkovChain.h
        src/Parser.cpp src/Parser.h
        src/MarkovState.cpp src/MarkovState.h
        GUI/MainGuiWindow.h GUI/MainGuiWindow.cpp
        )

set(Qt5_DIR "C:/Qt/5.15.2/mingw81_64/lib/cmake/Qt5")
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets)



#FILE(GLOB_RECURSE SRC_FILES src/*.h src/*.cpp src/*.hpp)