cmake_minimum_required(VERSION 3.10)

project (TyporaTools)

set(CMAKE_CXX_STANDARD 17)

add_executable(tic ImgCleaner.cpp)
add_executable(ta Archiver.cpp)
