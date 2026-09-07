cmake_minimum_required(VERSION 3.15)

# FORCE CMake to use vcpkg (Add this line first!)
set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

project(BoostTest)

set(Boost_NO_BOOST_CMAKE ON) 
find_package(Boost REQUIRED COMPONENTS system)

add_executable(BoostTest main.cpp)
target_link_libraries(BoostTest PRIVATE Boost::system)