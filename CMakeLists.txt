cmake_minimum_required(VERSION 3.20)
project(PokerRanges)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_LIST_DIR}/install")
message(STATUS "Install path: ${CMAKE_INSTALL_PREFIX}")

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

# Qt project part

# QT_PATH arg
option(QT_PATH "Path to the Qt installation" "")

if(QT_PATH)
    # Use the provided QT_PATH
elseif(ENV{QT_PATH})
    set(QT_PATH $ENV{QT_PATH})
else() # Hardcode the Qt path
    set(QT_PATH "C:/Qt/6.10.2/msvc2022_64")
endif()
message(STATUS "Use Qt from: ${QT_PATH}")
list(APPEND CMAKE_PREFIX_PATH "${QT_PATH}")

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

add_executable(Poker
    src/poker/main.cpp
)
target_link_libraries(Poker Qt6::Core Qt6::Widgets)

set_target_properties(Poker PROPERTIES
    AUTOMOC ON
)

install(TARGETS Poker)

qt_generate_deploy_app_script(
    TARGET Poker
    OUTPUT_SCRIPT deploy_qt_runtime
    NO_UNSUPPORTED_PLATFORM_ERROR
)

install(SCRIPT ${deploy_qt_runtime})
