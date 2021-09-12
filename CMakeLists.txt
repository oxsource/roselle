cmake_minimum_required(VERSION 3.20)
project(lct)

set(CMAKE_CXX_STANDARD 11)

add_executable(lct main.cpp Buffer.cpp Buffer.h Caches.cpp Caches.h MMapHeads.cpp MMapHeads.h MMaps.cpp MMaps.h Swaps.cpp Swaps.h)
