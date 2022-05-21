cmake_minimum_required(VERSION 3.16)
project(TOg_TXT_Generator)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/TOi/Anass)
include_directories(src/TOi/Chloe)
include_directories(src/TOi/Yousra)

add_executable(TOg_TXT_Generator
        src/TOi/Anass/DFA.cpp
        src/TOi/Anass/DFA.h
        src/TOi/Anass/json.hpp
        src/TOi/Anass/main.cpp
        src/TOi/Anass/NFA.cpp
        src/TOi/Anass/NFA.h
        src/TOi/Anass/StateNFA.cpp
        src/TOi/Anass/StateNFA.h
        src/TOi/Anass/TransitionDFA.cpp
        src/TOi/Anass/TransitionDFA.h
        src/TOi/Anass/TransitionNFA.cpp
        src/TOi/Anass/TransitionNFA.h
        src/TOi/Chloe/DFA.cpp
        src/TOi/Chloe/DFA.h
        src/TOi/Chloe/json.hpp
        src/TOi/Chloe/NFA.cpp
        src/TOi/Chloe/NFA.h
        src/TOi/Chloe/RE.cpp
        src/TOi/Chloe/RE.h
        src/TOi/Chloe/State.cpp
        src/TOi/Chloe/State.h
        src/TOi/Yousra/Automata.cpp
        src/TOi/Yousra/Automata.h
        src/TOi/Yousra/DFA.cpp
        src/TOi/Yousra/DFA.h
        src/TOi/Yousra/NFA.cpp
        src/TOi/Yousra/NFA.h
        src/main.cpp
        src/MarkovChain.cpp src/MarkovChain.h
        src/State.cpp src/State.h)

