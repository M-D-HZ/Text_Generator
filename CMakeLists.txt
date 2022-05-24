cmake_minimum_required(VERSION 3.16)
project(TOg_TXT_Generator)

set(CMAKE_CXX_STANDARD 14)

set(MARKOV_SOURCE_FILES
        src/main.cpp
        src/MarkovChain.cpp src/MarkovChain.h
        src/MarkovState.cpp src/MarkovState.h
        )

add_executable(Markovchain ${MARKOV_SOURCE_FILES})