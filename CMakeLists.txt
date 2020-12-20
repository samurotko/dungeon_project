cmake_minimum_required(VERSION 3.0)
project(dungeon_crawler_2020_6)

set(CMAKE_CXX_STANDARD 14)

# Fill EXECUTABLE_HEADERS and EXWECUTABLE_SOURCES variables with filenames
include_directories("src")

# Add DungeonCrawler target
file(GLOB SOURCES src/*.cpp)
add_executable(rpg ${SOURCES})

# Find and link SFML
#find_package(SFML 2.5 COMPONENTS audio system window graphics network REQUIRED)
target_link_libraries(rpg sfml-audio sfml-system sfml-window sfml-graphics sfml-network)