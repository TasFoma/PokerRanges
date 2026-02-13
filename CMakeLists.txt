cmake_minimum_required(VERSION 3.20)
project(PokerRanges VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

set(QT_PATH "C:/Qt/6.10.2/msvc2022_64" CACHE PATH "Qt path")
if(NOT QT_PATH AND DEFINED ENV{QT_PATH})
    set(QT_PATH $ENV{QT_PATH})
endif()
list(APPEND CMAKE_PREFIX_PATH "${QT_PATH}")
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

add_library(RangeManager STATIC
    src/range/Card.cpp
    src/range/Hand.cpp
    src/range/Range.cpp
    src/range/Cluster.cpp
    src/range/RangeManager.cpp
    src/range/Card.h
    src/range/Hand.h
    src/range/Range.h
    src/range/Cluster.h
    src/range/RangeManager.h
)

target_include_directories(RangeManager PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

add_executable(Example
    src/example/main.cpp
)

target_link_libraries(Example PRIVATE RangeManager)
target_include_directories(Example PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(PokerRanges
    src/poker/main.cpp
    src/poker/RangeWidget.cpp
    src/poker/RangeTableModel.cpp
    src/poker/RangeItemDelegate.cpp
    src/poker/RangeWidget.h
    src/poker/RangeTableModel.h
    src/poker/RangeItemDelegate.h
)

target_link_libraries(PokerRanges PRIVATE
    RangeManager
    Qt6::Core
    Qt6::Widgets
)

target_include_directories(PokerRanges PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/poker
)

set_target_properties(PokerRanges PROPERTIES
    AUTOMOC ON
    WIN32_EXECUTABLE TRUE
)
