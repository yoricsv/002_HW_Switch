# 002_HW_Switch

# *******************************************************************************
# @file           : README.md
# @brief          : Short description of the project
# *******************************************************************************
# @attention
#
# > JUST FOR ME!!! > I wanna refactoring this code!!! (slit on the files)
#
# The PROJECT STRUCTURE (blank) part describes the common structure of the
# project in order to understand where the code is and where the Cmake 
# generator finds the source files.
# *******************************************************************************
# @description
# 
# A few months ago I made a program for the STM32F103x MCU, making a dynamic
# indication on a four-digit seven-segment display. Of course, creating a program
# in which I only use the switch operator is not interested, and I try to
# implement the same in C ++ for a console application.
# *******************************************************************************

# *********************** PROJECT STRUCTURE (blank) ************************* 
# [<Project_name>]
#  |
#  |->[.build]           // directory for building system
#  |   |
#  |   |->[CMakeFiles]   // all necessary directories and files for CMake build 
#  |                     // generator
#  |
#  |->[.git]             // all necessary directories and files for Git
#  |
#  |
#  |->[.settings]        // contains project file directories for different IDEs
#  |
#  |
#  |->[debug]            // contains compiller, linker, object files
#  |   |
#  |   |->[logs]         // contains logs
#  |
#  |->[<Project_name Repository>]
#  |   |
#  |   |->[inc]          // contains public/private HEADERS (*.h) (might be split
#  |   |                 // into two directories public and privat)
#  |   |->[res]          // contains static/dynamic LIBRARIES     (might be split
#  |   |                 // into two directories static and dynamic)
#  |   |->[src]          // contains SOURCE files/code(s)   (.с; .cpp)
#  |   |
#  |   |->[ui]           // these directories for applications with USER INTERFACE
#  |                     // (might contains QML)
#  |
#  |->[output]           // directory for executable applications
#  |
#  |->[tests]            // directory for unit tests
#  |
#  |
#  |---> .gitignore
#  |---> CMakeLists.txt
#  |---> README.md
# ********************** END PROJECT STRUCTURE (blank) ************************ 