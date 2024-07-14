cmake_minimum_required(VERSION 3.29)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(ProcekEngine C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED True)

find_package(SDL2 REQUIRED)

add_library(ProcekEngine SHARED src/peBase.c)

set_target_properties(ProcekEngine PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib    
)

target_include_directories(ProcekEngine PRIVATE ${SDL2_INCLUDE_DIRS} ${CMAKE_BINARY_DIR}/include)
target_link_libraries(ProcekEngine PRIVATE ${SDL2_LIBRARIES} m)


