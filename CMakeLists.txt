cmake_minimum_required(VERSION 4.1)
project(personalSite)
set(SOURCE_FILES
    src/main.cpp
    src/parser.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
