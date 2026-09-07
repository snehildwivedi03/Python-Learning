cmake_minimum_required(VERSION 3.15)

# 1. Suppress the CMP0167 warning by using the OLD policy behavior
if(POLICY CMP0167)
    cmake_policy(SET CMP0167 OLD)
endif()

# 2. Point to vcpkg (Ensure this path is 100% correct for your PC)
set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

project(BoostTest)

# 3. Use standard find_package (vcpkg will intercept this automatically)
find_package(Boost REQUIRED COMPONENTS system)

add_executable(BoostTest vgs_server.cpp)

# 4. Link the target
target_link_libraries(BoostTest PRIVATE Boost::system)  