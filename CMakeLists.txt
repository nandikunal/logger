cmake_minimum_required (VERSION 3.10)

project (Logger)

include_directories (
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
)

add_executable (LoggerDemo
    main.cpp
    src/outputs.cpp
    src/mlogger.cpp
)

target_link_libraries(
	LoggerDemo
	pthread
)