cmake_minimum_required(VERSION 3.6)

# Set the project name
project (Main)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
	main.cpp
	thread_pool.h
	thread_pool.cpp
)

add_executable(Main ${SOURCES})