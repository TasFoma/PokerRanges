cmake_minimum_required(VERSION 3.20)
project(PokerRanges)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(src)

add_library(RangeManager
    src/range/Card.cpp
    src/range/Hand.cpp
    src/range/Range.cpp
    src/range/Cluster.cpp
    src/range/RangeManager.cpp
)

add_executable(Example
    src/example/main.cpp
)

target_link_libraries(Example PRIVATE RangeManager)