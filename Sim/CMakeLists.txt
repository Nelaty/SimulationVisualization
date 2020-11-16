cmake_minimum_required(VERSION 3.11)
project("SimulationVisualization")
set(PROJECT_SHORT_NAME "Sim")

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/)

# Projects
include_directories(
        Sim/src
        ../EyeCandy3D/EyeCandy3D/include
        ../EyeCandy3D/External/include
        /usr/include/freetype2
        ../Rumble3D/include)

add_subdirectory(Sim/src)
