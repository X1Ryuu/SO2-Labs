cmake_minimum_required(VERSION 3.28)
project(DPP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -static -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")

add_executable(DPP main.cpp
        mutexPhil/mPhilDPP.cpp
        mutexPhil/mPhilDPP.h
        noMutexPhil/nPhilDPP.cpp
        noMutexPhil/nPhilDPP.h
)
