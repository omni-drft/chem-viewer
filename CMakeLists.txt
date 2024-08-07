cmake_minimum_required(VERSION 3.29)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(ProcekEngine C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED True)

find_package(SDL2 REQUIRED)

add_library(ProcekEngine STATIC 
    src/peBase.c
    src/peRectangle.c
    src/peMath.c
)

set_target_properties(ProcekEngine PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

target_include_directories(ProcekEngine 
    PRIVATE 
        ${CMAKE_BINARY_DIR}/include
    PUBLIC
        ${SDL2_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(ProcekEngine 
    PRIVATE 
        ${SDL2_LIBRARIES} 
        m
)



add_executable(ProcekEngineTest test/Main.c)

set_target_properties(ProcekEngineTest 
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

target_include_directories(ProcekEngineTest PRIVATE include)
target_link_libraries(ProcekEngineTest PRIVATE ProcekEngine)

