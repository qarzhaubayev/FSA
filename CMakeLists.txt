cmake_minimum_required(VERSION 3.10)
project(VendingMachine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Library with the core logic
add_library(vending
    VendingMachine.cpp
)
target_include_directories(vending PUBLIC include)

# 2. Console executable
add_executable(vending_app main.cpp)
target_link_libraries(vending_app PRIVATE vending)
