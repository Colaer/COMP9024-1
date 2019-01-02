cmake_minimum_required(VERSION 3.9)
project(week3 C)

set(CMAKE_C_STANDARD 99)

add_executable(search pagerank.c Graph.h list.h readData.h readData.c Graph.c list.c collection.txt)