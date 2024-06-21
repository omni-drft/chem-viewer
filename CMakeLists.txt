cmake_minimum_required(VERSION 3.29)

project(ChemViewer C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED True)

find_package(SDL2 REQUIRED)

add_executable(ChemViewer Main.c)

set_target_properties(ChemViewer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin    
)

target_include_directories(ChemViewer PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(ChemViewer PRIVATE ${SDL2_LIBRARIES})


