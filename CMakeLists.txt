cmake_minimum_required(VERSION 3.3)
project(TP2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

set(SOURCE_FILES main.c
        tadbasics/cell.c tadbasics/cell.h
        tadbasics/queue.c tadbasics/queue.h
        tadbasics/xcpt.c tadbasics/xcpt.h
        image.c image.h
        )

add_executable(TP2 ${SOURCE_FILES})
