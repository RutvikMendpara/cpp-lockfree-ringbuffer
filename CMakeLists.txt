cmake_minimum_required(VERSION 3.10)
project(ringbuffer)

set(CMAKE_CXX_STANDARD 17)
add_executable(ringbuffer "ring_buffer_single_threaded.cpp" "main.cpp" "ring_buffer_single_threaded.h")
