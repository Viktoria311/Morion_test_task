cmake_minimum_required(VERSION 3.0)
project(configparser)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#add_library(my_lib src/my_lib/CFileConfig.cpp include/my_lib/CFileConfig.h include/my_lib/CConfig.h)
add_library(my_lib ${PROJECT_SOURCE_DIR}/src/my_lib/CFileConfig.cpp)

target_include_directories(my_lib PUBLIC include)

add_executable(configparser src/main.cpp)

target_link_libraries(configparser PUBLIC my_lib)
target_include_directories(configparser PUBLIC include)