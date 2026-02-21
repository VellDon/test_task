cmake_minimum_required(VERSION 3.23)
project(MyApp)
set(CMAKE_CXX_STANDARD 23)
add_executable(MyApp main.cpp)
target_include_directories(MyApp PRIVATE ./tomlplusplus/include)
./MyApp