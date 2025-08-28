cmake_minimum_required(VERSION 3.10)
project(Chess)

# Find SFML package (adjust the version if necessary)
find_package(SFML 2.5 REQUIRED graphics window system)

# Add the executable
add_executable(Chess main.cpp)

# Link SFML libraries
target_link_libraries(Chess sfml-graphics sfml-window sfml-system)