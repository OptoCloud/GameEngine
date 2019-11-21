cmake_minimum_required(VERSION 3.7)

set(project logic)
project(${project})

set(${project}_SOURCES
        object.cpp
	)

set(${project}_HEADERS
        object.h
	)

add_subdirectory(eventhandler)

add_library(${project}
    eventhandler
    ${${project}_SOURCES}
    ${${project}_HEADERS}
    )
