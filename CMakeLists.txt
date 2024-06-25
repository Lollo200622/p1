cmake_minimum_required(VERSION 3.10)


add_executable(robot_move src/main.cpp
        src/grid.cpp
        include/grid.hpp
        include/common.hpp
        src/common.cpp
        include/robot.hpp
        src/robot.cpp)

target_include_directories(robot_move PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
