cmake_minimum_required(VERSION 3.10)

project(jaroWinklerKMeans)

include_directories(include)
file(GLOB SOURCES "source/*.cpp")

add_executable(jaroWinklerKMeans ${SOURCES})
