cmake_minimum_required (VERSION 3.5 FATAL_ERROR)

    set (PROJECT_NAME    002_HW_Switch)
project (${PROJECT_NAME} LANGUAGES CXX)

    set (CMAKE_CXX_STANDARD           14)
    set (CMAKE_CXX_STANDARD_REQUIRED  ON)

add_executable (${PROJECT_NAME}
    src/main.cpp              inc/main.h
    src/conver_to_binary.cpp  inc/convert_to_binary.h
)

