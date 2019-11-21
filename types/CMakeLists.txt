cmake_minimum_required(VERSION 3.7)

set(project types)
project(${project})

set(${project}_SOURCES
	animation.cpp
        bitmap.cpp
        bone.cpp
        color.cpp
        mesh.cpp
        quaternion.cpp
        triangle.cpp
        vector2.cpp
        vector3.cpp
        vector4.cpp
        vertex.cpp
	)

set(${project}_HEADERS
	types.h
	)

add_library(${project}
    ${${project}_SOURCES}
    ${${project}_HEADERS}
    )
