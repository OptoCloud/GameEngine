cmake_minimum_required(VERSION 3.7)

set(project eventhandler)
project(${project})

add_library(${project} STATIC
	callbackhandler.h
	eventhandler.h
	functors.cpp
	functors.h
)

